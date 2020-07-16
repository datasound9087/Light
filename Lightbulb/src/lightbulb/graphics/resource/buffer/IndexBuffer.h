#pragma once
#include "lightbulb/graphics/resource/IGPUResource.h"

class IndexBuffer : public IGPUResource
{
public:
	static std::shared_ptr<IndexBuffer> create(uint32_t count, uint32_t* data);

	uint32_t getCount() const { return count; }

protected:
	uint32_t count;
};

