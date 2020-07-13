#include "rtpch.h"
#include "BufferLayout.h"

void BufferLayout::addBufferElement(const BufferElement& element)
{
	bufferElements.push_back(element);
	calcStrideOffset();
}

const std::vector<BufferElement>& BufferLayout::getElements()
{
	return bufferElements;
}

void BufferLayout::calcStrideOffset()
{
	size_t offset = 0;
	stride = 0;
	for (auto& elem : bufferElements)
	{
		elem.offset = offset;
		offset += elem.size;
		stride += elem.size;
	}
}
