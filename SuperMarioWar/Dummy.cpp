#include "Dummy.h"
#include "IncludeGL.h"

SMW::Dummy::Dummy(const GameOptions& renderOptions)
	: BaseEntity(renderOptions)
{
	_body = Rectangle<float>(0.0f, 0.0f, _gameOptions.BaseEntityWidth, _gameOptions.BaseEntityHeight);
	_xVelocity = 1.0f;
	_yVelocity = 1.0f;
}

SMW::Dummy::Dummy(const GameOptions& gameOptions, const Point<float>& initialPosition)
	: BaseEntity(gameOptions)
{
	_body = Rectangle<float>(initialPosition, _gameOptions.BaseEntityWidth, _gameOptions.BaseEntityHeight);
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
	if (_body.TopLeft().X < 0 || _body.TopRight().X > _gameOptions.ScreenWidth)
		_xVelocity *= -1.0f;

	for (auto checkEntity : dummies)
	{
		if (this != checkEntity)
		{
			auto dummy = (Dummy*)checkEntity;
			if (_body.CheckCollisionWith(dummy->_body))
			{
				_body.X -= _xVelocity;
				_xVelocity *= -1.0f;
				dummy->_xVelocity *= -1;
				/*if (_xVelocity < 0.0f)
				{
					
				}
				else if (_xVelocity > 0.0f)
				{

				}*/
			}
		}
	}

	_body.Y += _yVelocity;
	if (_body.TopLeft().Y < 0 || _body.BottomLeft().Y > _gameOptions.ScreenHeight)
		_yVelocity *= -1.0f;

	for (auto checkEntity : dummies)
	{
		if (this != checkEntity)
		{
			auto dummy = (Dummy*)checkEntity;
			if (_body.CheckCollisionWith(dummy->_body))
			{
				_body.Y -= _yVelocity;
				_yVelocity *= -1.0f;
				dummy->_yVelocity *= -1;
			}
		}
	}
}