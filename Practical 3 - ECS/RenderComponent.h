#pragma once
#include <SDL.h>
#include "Component.h"
#include <iostream>

class RenderComponent : public Component
{
public:
	RenderComponent() { }
	void setRect(int x, int y, int w, int h) { m_rect.x = x, m_rect.y = y, m_rect.w = w, m_rect.h = h; }
	void setColor(int r, int g, int b) { m_color.r = r, m_color.g = g, m_color.b = b; }
	SDL_Rect* getRec() { return &m_rect; }
	SDL_Color& getColor() { return m_color; }
private:
	SDL_Rect m_rect;
	SDL_Color m_color;
};