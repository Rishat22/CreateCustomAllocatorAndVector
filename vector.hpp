#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>
#include "vector_iterator.hpp"

template <typename T, typename Allocator = std::allocator<T>>
class Vector
{
	using iterator = VectorIterator<T>;
	using const_iterator = VectorIterator<const T>;
	using reverse_iterator =  VectorIterator<T>;
	using const_reverse_iterator =  VectorIterator<const T>;



public:
	Vector() = default;
	~Vector() = default;

	void PushBack(const T& value);
	void PushBack(const T&& value);
	const T& operator[](const size_t index) const;
	T& operator[](const size_t index);
	size_t Size() const;
	bool Empty() const;

	/* Iterators */
	iterator	begin() const { return iterator(&m_Data[0]); }
	iterator	end() const { return iterator(&m_Data[m_Size]); }
	const_iterator	cbegin() const { return const_iterator(&m_Data[0]);}
	const_iterator	cend() const { return const_iterator(&m_Data[m_Size]);}

private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
	Allocator m_Allocator;
};

template <typename T, typename A>
void Vector<T, A>::PushBack(const T& value)
{
	if(m_Data == nullptr)
	{
		m_Data = m_Allocator.allocate(size_t(1));
		m_Allocator.construct(m_Data);
//		m_Data = new (memBlock) T( std::move(value));
	}
	m_Data[m_Size++] = value;
}

template <typename T, typename A>
void Vector<T, A>::PushBack(const T&& value)
{
	if(m_Data == nullptr)
	{
		m_Data = m_Allocator.allocate(size_t(1));
		m_Allocator.construct(m_Data);
//		m_Data = new (memBlock) T( std::move(value));
	}
	m_Data[m_Size++] = value;
}

template <typename T, typename A>
const T& Vector<T, A>::operator[](const size_t index) const
{
	if(index >= m_Size)
	{
		//assert
	}
	return m_Data[index];
}

template <typename T, typename A>
T& Vector<T, A>::operator[](const size_t index)
{
	if(index >= m_Size)
	{
		//assert
	}
	return m_Data[index];
}

template <typename T, typename A>
size_t Vector<T, A>::Size() const
{
	return m_Size;
}

template <typename T, typename A>
bool Vector<T, A>::Empty() const
{
	return m_Size == 0;
}

#endif // VECTOR_H
