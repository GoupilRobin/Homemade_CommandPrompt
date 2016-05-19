#ifndef Renderer_SDL
#define Renderer_SDL

#include "Renderer.h"
#include "Color.h"

class WindowSDL;
struct SDL_Renderer;
class TextSDL;
class TextLineSDL;

class RendererSDL : public Renderer
{
public:
	RendererSDL(Window * window);
	~RendererSDL();
	void Clear(const Color & color) override;
	void Draw(Drawable * drawable) override;
	void Render() override;

protected:
	SDL_Renderer * m_Renderer;
	Color m_PreviousColor;

	friend TextSDL;
	friend TextLineSDL;
};

#endif