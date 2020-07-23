#pragma once
#include "Layer.h"
#include "lightbulb/core/OrthographicCamera.h"
#include "lightbulb/graphics/Renderer2D.h"

class Layer2D : public Layer
{
public:
	Layer2D(const std::string& name, int width, int height);
	virtual ~Layer2D();

	virtual void onEvent(const std::shared_ptr<event::Event>& evt) {}
	void onLayerEvent(const std::shared_ptr<event::Event>& evt) override;

	virtual void render() = 0;
	void renderLayer() override;

protected:
	std::shared_ptr<OrthographicCamera> camera;
	std::unique_ptr<Renderer2D> renderer;
};

