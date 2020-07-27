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

	if (overlay != nullptr) overlay->onLayerEvent(evt);
}

void LayerStack::update()
{
	auto it = layerStack.rbegin();
	for (it; it != layerStack.rend(); it++)
	{
		auto layer = *it;
		layer->layerUpdate();
	}

	if (overlay != nullptr) overlay->layerUpdate();
}

void LayerStack::tick()
{
	auto it = layerStack.rbegin();
	for (it; it != layerStack.rend(); it++)
	{
		auto layer = *it;
		layer->layerTick();
	}

	if (overlay != nullptr) overlay->layerTick();
}

void LayerStack::render()
{
	auto it = layerStack.begin();
	for (it; it != layerStack.end(); it++)
	{
		auto layer = *it;
		if(layer->isVisible())
			layer->renderLayer();
	}

	if (overlay != nullptr && overlay->isVisible()) overlay->renderLayer();
}

void LayerStack::setOverlay(const std::shared_ptr<Layer>& overlay)
{
	if (this->overlay != nullptr)
	{
		overlay->shutdown();
	}

	this->overlay = overlay;
	this->overlay->init();
}
