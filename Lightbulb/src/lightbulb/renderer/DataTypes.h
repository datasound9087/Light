#pragma once
#include "lbpch.h"

struct DataTypes
{
	enum class Types
	{
		Bool = 0,
		uByte, Byte,
		Float, Float2, Float3, Float4, 
		Int, Int2, Int3, Int4,
		uInt,
		Mat3, Mat4
	};

	static uint32_t getSize(const Types& type);
	static uint32_t getComponentCount(const Types& type);
};
