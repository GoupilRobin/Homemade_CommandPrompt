#ifndef Color_h_
#define Color_h_

class Color
{
public:
	Color();
	Color(float r, float g, float b, float a = 1.0f);
	~Color();

	void SetRed(float r);
	void SetGreen(float g);
	void SetBlue(float b);
	void SetAlpha(float a);
	void SetColor(float r, float g, float b, float a = 1.0f);

	float GetRed() const;
	float GetGreen() const;
	float GetBlue() const;
	float GetAlpha() const;

	bool operator== (const Color & rhs) const;
	bool operator!= (const Color & rhs) const;

protected:
	float m_R;
	float m_G;
	float m_B;
	float m_A;

public:
	static Color White;
	static Color Black;
	static Color Red;
	static Color Blue;
	static Color Green;
	static Color Transparent;
};

#endif