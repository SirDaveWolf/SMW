#include "Dummy.h"
#include "IncludeGL.h"

SMW::Dummy::Dummy(const RenderOptions& renderOptions)
	: BaseEntity(renderOptions)
{
	_body = Rectangle<float>(0.0f, 0.0f, _renderOptions.BaseEntityWidth, _renderOptions.BaseEntityHeight);
	_xVelocity = 1.0f;
	_yVelocity = 1.0f;
}

SMW::Dummy::Dummy(const RenderOptions& renderOptions, const Point<float>& initialPosition)
	: BaseEntity(renderOptions)
{
	_body = Rectangle<float>(initialPosition, _renderOptions.BaseEntityWidth, _renderOptions.BaseEntityHeight);
	_xVelocity = 1.0f;
	_yVelocity = 1.0f;
}

void SMW::Dummy::Render()
{
	glBegin(GL_QUADS);
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(_body.TopLeft().X, _body.TopLeft().Y, 0);
		glVertex3f(_body.TopRight().X, _body.TopRight().Y, 0);
		glVertex3f(_body.BottomRight().X, _body.BottomRight().Y, 0);
		glVertex3f(_body.BottomLeft().X, _body.BottomLeft().Y, 0);
	}
	glEnd();
}

void SMW::Dummy::Think(const std::vector<BaseEntity*>& dummies)
{
	_body.X += _xVelocity;
	if (_body.TopLeft().X < 0 || _body.TopRight().X > _renderOptions.ScreenWidth)
		_xVelocity *= -1.0f;

	_body.Y += _yVelocity;
	if (_body.TopLeft().Y < 0 || _body.BottomLeft().Y > _renderOptions.ScreenHeight)
		_yVelocity *= -1.0f;

	for (auto checkEntity : dummies)
	{
		if (this != checkEntity)
		{
			auto dummy = (Dummy*)checkEntity;
			if (_body.CheckCollisionWith(dummy->_body, _xVelocity, _yVelocity))
			{
				_xVelocity *= -1.0f;
			}
		}
	}
}