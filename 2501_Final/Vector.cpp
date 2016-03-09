#include "Vector.h"

namespace vec
{
	Vector2::Vector2()
		: x(0),
		y(0)
	{
		_mag();
	}

	// ANGLE CONSTRUCTOR (Radians)
	Vector2::Vector2(int angle)
		: x(std::cos(angle)),
		y(std::sin(angle))
	{
		_mag();
	}

	Vector2::Vector2(float angle)
		: x(std::cos(angle)),
		y(std::sin(angle))
	{
		_mag();
	}

	Vector2::Vector2(double angle)
		: x(std::cos(angle)),
		y(std::sin(angle))
	{
		_mag();
	}

	// X&Y CONSTRUCTORS
	Vector2::Vector2(int _x, int _y)
		: x(_x),
		y(_y)
	{
		_mag();
	}

	Vector2::Vector2(float _x, float _y)
		: x(_x),
		y(_y)
	{
		_mag();
	}

	Vector2::Vector2(double _x, double _y)
		: x(_x),
		y(_y)
	{
		_mag();
	}

	Vector2::~Vector2() {}



	// GETTERS
	double Vector2::getMag() const { return mag; }
	double Vector2::getX() const { return x; }
	double Vector2::getY() const { return y; }

	// SETTERS
	Vector2& Vector2::setMag(double m)
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

	Vector2& Vector2::setX(double _x)
	{
		x = _x;

		_mag();
		return *this;
	}

	Vector2& Vector2::setY(double _y)
	{
		y = _y;

		_mag();
		return *this;
	}


	// SIMPLE OPERATIONS
	Vector2& Vector2::operator*=(const double r)
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

	Vector2& Vector2::operator/=(const double r)
	{
		if (r == 0)
			return *this;

		x /= r;
		y /= r;

		_mag();
		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& r)
	{
		x += r.getX();
		y += r.getY();

		_mag();
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& r)
	{
		x -= r.getX();
		y -= r.getY();

		_mag();
		return *this;
	}


	// COMPLEX OPERATIONS
	double Vector2::dot(const Vector2& r) const
	{
		return (x * r.getX()) + (y * r.getY());
	}

	double Vector2::cross(const Vector2& r) const
	{
		return (x * r.getY()) - (y * r.getX());
	}

	double Vector2::dist(const Vector2& r) const
	{
		double dx = this->getX() - r.getX();
		double dy = this->getY() - r.getY();

		return std::sqrt((dx * dx) + (dy* dy));
	}

	double Vector2::angleBetween(const Vector2& r) const
	{
		return std::acos( dot(r) / (getMag() * r.getMag()) );
	}

	Vector2& Vector2::rotate(const double angle)
	{
		double _x = x * std::cos(angle) - y * std::sin(angle);
		double _y = x * std::sin(angle) + y * std::cos(angle);

		x = _x;
		y = _y;

		return *this;
	}



	// PRIVATE FUNCTIONS
	void Vector2::_mag()
	{
		mag = std::sqrt((x * x) + (y * y));
	}



	//////////////////////////////////////////////
	//                 GLOBALS                  //
	//////////////////////////////////////////////


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

	double angleBetween(const Vector2& l, const Vector2& r)
	{
		return std::acos(dot(l, r) / (l.getMag() * r.getMag()));
	}

	Vector2 rotate(const Vector2& vec, const double angle)
	{
		vec::Vector2 newVec = vec;
		newVec.rotate(angle);

		return newVec;
	}


}

// OTHER OPERATIONS
std::ostream& operator<<(std::ostream& out, const vec::Vector2& vec)
{
	return out << "(" << vec.getX() << ", " << vec.getY() << ")[" << vec.getMag() << "]";
}

double toRadians(double degrees)
{
	return degrees * PI / 180.0f;
}

double toDegrees(double radians)
{
	return radians * 180.0f / PI;
}