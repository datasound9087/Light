#pragma once

class IGPUResource
{
public:

	virtual ~IGPUResource() = default;
	virtual void bind() = 0;
	virtual void unBind() = 0;
};