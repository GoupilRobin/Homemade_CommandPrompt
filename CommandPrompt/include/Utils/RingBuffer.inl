#ifndef RingBuffer_inl_
#define RingBuffer_inl_

#include "RingBuffer.h"

template <typename T>
RingBuffer<T>::RingBuffer(unsigned int size = 512) :
	m_Size(0), m_Buffer(0x0), m_Begin(0x0), m_End(0x0), m_Str(0x0)
{
	Resize(size);
}

template <typename T>
RingBuffer<T>::~RingBuffer()
{
	if (m_Buffer != 0x0)
	{
		delete[] m_Buffer;
	}

	if (m_Str != 0x0)
	{
		delete[] m_Str;
	}
}

template<typename T>
void RingBuffer<T>::Push(const T & content)
{
	*m_End = content;
	m_End++;
	// loop m_End back to m_Buffer if out of bounds
	if (m_End - m_Buffer >= m_Size)
	{
		m_End = m_Buffer;
	}
	// push m_Begin when at the same position as m_End
	if (m_End == m_Begin)
	{
		m_Begin = m_End + 1;
	}
	// loop m_Begin back to m_Buffer if out of bounds
	if (m_Begin - m_Buffer >= m_Size)
	{
		m_Begin = m_Buffer;
	}
	*m_End = 0;

	T * cursor = m_Begin;
	for (unsigned int i = 0; i < m_Size; ++i)
	{
		m_Str[i] = *cursor;
		cursor++;
		// loop cursor back to m_Buffer if out of bounds
		if (cursor - m_Buffer >= m_Size)
		{
			cursor = m_Buffer;
		}
	}
}

template<typename T>
void RingBuffer<T>::Push(const T * content, unsigned int len)
{
	for (int i = 0; i < len; ++i)
	{
		Push(content[i]);
	}
}

template<typename T>
void RingBuffer<T>::Resize(unsigned int size)
{
	m_Size = size;

	if (m_Buffer != 0x0)
	{
		delete[] m_Buffer;
	}

	if (m_Str != 0x0)
	{
		delete[] m_Str;
	}

	m_Buffer = new T[m_Size];
	m_Str = new T[m_Size];
	for (unsigned int i = 0; i < m_Size; i++)
	{
		m_Buffer[i] = 0;
		m_Str[i] = 0;
	}
	m_End = m_Begin = m_Buffer;
}

template<typename T>
const T * RingBuffer<T>::GetStr()
{
	return m_Str;
}

#endif