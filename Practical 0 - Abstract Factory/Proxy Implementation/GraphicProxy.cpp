#include "GraphicProxy.h"

GraphicProxy::GraphicProxy()
{
	this->graphic = nullptr;
}

GraphicProxy::~GraphicProxy()
{
	if (graphic)
		delete graphic;
}

Graphic* GraphicProxy::getInstance(void)
{
	if (!graphic)
		graphic = new Graphic();
	return graphic;
}

void GraphicProxy::draw()
{
	getInstance()->draw();
}