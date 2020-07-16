#pragma once
class GraphicsContext
{
public:
	static std::unique_ptr<GraphicsContext> create(void* window);

	virtual ~GraphicsContext() = default;
	virtual void init() = 0;
	virtual void swapBuffers() = 0;
};

