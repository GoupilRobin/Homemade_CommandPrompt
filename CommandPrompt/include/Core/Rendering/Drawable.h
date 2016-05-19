#ifndef Drawable_h_
#define Drawable_h_

class Renderer;

class Drawable
{
public:
	virtual ~Drawable() {}

	virtual void Draw(Renderer * renderer) = 0;
};

#endif