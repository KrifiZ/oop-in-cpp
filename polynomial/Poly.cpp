#include "Poly.h"
#include <cmath>
#include <iterator>

Poly::Poly(double c0)
{
	(*this)[0] = c0;
}

Poly::Ref& Poly::Ref::operator=(double v)
{
	if (v == 0)
		p.coef.erase(n);
	else
		p.coef[n] = v;
	return *this;
}

void Poly::trim()
{
	for (auto it = coef.begin(); it != coef.end();)
		it = it->second == 0 ? coef.erase(it) : std::next(it);
}

double Poly::operator[](unsigned n) const
{
	auto it = coef.find(n);
	return it == coef.end() ? 0.0 : it->second;
}

double Poly::operator()(double x) const
{
	double sum = 0;
	for (const auto& [n, c] : coef)
		sum += c * std::pow(x, n);
	return sum;
}

Poly& Poly::operator+=(const Poly& other)
{
	for (const auto& [n, c] : other.coef)
		coef[n] += c;
	trim();
	return *this;
}

Poly& Poly::operator-=(const Poly& other)
{
	for (const auto& [n, c] : other.coef)
		coef[n] -= c;
	trim();
	return *this;
}

Poly& Poly::operator*=(const Poly& other)
{
	Poly result;
	for (const auto& [n1, c1] : coef)
		for (const auto& [n2, c2] : other.coef)
			result.coef[n1 + n2] += c1 * c2;
	result.trim();
	coef.swap(result.coef);
	return *this;
}

Poly operator+(Poly lhs, const Poly& rhs) { return lhs += rhs; }
Poly operator-(Poly lhs, const Poly& rhs) { return lhs -= rhs; }
Poly operator*(const Poly& lhs, const Poly& rhs) { return Poly(lhs) *= rhs; }

std::ostream& operator<<(std::ostream& out, const Poly& p)
{
	if (p.coef.empty())
		return out << 0;

	bool first = true;
	for (const auto& [n, c] : p.coef) {
		if (first)
			out << (c < 0 ? "-" : "");
		else
			out << (c < 0 ? " - " : " + ");
		first = false;

		double a = std::abs(c);
		if (a != 1 || n == 0)
			out << a;
		if (n > 0)
			out << 'x';
		if (n > 1)
			out << '^' << n;
	}
	return out;
}
