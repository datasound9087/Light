#include "lbpch.h"
#include "BufferLayout.h"

BufferLayout::BufferLayout()
{
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
{
	addBufferElements(elements);
}

void BufferLayout::addBufferElement(const BufferElement& element)
{
	bufferElements.push_back(element);
	calcStrideOffset();
}

void BufferLayout::addBufferElements(const std::initializer_list<BufferElement>& elements)
{
	for (auto& elem : elements)
	{
		bufferElements.push_back(elem);
	}

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
