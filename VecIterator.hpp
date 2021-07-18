#ifndef VECITERATOR_H
#define VECITERATOR_H
#include <algorithm>

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

	VecIterator<lDataType>&	operator=(const VecIterator<lDataType>& rawIterator) = default;
	VecIterator<lDataType>&	operator=(lDataType* ptr){m_Ptr = ptr;return (*this);}

	operator bool() const
	{
		if(m_Ptr)
			return true;
		else
			return false;
	}

	bool operator==(const VecIterator<lDataType>& rawIterator) const {return (m_Ptr == rawIterator.getConstPtr());}
	bool operator!=(const VecIterator<lDataType>& rawIterator) const {return (m_Ptr != rawIterator.getConstPtr());}

	VecIterator<lDataType>&	operator+=(const difference_type& movement) {m_Ptr += movement;return (*this);}
	VecIterator<lDataType>&	operator-=(const difference_type& movement) {m_Ptr -= movement;return (*this);}
	VecIterator<lDataType>&	operator++() {++m_Ptr;return (*this);}
	VecIterator<lDataType>&	operator--() {--m_Ptr;return (*this);}
	VecIterator<lDataType>	operator++(int) {auto temp(*this);++m_Ptr;return temp;}
	VecIterator<lDataType>	operator--(int) {auto temp(*this);--m_Ptr;return temp;}
	VecIterator<lDataType>	operator+(const difference_type& movement)
	{auto oldPtr = m_Ptr;m_Ptr+=movement;auto temp(*this);m_Ptr = oldPtr;return temp;}
	VecIterator<lDataType>	operator-(const difference_type& movement)
	{auto oldPtr = m_Ptr;m_Ptr-=movement;auto temp(*this);m_Ptr = oldPtr;return temp;}

	difference_type	operator-(const VecIterator<lDataType>& rawIterator)
	{return std::distance(rawIterator.getPtr(),this->getPtr());}

	lDataType&	operator*() { return *m_Ptr; }
	const lDataType&	operator*() const { return *m_Ptr; }
	lDataType*	operator->() { return m_Ptr; }

	lDataType* getPtr()const{ return m_Ptr; }
	const lDataType* getConstPtr() const { return m_Ptr; }

protected:
	lDataType*	m_Ptr;
};
#endif // VECITERATOR_H
