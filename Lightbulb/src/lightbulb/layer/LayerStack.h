#pragma once
#include "Layer.h"
#include "lightbulb/event/Event.h"

class LayerStack
{
public:
	LayerStack() = default;
	~LayerStack();
	void pushLayer(const std::shared_ptr<Layer>& layer);
	void pop();
	void onEvent(const std::shared_ptr<event::Event>& evt);
	void update();
	void render();

	std::shared_ptr<Layer>& getOverlay() { return overlay; }
	void setOverlay(const std::shared_ptr<Layer>& overlay);

private:
	std::vector<std::shared_ptr<Layer>> layerStack;
	std::shared_ptr<Layer> overlay;
};

