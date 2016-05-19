#ifndef Text_h_
#define Text_h_

#include "Drawable.h"
#include "glm/vec2.hpp"
#include "Color.h"
#include "ustring.h"

class Font;

class Text : public Drawable
{
public:
	enum Alignment
	{
		Left = 0,
		Center = 1,
		Right = 2,
	};

public:
	Text(Font * font, const char16_t * str = 0x0, const Color & color = Color::White, bool smooth = true) :
		m_Font(font), m_Str(u""), m_Color(color), m_Position(glm::vec2(0.0f, 0.0f)), m_Scale(glm::vec2(1.0f, 1.0f)), m_Alignment(Alignment::Left), m_Smooth(smooth) { SetStr(str); }
	virtual ~Text() {}

	virtual void SetFont(Font * font) { m_Font = font; }
	virtual void SetStr(const char16_t * str) { m_Str = str; }
	virtual void SetColor(const Color & color) { m_Color = color; }
	virtual void SetPosition(const glm::vec2 & position) { m_Position = position; }
	virtual void SetScale(const glm::vec2 & scale) { m_Scale = scale; }
	virtual void SetAlignment(const Alignment & alignment) { m_Alignment = alignment; }
	virtual void SetSmooth(const bool & smooth) { m_Smooth = smooth; }
	virtual Font * GetFont() { return m_Font; }
	virtual const char16_t * GetStr() { return m_Str; }
	virtual const Color & GetColor() { return m_Color; }
	virtual const glm::vec2 & GetPosition() { return m_Position; }
	virtual const glm::vec2 & GetSscale() { return m_Scale; }
	virtual const glm::vec2 & GetSize() { return m_Size; }
	virtual const Alignment & GetAlignment() { return m_Alignment; }
	virtual const bool & GetSmooth() { return m_Smooth; }

protected:
	Font * m_Font;
	const char16_t * m_Str;
	Color m_Color;
	glm::vec2 m_Position;
	glm::vec2 m_Scale;
	glm::vec2 m_Size;
	Alignment m_Alignment;
	bool m_Smooth;
};

#endif