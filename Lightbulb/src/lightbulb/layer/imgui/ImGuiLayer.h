#pragma once

#include "lightbulb/layer/Layer.h"
class ImGuiLayer : public Layer
{
public:
	ImGuiLayer(const std::string& name)
		: Layer(name)
	{}
	void init() override;
	virtual void onLayerEvent(const std::shared_ptr<event::Event>& evt) override;
	virtual void layerUpdate() override {}
	virtual void render() = 0;
	virtual void renderLayer() override;
	virtual void shutdown() override;
};

