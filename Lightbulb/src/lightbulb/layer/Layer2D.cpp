#include "lbpch.h"
#include "Layer2D.h"

Layer2D::Layer2D(const std::string& name, const std::shared_ptr<OrthographicCamera>& camera)
	: Layer(name)
{
	renderer = std::make_unique<Renderer2D>(camera);
}

Layer2D::~Layer2D()
{
}

void Layer2D::renderLayer()
{
	renderer->beginScene();
	render();
	renderer->endScene();
	renderer->flush();
}
