#pragma once
#include "RenderOptions.h"
#include <vector>

namespace SMW
{
	class BaseEntity
	{
	public:
		BaseEntity(const GameOptions&);
		virtual void Render() = 0;
		virtual void Think(const std::vector<BaseEntity*>&) = 0;

		virtual bool CollideWith(const BaseEntity&) = 0;

	protected:
		const GameOptions& _gameOptions;
	};
}

