#pragma once
#include "raytracer/renderer/resource/IGPUResource.h"
#include "BufferLayout.h"
#include "raytracer/renderer/DataTypes.h"

class VertexBuffer : public IGPUResource
{
public:
	enum class Usage
	{
		STATIC = 0,
		DYNAMIC
	};
	Usage getUsage() const { return usage; }

	static std::shared_ptr<VertexBuffer> create(const DataTypes::Types& type, size_t size, const Usage& usage);
	static std::shared_ptr<VertexBuffer> create(const DataTypes::Types& type, size_t size, void* data, const Usage& usage);

	virtual void setData(const std::unique_ptr<void>& data, size_t size) = 0;
	size_t getSize() const { return size; }
	const BufferLayout& getLayout() const { return layout; }
	void setBufferLayout(const BufferLayout& layout) { this->layout = layout; }

protected:
	Usage usage;
	DataTypes::Types type;
	size_t size;

private:
	BufferLayout layout;
};

