#pragma once
#include "Layer.h"

class LayerStack
{
public:
	~LayerStack();
	void pushLayer(const std::shared_ptr<Layer>& layer);
	void pop();
	void update();
	void render();
private:
	std::vector<std::shared_ptr<Layer>> layerStack;
};

