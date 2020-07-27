#pragma once

#include "Layer.h"
#include "lightbulb/camera/CameraController.h"

class CameraLayer : public Layer
{
public:
	CameraLayer(const std::string& name, const std::shared_ptr<ICamera>& camera, bool canMove, bool canRotate, bool canScroll);

	virtual void onEvent(const std::shared_ptr<event::Event>& evt) = 0;
	void onLayerEvent(const std::shared_ptr<event::Event>& evt) override;
	virtual void update() = 0;
	void layerUpdate() override;

protected:
	std::unique_ptr<CameraController> camController;
};

