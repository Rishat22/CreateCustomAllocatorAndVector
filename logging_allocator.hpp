#ifndef LOGGING_ALLOCATOR_H
#define LOGGING_ALLOCATOR_H
#include <iostream>

#define USE_PRETTY 1

template<typename T>
struct logging_allocator {
	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template<typename U>
	struct rebind {
		using other = logging_allocator<U>;
	};

	logging_allocator() = default;
	logging_allocator(const std::size_t size)
	{
		ReAlloc(size);
	}
	~logging_allocator() = default;

	template<typename U>
	logging_allocator(const logging_allocator<U>&) {

	}

	T *allocate(std::size_t n) {

		if(IsUsedAllocatedMem())
		{
			if(++m_Size >= m_Capacity)
				ReAlloc(m_Capacity + m_Capacity /2);
			return &m_Data[m_Size - 1];
		}

		auto p = std::malloc(n * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T *>(p);
	}

	void deallocate(T *p, std::size_t n) {
		if(IsUsedAllocatedMem())
		{
			if(--m_Size <= m_Capacity/2)
				ReAlloc(m_Size + m_Size /2);
			return;
		}
		else
			std::free(p);
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		if(IsUsedAllocatedMem())
			return;
		new(p) U(std::forward<Args>(args)...);
	};

	void destroy(T *p) {
		if(IsUsedAllocatedMem())
			return;
		p->~T();
	}

private:
	void ReAlloc(const size_t newCapacity)
	{
		T* newBlock = (T*)::operator new( newCapacity * sizeof (T) );

		if(newCapacity < m_Size)
				m_Size = newCapacity;

		for(size_t i = 0; i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]);

		for(size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		::operator delete( m_Data,m_Capacity * sizeof (T));
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}

	bool IsUsedAllocatedMem () { return m_Size != 0; }
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};
#endif // LOGGING_ALLOCATOR_H
