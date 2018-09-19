#pragma once
#include "Graphic.h"

class GraphicProxy : public IGraphic
{
public:
	GraphicProxy();
	~GraphicProxy();
	void draw();

private:
	Graphic * graphic;
	Graphic* getInstance(void);
};