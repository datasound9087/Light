#pragma once
#include "Layer.h"
#include "lightbulb/core/ICamera.h"
#include "lightbulb/graphics/Renderer2D.h"

class Layer2D : public Layer
{
public:
	Layer2D(const std::string& name, const std::shared_ptr<OrthographicCamera>& camera);
	virtual ~Layer2D();

	virtual void render() = 0;
	void renderLayer() override;
protected:
	std::unique_ptr<Renderer2D> renderer;
};

