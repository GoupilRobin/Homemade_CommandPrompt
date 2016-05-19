#ifndef TerminalBuffer_inl_
#define TerminalBuffer_inl_

#include "TerminalBuffer.h"
#include <cstring>

template<typename T>
TerminalBuffer<T>::TerminalBuffer(unsigned int width, unsigned int linesCount) :
	m_Width(width), m_LinesCount(linesCount)
{
	m_LinesArray = new T * [m_LinesCount];
	for (unsigned int i = 0; i < m_LinesCount; ++i)
	{
		m_LinesArray[i] = new T[m_Width + 1];
		memset(m_LinesArray[i], 0, (m_Width + 1) * sizeof(T));
	}

	m_CurrentLineIndex = 0;
	m_CurrentCharIndex = 0;
}

template<typename T>
TerminalBuffer<T>::~TerminalBuffer()
{
	for (unsigned int i = 0; i < m_LinesCount; ++i)
	{
		delete[] m_LinesArray[i];
	}
	delete[] m_LinesArray;
}

template<typename T>
void TerminalBuffer<T>::Push(const T & elem)
{
	m_LinesArray[m_CurrentLineIndex][m_CurrentCharIndex] = elem;
	m_CurrentCharIndex++;
	m_LinesArray[m_CurrentLineIndex][m_CurrentCharIndex] = 0;
	if (m_CurrentCharIndex >= m_Width)
	{
		NewLine();
	}
}

template<typename T>
void TerminalBuffer<T>::Push(const T * elem, unsigned int len)
{
	for (unsigned int i = 0; i < len; ++i)
	{
		Push(elem[i]);
	}
}

template<typename T>
void TerminalBuffer<T>::Erase()
{
	MoveBack();
	Push(0);
	MoveBack();
}

template<typename T>
void TerminalBuffer<T>::NewLine()
{
	m_CurrentCharIndex = 0;
	m_CurrentLineIndex++;
	if (m_CurrentLineIndex >= m_LinesCount)
	{
		// Move each line one position up
		for (unsigned int i = 0; i < m_LinesCount - 1; ++i)
		{
			memcpy_s(m_LinesArray[i], (m_Width + 1) * sizeof(T), m_LinesArray[i + 1], (m_Width + 1) * sizeof(T));
		}
		// Memset the last line so we can write on it again
		memset(m_LinesArray[m_LinesCount - 1], 0, (m_Width + 1) * sizeof(T));
		m_CurrentLineIndex = m_LinesCount - 1;
	}
}

template<typename T>
void TerminalBuffer<T>::MoveBack()
{
	if (m_CurrentCharIndex > 0)
	{
		SetPosition(m_CurrentCharIndex - 1, m_CurrentLineIndex);
	}
	else if (m_CurrentLineIndex > 0)
	{
		unsigned int lastCharIndex = 0;
		while (m_LinesArray[m_CurrentLineIndex - 1][lastCharIndex] != 0)
		{
			lastCharIndex++;
			// if the last line if full
			if (lastCharIndex == m_Width)
			{
				SetPosition(lastCharIndex - 1, m_CurrentLineIndex - 1);
				return;
			}
		}
		// we put the cursor just after the last character of the previous line
		SetPosition(lastCharIndex, m_CurrentLineIndex - 1);
	}
}

template<typename T>
void TerminalBuffer<T>::SetPosition(unsigned int x, unsigned int y)
{
	m_CurrentCharIndex = x;
	m_CurrentLineIndex = y;
}

template<typename T>
void TerminalBuffer<T>::Set(const T & elem, unsigned int x, unsigned int y)
{
	SetPosition(x, y);
	Push(elem);
}

template<typename T>
T * TerminalBuffer<T>::GetLineStr(unsigned int index) const
{
	return m_LinesArray[index];
}

template<typename T>
unsigned int TerminalBuffer<T>::GetCursorX() const
{
	return m_CurrentCharIndex;
}

template<typename T>
unsigned int TerminalBuffer<T>::GetCursorY() const
{
	return m_CurrentLineIndex;
}

template<typename T>
unsigned int TerminalBuffer<T>::GetWidth() const
{
	return m_Width;
}

template<typename T>
unsigned int TerminalBuffer<T>::GetLinesCount() const
{
	return m_LinesCount;
}

#endif
