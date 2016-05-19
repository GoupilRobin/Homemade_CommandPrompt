#include "Terminal.h"

#include "Window.h"
#include "FontSDL.h"
#include "TextSDL.h"
#include "Renderer.h"

Terminal::Terminal(Window * window, unsigned int historyLineCount, Font * font) :
	m_Buffer(0x0), m_Window(window), m_HistoryLineCount(historyLineCount), m_Font(font), m_NeedRedaw(true)
{
	m_ForegroundColor = Color::White;
	m_BackgroundColor = Color::Black;

	UpdateBufferSize();

	m_TextsArray = new Text *[m_Buffer->GetLinesCount()];
	for (unsigned int i = 0; i < m_Buffer->GetLinesCount(); ++i)
	{
		m_TextsArray[i] = new TextSDL(m_Font, m_Buffer->GetLineStr(i), m_ForegroundColor);
		m_TextsArray[i]->SetPosition(glm::vec2(0, m_Font->GetLineHeight() * i));
	}

	window->OnKeyDown.AddListener([this](char key, unsigned int timestamp) {
		m_NeedRedaw = true;
		if (key == '\n' || key == '\r')
		{
			m_Buffer->Push(0);
			m_Buffer->MoveBack();
			m_Buffer->NewLine();
		}
		else if (key == '\b')
		{
			m_Buffer->Push(0);
			m_Buffer->Erase();
			m_Buffer->Erase();
		}
		else if (key > 0 && ::isprint(key))
		{
			m_Buffer->Push(key);
		}
		else
		{
			m_NeedRedaw = false;
		}
	});
}

Terminal::~Terminal()
{
	for (unsigned int i = 0; i < m_Buffer->GetLinesCount(); ++i)
	{
		delete(m_TextsArray[i]);
	}
	delete(m_TextsArray);

	if (m_Buffer != 0x0)
	{
		delete(m_Buffer);
	}
}

void Terminal::Draw(Renderer * renderer)
{
	if (m_NeedRedaw)
	{
		m_Buffer->Push('_');
		m_Buffer->MoveBack();

		renderer->Clear(m_BackgroundColor);

		for (unsigned int i = 0; i < m_Buffer->GetLinesCount(); ++i)
		{
			m_TextsArray[i]->SetStr(m_Buffer->GetLineStr(i));
			renderer->Draw(m_TextsArray[i]);
		}
	}
}

void Terminal::UpdateBufferSize()
{
	if (m_Buffer != 0x0)
	{
		delete(m_Buffer);
	}

	glm::vec2 monoCharSize;
	m_Font->GetCharacterSize('0', monoCharSize);

	m_Buffer = new TerminalBuffer<char16_t>((unsigned int)(m_Window->GetWidth() / monoCharSize.x), (unsigned int)(m_Window->GetHeight() / monoCharSize.y));
}
