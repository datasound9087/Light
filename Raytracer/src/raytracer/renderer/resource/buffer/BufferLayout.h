#pragma once
#include "BufferElement.h"

class BufferLayout
{
public:
	void addBufferElement(const BufferElement& element);
	const std::vector<BufferElement>& getElements();
	uint32_t getStride() const { return stride; }

private:
	void calcStrideOffset();

private:
	std::vector<BufferElement> bufferElements;
	size_t stride; //gap between consecutive vertex elements
};