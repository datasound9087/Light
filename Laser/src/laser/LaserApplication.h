#pragma once
#include <lightbulb/Lightbulb.h>

class LaserApplication : public App
{
public:
	LaserApplication();
	virtual ~LaserApplication();

	void init() override;
	void update() override;
	void render() override;
	void onEvent(const std::unique_ptr<event::Event>& event) override;
	void shutdown() override;

private:
	std::unique_ptr<Renderer2D> renderer;
	std::shared_ptr<Texture2D> testTexture;
};

