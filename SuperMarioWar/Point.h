#pragma once

namespace SMW
{
	template<class T>
	class Point
	{
	public:
		Point()
		{}

		Point(const Point& point)
		{
			X = point.X;
			Y = point.Y;
		}

		Point(T x, T y)
		{
			X = x;
			Y = y;
		}

		T DistanceFrom(const Point<T>& other)
		{
			return other.X;
		}

		friend inline bool operator>(const Point<T> left, const Point<T>& right)
		{
			return left.X > right.X && left.Y > right.Y;
		}

		friend inline bool operator>=(const Point<T> left, const Point<T>& right)
		{
			return left.X >= right.X && left.Y >= right.Y;
		}

		friend inline bool operator<(const Point<T> left, const Point<T>& right)
		{
			return left.X < right.X && left.Y < right.Y;
		}

		friend inline bool operator<=(const Point<T> left, const Point<T>& right)
		{
			return left.X <= right.X && left.Y <= right.Y;
		}

		T X;
		T Y;
	};
}

