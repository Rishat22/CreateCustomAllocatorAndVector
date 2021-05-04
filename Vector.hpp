#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>
#include <algorithm>
#include <utility>

template<typename lDataType>
class VecIterator
{
public:

	using iterator_category = std::random_access_iterator_tag;
	using value_type = lDataType;
	using difference_type = std::ptrdiff_t;
	using pointer = lDataType*;
	using reference = lDataType&;

public:

	VecIterator(lDataType* ptr = nullptr){m_Ptr = ptr;}
	VecIterator(const VecIterator<lDataType>& rawIterator) = default;
	~VecIterator() = default;

	VecIterator<lDataType>&                  operator=(const VecIterator<lDataType>& rawIterator) = default;
	VecIterator<lDataType>&                  operator=(lDataType* ptr){m_Ptr = ptr;return (*this);}

	operator                                    bool()const
	{
		if(m_Ptr)
			return true;
		else
			return false;
	}

	bool                                        operator==(const VecIterator<lDataType>& rawIterator)const{return (m_Ptr == rawIterator.getConstPtr());}
	bool                                        operator!=(const VecIterator<lDataType>& rawIterator)const{return (m_Ptr != rawIterator.getConstPtr());}

	VecIterator<lDataType>&                  operator+=(const difference_type& movement){m_Ptr += movement;return (*this);}
	VecIterator<lDataType>&                  operator-=(const difference_type& movement){m_Ptr -= movement;return (*this);}
	VecIterator<lDataType>&                  operator++(){++m_Ptr;return (*this);}
	VecIterator<lDataType>&                  operator--(){--m_Ptr;return (*this);}
	VecIterator<lDataType>                   operator++(int){auto temp(*this);++m_Ptr;return temp;}
	VecIterator<lDataType>                   operator--(int){auto temp(*this);--m_Ptr;return temp;}
	VecIterator<lDataType>                   operator+(const difference_type& movement){auto oldPtr = m_Ptr;m_Ptr+=movement;auto temp(*this);m_Ptr = oldPtr;return temp;}
	VecIterator<lDataType>                   operator-(const difference_type& movement){auto oldPtr = m_Ptr;m_Ptr-=movement;auto temp(*this);m_Ptr = oldPtr;return temp;}

	difference_type                             operator-(const VecIterator<lDataType>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

	lDataType&                                 operator*(){return *m_Ptr;}
	const lDataType&                           operator*()const{return *m_Ptr;}
	lDataType*                                 operator->(){return m_Ptr;}

	lDataType*                                 getPtr()const{return m_Ptr;}
	const lDataType*                           getConstPtr()const{return m_Ptr;}

protected:

	lDataType*                                 m_Ptr;
};

template <typename T, typename A = std::allocator<T>>
class Vector
{
	using iterator = VecIterator<T>;
	using const_iterator = VecIterator<const T>;
	using reverse_iterator =  VecIterator<T>;
	using const_reverse_iterator =  VecIterator<const T>;

	/* How to implement it correctly here */
//	typename std::allocator_traits<A>::pointer allocData;

public:
	Vector()
	{
		ReAlloc(2);
	}

	/* How to implement it correctly here */
//	Vector(A allocator)
//		:	m_Allocator(allocator)
//	{
//		allocData = std::allocator_traits<A>::allocate(m_Allocator, 1);
//		std::allocator_traits<A>::construct(m_Allocator, allocData, ?);
//	}
	~Vector();

	void Clear();
	void PushBack(const T& value);
	void PushBack(const T&& value);
	const T& operator[](const size_t index) const;
	T& operator[](const size_t index);
	size_t Size() const;
	bool Empty() const;

	/* Iterators */
	iterator			begin() const { return iterator(&m_Data[0]); }
	iterator			end() const { return iterator(&m_Data[m_Size]); }
	const_iterator	cbegin() const { return const_iterator(&m_Data[0]);}
	const_iterator	cend() const { return const_iterator(&m_Data[m_Size]);}

private:
	void ReAlloc(const size_t newCapacity);
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
	A m_Allocator;
};

template <typename T, typename A>
Vector<T, A>::~Vector()
{
	/* How to implement it correctly here */
//	std::allocator_traits<A>::destroy(m_Allocator, allocData);
//	std::allocator_traits<A>::deallocate(m_Allocator, allocData, 1);
	Clear();
	::operator delete( m_Data, m_Capacity * sizeof (T) );
}

template <typename T, typename A>
void Vector<T, A>::Clear()
{
	for(size_t i = 0; i < m_Size; i++)
		m_Data[i].~T();
}

template <typename T, typename A>
void Vector<T, A>::PushBack(const T& value)
{
	if(m_Size >= m_Capacity)
		ReAlloc(m_Capacity + m_Capacity /2);

	m_Data[m_Size] = value;
	m_Size++;
}

template <typename T, typename A>
void Vector<T, A>::PushBack(const T&& value)
{
	if(m_Size >= m_Capacity)
		ReAlloc(m_Capacity + m_Capacity /2);

	m_Data[m_Size] = std::move(value);
	m_Size++;
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

template <typename T, typename A>
void Vector<T, A>::ReAlloc(const size_t newCapacity)
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

#endif // VECTOR_H