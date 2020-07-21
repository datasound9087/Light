#pragma once
#include "ImGuiLayer.h"
class DebugLayer : public ImGuiLayer
{
public:
	DebugLayer()
		: ImGuiLayer("Debug")
	{}
	void render() override;
};

