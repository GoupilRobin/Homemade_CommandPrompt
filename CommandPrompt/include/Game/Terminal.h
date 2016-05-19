#ifndef Terminal_h_
#define Terminal_h_

#include "TerminalBuffer.h"
#include "Drawable.h"
#include "Color.h"

class Window;
class Font;
class Text;

class Terminal : public Drawable
{
public:
	Terminal(Window * window, unsigned int historyLineCount, Font * font);
	~Terminal();
	void Draw(Renderer * renderer) override;

protected:
	void UpdateBufferSize();

	Window * m_Window;
	unsigned int m_HistoryLineCount;
	TerminalBuffer<char16_t> * m_Buffer;
	Font * m_Font;
	Color m_BackgroundColor;
	Color m_ForegroundColor;
	Text ** m_TextsArray;
	bool m_NeedRedaw;
};

#endif