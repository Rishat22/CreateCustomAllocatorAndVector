#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H
#include <algorithm>

template<typename lDataType>
class VectorIterator
{
public:

	using iterator_category = std::random_access_iterator_tag;
	using value_type = lDataType;
	using difference_type = std::ptrdiff_t;
	using pointer = lDataType*;
	using reference = lDataType&;

public:

	VectorIterator(lDataType* ptr = nullptr){m_Ptr = ptr;}
	VectorIterator(const VectorIterator<lDataType>& rawIterator) = default;
	~VectorIterator() = default;

	VectorIterator<lDataType>&	operator=(const VectorIterator<lDataType>& rawIterator) = default;
	VectorIterator<lDataType>&	operator=(lDataType* ptr){m_Ptr = ptr;return (*this);}

	operator bool() const
	{
		if(m_Ptr)
			return true;
		else
			return false;
	}

	bool operator==(const VectorIterator<lDataType>& rawIterator) const {return (m_Ptr == rawIterator.getConstPtr());}
	bool operator!=(const VectorIterator<lDataType>& rawIterator) const {return (m_Ptr != rawIterator.getConstPtr());}

	VectorIterator<lDataType>&	operator+=(const difference_type& movement) {m_Ptr += movement;return (*this);}
	VectorIterator<lDataType>&	operator-=(const difference_type& movement) {m_Ptr -= movement;return (*this);}
	VectorIterator<lDataType>&	operator++() {++m_Ptr;return (*this);}
	VectorIterator<lDataType>&	operator--() {--m_Ptr;return (*this);}
	VectorIterator<lDataType>	operator++(int) {auto temp(*this);++m_Ptr;return temp;}
	VectorIterator<lDataType>	operator--(int) {auto temp(*this);--m_Ptr;return temp;}
	VectorIterator<lDataType>	operator+(const difference_type& movement)
	{auto oldPtr = m_Ptr;m_Ptr+=movement;auto temp(*this);m_Ptr = oldPtr;return temp;}
	VectorIterator<lDataType>	operator-(const difference_type& movement)
	{auto oldPtr = m_Ptr;m_Ptr-=movement;auto temp(*this);m_Ptr = oldPtr;return temp;}

	difference_type	operator-(const VectorIterator<lDataType>& rawIterator)
	{return std::distance(rawIterator.getPtr(),this->getPtr());}

	lDataType&	operator*() { return *m_Ptr; }
	const lDataType&	operator*() const { return *m_Ptr; }
	lDataType*	operator->() { return m_Ptr; }

	lDataType* getPtr()const{ return m_Ptr; }
	const lDataType* getConstPtr() const { return m_Ptr; }

protected:
	lDataType*	m_Ptr;
};
#endif // VECTOR_ITERATOR_H
