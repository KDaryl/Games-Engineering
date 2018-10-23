#pragma once
#include "IGraphic.h"

class Graphic : public IGraphic
{
public:
	Graphic();
	~Graphic();
	void draw();
};