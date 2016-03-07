#pragma once

#include <iostream>
#include <string>
#include <SFML\System\Vector2.hpp>

namespace vec
{
	class Vector2
	{
	public:
		Vector2();

		// Amgle Ctr
		Vector2(int);
		Vector2(float);
		Vector2(double);

		// X & Y Co-ord Ctrs
		Vector2(int, int);
		Vector2(float, float);
		Vector2(double, double);
		~Vector2();

		// GETTERS
		double getMag() const;
		double getX() const;
		double getY() const;

		// SETTERS
		Vector2& setMag(double);
		Vector2& setX(double);
		Vector2& setY(double);

		// SIMPLE OPERATIONS
		Vector2& operator*=(const double);
		Vector2& operator/=(const double);
		Vector2& operator+=(const Vector2&);
		Vector2& operator-=(const Vector2&);

		// COMPLEX OPERATIONS
		double dot(const Vector2&) const;
		double cross(const Vector2&) const;
		double dist(const Vector2&) const;
		double angleBetween(const Vector2&) const;
		Vector2& rotate(const double);

	private:
		void _mag();

		double x, y, mag;
	};

	// SIMPLE GLOBAL OPERATIONS
	Vector2 operator*(const Vector2&, const double);
	Vector2 operator/(const Vector2&, const double);
	Vector2 operator+(const Vector2&, const Vector2&);
	Vector2 operator-(const Vector2&, const Vector2&);
	bool operator==(const Vector2&, const Vector2&);
	bool operator!=(const Vector2&, const Vector2&);

	// COMPLEX GLOBAL OPERATIONS
	double dot(const Vector2&, const Vector2&);
	double cross(const Vector2&, const Vector2&);
	double dist(const Vector2&, const Vector2&);
	double angleBetween(const Vector2&, const Vector2&);
	Vector2 rotate(const Vector2&, const double);
}

// OTHER OPERATIONS
std::ostream& operator<<(std::ostream&, const vec::Vector2&);