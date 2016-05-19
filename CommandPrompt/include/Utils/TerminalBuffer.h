#ifndef TerminalBuffer_h_
#define TerminalBuffer_h_

template <typename T>
class TerminalBuffer
{
public:
	TerminalBuffer(unsigned int width, unsigned int linesCount);
	~TerminalBuffer();

	void Push(const T & elem);
	void Push(const T * elem, unsigned int len);
	void Erase();
	void NewLine();
	void MoveBack();
	void SetPosition(unsigned int x, unsigned int y);
	void Set(const T & elem, unsigned int x, unsigned int y);
	unsigned int GetWidth() const;
	unsigned int GetLinesCount() const;
	T * GetLineStr(unsigned int index) const;
	unsigned int GetCursorX() const;
	unsigned int GetCursorY() const;

protected:
	unsigned int m_Width;
	unsigned int m_LinesCount;
	T ** m_LinesArray;
	unsigned int m_CurrentLineIndex;
	unsigned int m_CurrentCharIndex;
};

#include "TerminalBuffer.inl"

#endif
