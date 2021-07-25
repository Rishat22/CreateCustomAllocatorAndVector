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
		free( m_Data );
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
		m_Size += n;
		if (m_Size > SIZE)
			throw std::out_of_range("Maximum number of elements must not exceed the specified value");
		return &m_Data[m_Size];
	}

	void deallocate(T *p, std::size_t n) {
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		new(p) U(std::forward<Args>(args)...);
	};

	void destroy(T *p) {
		p->~T();
	}

private:
	void ReAlloc(const size_t new_size)
	{
		auto newBlock = std::malloc(new_size * sizeof(T));
		if (newBlock == nullptr)
			throw std::bad_alloc();

		m_Data = reinterpret_cast<T *>(newBlock);
	}
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
};
#endif // custom_allocator_H
