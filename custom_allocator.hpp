#ifndef custom_allocator_H
#define custom_allocator_H
#include <iostream>

#define USE_PRETTY 1

template<typename T, const std::size_t SIZE>
struct custom_allocator {
	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template<typename U>
	struct rebind {
		using other = custom_allocator<U, SIZE>;
	};

	custom_allocator() = default;
	~custom_allocator()
	{
		::operator delete( m_Data, m_Capacity * sizeof (T) );
	}

	explicit custom_allocator(const custom_allocator<T,  SIZE>& /*inputAllocator*/)  noexcept
	{
	}

	template<typename U>
	explicit custom_allocator(const custom_allocator<U, SIZE>& /*inputAllocator*/)  noexcept
	{
	}

	T* allocate(std::size_t n) {
		if(m_Data == nullptr)
		{
			ReAlloc(SIZE);
		}
		if (m_Size == SIZE)
			throw std::out_of_range("Maximum number of elements must not exceed the specified value");
		return &m_Data[m_Size++];
	}

	void deallocate(T *p, std::size_t n) {
		if( m_Capacity > n)
			m_Capacity -= n;
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		new(p) U(std::forward<Args>(args)...);
	};

	void destroy(T *p) {
		p->~T();
	}

private:
	void ReAlloc(const size_t newCapacity)
	{
		auto newBlock = std::malloc(newCapacity * sizeof(T));
		if (newBlock == nullptr)
			throw std::bad_alloc();

//		T* newBlock = (T*)::operator new( newCapacity * sizeof (T) );

//		if(newCapacity < m_Size)
//			m_Size = newCapacity;

//		for(size_t i = 0; i < m_Size; i++)
//			newBlock[i] = std::move(m_Data[i]);

//		for(size_t i = 0; i < m_Size; i++)
//			m_Data[i].~T();

//		::operator delete( m_Data,m_Capacity * sizeof (T));
		m_Data = reinterpret_cast<T *>(newBlock);
		m_Capacity = newCapacity;
	}
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};
#endif // custom_allocator_H
