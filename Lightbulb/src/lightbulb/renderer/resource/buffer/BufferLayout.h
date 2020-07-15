#pragma once
#include "BufferElement.h"

class BufferLayout
{
public:
	BufferLayout();
	BufferLayout(const std::initializer_list<BufferElement>& elements);
	void addBufferElement(const BufferElement& element);
	void addBufferElements(const std::initializer_list<BufferElement>& elements);
	const std::vector<BufferElement>& getElements();
	size_t getStride() const { return stride; }

private:
	void calcStrideOffset();

private:
	std::vector<BufferElement> bufferElements;
	size_t stride; //gap between consecutive vertex elements
};