#include "lbpch.h"
#include "ImGuiLayer.h"

#include <imgui/imgui.h>
#include "ImGuiBuild.h"
#include "lightbulb/App.h"

void ImGuiLayer::init()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	imguiBuild::init();
}

void ImGuiLayer::onLayerEvent(const std::shared_ptr<event::Event>& evt)
{
	ImGuiIO& io = ImGui::GetIO();
	
	if (evt->getEventType() == event::EventType::WindowResized)
	{
		auto win = App::getApp().getWindow();
		io.DisplaySize = ImVec2((float)win->getWidth(), (float)win->getHeight());
	}
}

void ImGuiLayer::renderLayer()
{
	imguiBuild::begin();
	ImGui::NewFrame();
	render();
	imguiBuild::end();
	ImGui::Render();
	imguiBuild::render();
}

void ImGuiLayer::shutdown()
{
	imguiBuild::shutdown();
	ImGui::DestroyContext();
}
