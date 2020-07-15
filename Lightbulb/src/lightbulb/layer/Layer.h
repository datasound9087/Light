#pragma once
#include "lbpch.h"
#include "lightbulb/event/Event.h"

class Layer
{
public:
	Layer(const std::string& name)
		: name(name)
	{}
	virtual ~Layer() = default;

	//on added to stack - run once
	virtual void init() {}
	//on made front of stack
	virtual void onMadeFront() {}
	//events
	virtual void onEvent(const std::shared_ptr<event::Event>& evt) {}
	//updates
	virtual void update() = 0;
	//render
	virtual void renderLayer() = 0;
	//on move back in layer stack
	virtual void onMoveBack() {}
	//on removed from stack
	virtual void shutdown() {}

	void setName(const std::string& name) { this->name = name; }
	const std::string& getName()  const { return name; }

protected:
	std::string name;
};