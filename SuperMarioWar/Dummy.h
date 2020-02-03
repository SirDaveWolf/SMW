#pragma once
#include "BaseEntity.h"
#include "Rectangle.h"

namespace SMW
{
	class Dummy : public BaseEntity
	{
	public:
		Dummy(const RenderOptions&);
		Dummy(const RenderOptions&, const Point<float>&);

		virtual void Render();
		virtual void Think(const std::vector<BaseEntity*>&);

	private:
		SMW::Rectangle<float> _body;
		float _xVelocity;
		float _yVelocity;
	};
}

