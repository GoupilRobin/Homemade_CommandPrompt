#ifndef Font_h_
#define Font_h_

#include <glm/vec2.hpp>

class Font
{
public:
	Font(char * path, unsigned int size) : m_Bold(false), m_Italic(false), m_Underline(false), m_StrikeThrough(false) {}
	virtual ~Font() {}

	virtual void SetSize(unsigned int size) { m_Size = size; }
	virtual void SetBold(bool status) { m_Bold = status; }
	virtual void SetItalic(bool status) { m_Italic = status; }
	virtual void SetUnderline(bool status) { m_Underline = status; }
	virtual void SetStrikeThrough(bool status) { m_StrikeThrough = status; }
	virtual unsigned int GetSize() { return m_Size; }
	virtual bool GetBold() { return m_Bold; }
	virtual bool GetItalic() { return m_Italic; }
	virtual bool GetUnderline() { return m_Underline; }
	virtual bool GetStrikeThrough() { return m_StrikeThrough; }
	virtual void GetCharacterSize(const char & c, glm::vec2 & size) = 0;
	virtual unsigned int GetLineHeight() { return m_LineHeight; }

protected:
	unsigned int m_Size;
	bool m_Bold;
	bool m_Italic;
	bool m_Underline;
	bool m_StrikeThrough;
	unsigned int m_LineHeight;
};

#endif