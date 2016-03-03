#pragma once

#include <iostream>
#include <string>

namespace vec
{
	class Vector2
	{
	public:
		Vector2() { x = 0; y = 0; _mag(); }
		Vector2(int _x, int _y) { x = _x; y = _y; _mag(); }
		Vector2(float _x, float _y) { x = _x; y = _y; _mag(); }
		Vector2(double _x, double _y) { x = _x; y = _y; _mag(); }
		~Vector2() {}

		// GETTERS
		double getMag() const { return mag; }
		double getX() const { return x; }
		double getY() const { return y; }

		// SETTERS
		Vector2& setMag(double m)
		{
			// Check for zero mag
			if (mag == 0)
			{
				x = m;
				y = 0;
				mag = m;
			}
			else
			{
				double oldMag = mag;
				x /= oldMag;
				y /= oldMag;

				x *= m;
				y *= m;
			}

			_mag();
			return *this;
		}

		Vector2& setX(double _x)
		{
			x = _x;

			_mag();
			return *this;
		}

		Vector2& setY(double _y)
		{
			y = _y;

			_mag();
			return *this;
		}


		// SIMPLE OPERATIONS
		Vector2& operator*=(const double r)
		{
			if (r == 0)
			{
				x = 0;
				y = 0;
				mag = 0;
				return *this;
			}

			x *= r;
			y *= r;

			_mag();
			return *this;
		}

		Vector2& operator/=(const double r)
		{
			if (r == 0)
				return *this;

			x /= r;
			y /= r;

			_mag();
			return *this;
		}

		Vector2& operator+=(const Vector2& r)
		{
			x += r.getX();
			y += r.getY();

			_mag();
			return *this;
		}

		Vector2& operator-=(const Vector2& r)
		{
			x -= r.getX();
			y -= r.getY();

			_mag();
			return *this;
		}


		// COMPLEX OPERATIONS
		double dot(const Vector2& r) const
		{
			return (x * r.getX()) + (y * r.getY());
		}

		double cross(const Vector2& r) const
		{
			return (x * r.getY()) - (y * r.getX());
		}

		double dist(const Vector2& r) const
		{
			double dx = this->getX() - r.getX();
			double dy = this->getY() - r.getY();

			return std::sqrt((dx * dx) + (dy* dy));
		}


	private:
		void _mag()
		{
			mag = std::sqrt((x * x) + (y * y));
		}

		double x, y, mag;
	};






	// SIMPLE GLOBAL OPERATIONS
	Vector2 operator*(const Vector2& l, const double r)
	{
		return Vector2(l.getX() * r, l.getY() * r);
	}

	Vector2 operator/(const Vector2& l, const double r)
	{
		if (r == 0)
			return Vector2(0, 0);

		return Vector2(l.getX() / r, l.getY() / r);
	}

	Vector2 operator+(const Vector2& l, const Vector2& r)
	{
		return Vector2(l.getX() + r.getX(), l.getY() + r.getY());
	}

	Vector2 operator-(const Vector2& l, const Vector2& r)
	{
		return Vector2(l.getX() - r.getX(), l.getY() - r.getY());
	}

	bool operator==(const Vector2& l, const Vector2& r)
	{
		return (l.getX() == r.getX()) && (l.getY() == r.getY());
	}

	bool operator!=(const Vector2& l, const Vector2& r)
	{
		return (l.getX() != r.getX()) || (l.getY() != r.getY());
	}

	// COMPLEX GLOBAL OPERATIONS
	double dot(const Vector2& l, const Vector2& r)
	{
		return (l.getX() * r.getX()) + (l.getY() * r.getY());
	}

	double cross(const Vector2& l, const Vector2& r)
	{
		return (l.getX() * r.getY()) - (l.getY() * r.getX());
	}

	double dist(const Vector2& l, const Vector2& r)
	{
		return (l - r).getMag();
	}

}

// OTHER OPERATIONS
std::ostream& operator<<(std::ostream& out, const vec::Vector2& vec)
{
	return out << "(" << vec.getX() << ", " << vec.getY() << ")[" << vec.getMag() << "]";
}