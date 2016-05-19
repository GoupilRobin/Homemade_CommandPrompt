#ifndef RingBuffer_h_
#define RingBuffer_h_

template <typename T>
class RingBuffer
{
public:
	RingBuffer(unsigned int size = 512);
	~RingBuffer();

	void Push(const T & content);
	void Push(const T * content, unsigned int len);
	// Reset the content
	void Resize(unsigned int size);
	const T * GetStr();

protected:
	unsigned int m_Size;
	T * m_Buffer;
	T * m_Begin;
	T * m_End;
	T * m_Str;
};

#include "RingBuffer.inl"

#endif