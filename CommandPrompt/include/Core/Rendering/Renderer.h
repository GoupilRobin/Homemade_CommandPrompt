#ifndef Renderer_h_
#define Renderer_h_

class Window;
class Color;
class Text;
class Drawable;

class Renderer
{
public:
	Renderer(Window * window) : m_WindowPtr(window) {}
	virtual ~Renderer() {}
	virtual void Clear(const Color & color) = 0;
	virtual void Draw(Drawable * text) = 0;
	virtual void Render() = 0;
	virtual Window * GetWindowPtr() { return m_WindowPtr; }

protected:
	Window * m_WindowPtr;
};

#endif