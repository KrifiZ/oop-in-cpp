#pragma once
#include <cstddef>
#include <functional>
#include <map>
#include <ostream>

class Poly {
	// Only non-zero coefficients, highest power first. std::map copies itself,
	// so the compiler-generated copy ctor / operator= / dtor are correct (rule of zero).
	std::map<unsigned, double, std::greater<unsigned>> coef;

	void trim();

public:
	// Returned by non-const operator[]: reading does not create a zero entry,
	// assigning 0 removes the coefficient.
	class Ref {
		Poly& p;
		unsigned n;
	public:
		Ref(Poly& p, unsigned n) : p(p), n(n) {}
		Ref& operator=(double v);
		Ref& operator=(const Ref& r) { return *this = double(r); }
		operator double() const { return static_cast<const Poly&>(p)[n]; }
	};

	Poly(double c0 = 0.0);

	Ref operator[](unsigned n) { return Ref(*this, n); }
	double operator[](unsigned n) const;
	double operator()(double x) const;
	std::size_t terms() const { return coef.size(); }

	Poly& operator+=(const Poly& other);
	Poly& operator-=(const Poly& other);
	Poly& operator*=(const Poly& other);

	friend std::ostream& operator<<(std::ostream& out, const Poly& p);
};

Poly operator+(Poly lhs, const Poly& rhs);
Poly operator-(Poly lhs, const Poly& rhs);
Poly operator*(const Poly& lhs, const Poly& rhs);
