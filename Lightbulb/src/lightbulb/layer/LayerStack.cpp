#include "lbpch.h"
#include "LayerStack.h"

LayerStack::~LayerStack()
{
	while (layerStack.size() > 0)
	{
		auto layer = layerStack.back();
		layerStack.pop_back();
		layer->shutdown();
	}
}

void LayerStack::pushLayer(const std::shared_ptr<Layer>& layer)
{
	layer->init();
	if(layerStack.size() > 1) layerStack.back()->onMoveBack();
	layerStack.push_back(layer);
}

void LayerStack::pop()
{
	if (!layerStack.empty())
	{
		auto layer = layerStack.back();
		layerStack.pop_back();
		layerStack.back()->onMadeFront();
		layer->shutdown();
	}
}

void LayerStack::onEvent(const std::shared_ptr<event::Event>& evt)
{
	auto it = layerStack.rbegin();
	for (it; it != layerStack.rend(); it++)
	{
		auto layer = *it;
		layer->onLayerEvent(evt);
	}
}

void LayerStack::update()
{
	auto it = layerStack.rbegin();
	for (it; it != layerStack.rend(); it++)
	{
		auto layer = *it;
		layer->update();
	}
}

void LayerStack::render()
{
	auto it = layerStack.rbegin();
	for (it; it != layerStack.rend(); it++)
	{
		auto layer = *it;
		layer->renderLayer();
	}
}
