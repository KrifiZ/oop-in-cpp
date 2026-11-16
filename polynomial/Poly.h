#pragma once
#include <map>
#include <ostream>

class Poly {
public:
	// Returned by non-const operator[]. Reading through it does not create
	// a coefficient and assigning 0 removes one, so only non-zero ones are stored.
	class Coefficient {
	public:
		Coefficient(Poly& poly, int power) : poly(poly), power(power) {}

		Coefficient& operator=(double value);
		Coefficient& operator=(const Coefficient& other);
		operator double() const;

	private:
		Poly& poly;
		int power;
	};

	Poly(double constant = 0.0);

	Coefficient operator[](int power);
	double operator[](int power) const;
	double operator()(double x) const;

	Poly& operator+=(const Poly& other);
	Poly& operator-=(const Poly& other);
	Poly& operator*=(const Poly& other);

	friend std::ostream& operator<<(std::ostream& out, const Poly& p);

private:
	std::map<int, double> coefficients; // power -> non-zero coefficient

	double get(int power) const;
	void set(int power, double value);
};

Poly operator+(Poly lhs, const Poly& rhs);
Poly operator-(Poly lhs, const Poly& rhs);
Poly operator*(Poly lhs, const Poly& rhs);
