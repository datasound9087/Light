#include "lbpch.h"
#include "DataTypes.h"

uint32_t DataTypes::getSize(const Types& type)
{
	constexpr uint32_t FLOAT_SIZE_BYTES = 4;
	constexpr uint32_t INT_SIZE_BYTES = 4;

	switch (type)
	{
	case Types::Bool: return 1;
	case Types::Byte: return 1;
	case Types::uByte: return 1;
	case Types::Float: return FLOAT_SIZE_BYTES;
	case Types::Float2: return 2 * FLOAT_SIZE_BYTES;
	case Types::Float3: return 3 * FLOAT_SIZE_BYTES;
	case Types::Float4: return 4 * FLOAT_SIZE_BYTES;
	case Types::Int: return INT_SIZE_BYTES;
	case Types::Int2: return 2 * INT_SIZE_BYTES;
	case Types::Int3: return 3 * INT_SIZE_BYTES;
	case Types::Int4: return 4 * INT_SIZE_BYTES;
	case Types::uInt: return INT_SIZE_BYTES;
	case Types::Mat3: return FLOAT_SIZE_BYTES * 3 * 3;
	case Types::Mat4: return FLOAT_SIZE_BYTES * 4 * 4;
	default:
		ERROR("Undefined size for {0}", type);
		return 0;
	}
}

uint32_t DataTypes::getComponentCount(const Types& type)
{
	switch (type)
	{
	case Types::Bool: return 1;
	case Types::Byte: return 1;
	case Types::uByte: return 1;
	case Types::Float: return 1;
	case Types::Float2: return 2;
	case Types::Float3: return 3;
	case Types::Float4: return 4;
	case Types::Int: return 1;
	case Types::Int2: return 2;
	case Types::Int3: return 3;
	case Types::Int4: return 4;
	case Types::uInt: return 1;
	case Types::Mat3: return 3;
	case Types::Mat4: return 4;
	default:
		ERROR("Undefined no. of components for {0}", type);
		return 0;
	}
}
