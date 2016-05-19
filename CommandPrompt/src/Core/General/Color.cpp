#include "Color.h"

Color::Color() : Color(0.0f, 0.0f, 0.0f, 1.0)
{
}

Color::Color(float r, float g, float b, float a /*= 1.0f*/) : m_R(r), m_G(g), m_B(b), m_A(a)
{
}

Color::~Color()
{
}

void Color::SetRed(float r)
{
	m_R = r;
}

void Color::SetGreen(float g)
{
	m_G = g;
}

void Color::SetBlue(float b)
{
	m_B = b;
}

void Color::SetAlpha(float a)
{
	m_A = a;
}

void Color::SetColor(float r, float g, float b, float a /*= 1.0f*/)
{
	m_R = r;
	m_G = g;
	m_B = b;
	m_A = a;
}

float Color::GetRed() const
{
	return m_R;
}

float Color::GetGreen() const
{
	return m_G;
}

float Color::GetBlue() const
{
	return m_B;
}

float Color::GetAlpha() const
{
	return m_A;
}

bool Color::operator==(const Color & rhs) const
{
	return m_R == rhs.m_R && m_G == rhs.m_G && m_B == rhs.m_B && m_A == rhs.m_A;
}

bool Color::operator!=(const Color & rhs) const
{
	return !operator==(rhs);
}

Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);
Color Color::Black(0.0f, 0.0f, 0.0f, 0.0f);
Color Color::Red(1.0f, 0.0f, 0.0f, 1.0f);
Color Color::Blue(0.0f, 1.0f, 0.0f, 1.0f);
Color Color::Green(0.0f, 0.0f, 0.0f, 1.0f);
Color Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);