#pragma once
#include "Point.h"

namespace SMW
{
	template<class T>
	class Rectangle
	{
	public:
		Rectangle()
		{}

		Rectangle(const Rectangle& rectangle)
		{
			X = rectangle.X;
			Y = rectangle.Y;
			Width = rectangle.Width;
			Height = rectangle.Height;
		}

		Rectangle(T x, T y, T width, T height)
		{
			X = x;
			Y = y;
			Width = width;
			Height = height;
		}

		Rectangle(const Point<T>& location, T width, T height)
		{
			X = location.X;
			Y = location.Y;
			Width = width;
			Height = height;
		}

		const Point<T>& TopLeft() const
		{
			return Point<T>(X, Y);
		}

		const Point<T>& TopRight() const
		{
			return Point<T>(X + Width, Y);
		}

		const Point<T>& BottomLeft() const
		{
			return Point<T>(X, Y + Height);
		}

		const Point<T>& BottomRight() const
		{
			return Point<T>(X + Width, Y + Height);
		}

		bool CheckCollisionWith(const Rectangle<T>& other, float xVelocity, float yVelocity)
		{
			if (xVelocity < 0.0f && yVelocity < 0.0f)
			{
				if (TopLeft().X < other.BottomRight().X &&
					TopLeft().Y < other.BottomRight().Y)
					return true;
			}
			else if (xVelocity > 0.0f && yVelocity < 0.0f)
			{
				if (TopRight().X > other.BottomLeft().X &&
					TopRight().Y < other.BottomLeft().Y)
					return true;
			}
			else if (xVelocity < 0.0f && yVelocity > 0.0f)
			{
				if (BottomLeft().X < other.TopRight().X &&
					BottomLeft().Y > other.TopRight().Y)
					return true;
			}
			else if(xVelocity > 0.0f && yVelocity > 0.0f)
			{
				if (BottomRight().X > other.TopLeft().X &&
					BottomRight().Y > other.TopLeft().Y)
					return true;
			}

			return false;
		}

		T X;
		T Y;
		T Width;
		T Height;
	};
}

