#pragma once
#include "RenderOptions.h"
#include <vector>

namespace SMW
{
	class BaseEntity
	{
	public:
		BaseEntity(const RenderOptions&);
		virtual void Render() = 0;
		virtual void Think(const std::vector<BaseEntity*>&) = 0;

	protected:
		const RenderOptions& _renderOptions;
	};
}

