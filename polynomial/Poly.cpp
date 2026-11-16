#include "Poly.h"
#include <cmath>
#include <stdexcept>

static void checkPower(int power) {
	if (power < 0) {
		throw std::invalid_argument("Negative power");
	}
}

Poly::Coefficient& Poly::Coefficient::operator=(double value) {
	poly.set(power, value);
	return *this;
}

Poly::Coefficient& Poly::Coefficient::operator=(const Coefficient& other) {
	return *this = double(other);
}

Poly::Coefficient::operator double() const { return poly.get(power); }

Poly::Poly(double constant) { set(0, constant); }

Poly::Coefficient Poly::operator[](int power) {
	checkPower(power);
	return Coefficient(*this, power);
}

double Poly::operator[](int power) const {
	checkPower(power);
	return get(power);
}

double Poly::get(int power) const {
	auto it = coefficients.find(power);
	return it == coefficients.end() ? 0.0 : it->second;
}

void Poly::set(int power, double value) {
	if (value == 0.0)
		coefficients.erase(power);
	else
		coefficients[power] = value;
}

double Poly::operator()(double x) const {
	double result = 0.0;
	for (const auto& [power, value] : coefficients)
		result += value * std::pow(x, power);
	return result;
}

Poly& Poly::operator+=(const Poly& other) {
	for (const auto& [power, value] : other.coefficients)
		set(power, get(power) + value);
	return *this;
}

Poly& Poly::operator-=(const Poly& other) {
	for (const auto& [power, value] : other.coefficients)
		set(power, get(power) - value);
	return *this;
}

Poly& Poly::operator*=(const Poly& other) {
	Poly product;
	for (const auto& [power1, value1] : coefficients)
		for (const auto& [power2, value2] : other.coefficients)
			product.set(power1 + power2, product.get(power1 + power2) + value1 * value2);
	coefficients = product.coefficients;
	return *this;
}

Poly operator+(Poly lhs, const Poly& rhs) { return lhs += rhs; }
Poly operator-(Poly lhs, const Poly& rhs) { return lhs -= rhs; }
Poly operator*(Poly lhs, const Poly& rhs) { return lhs *= rhs; }

std::ostream& operator<<(std::ostream& out, const Poly& p) {
	if (p.coefficients.empty())
		return out << 0;

	for (auto it = p.coefficients.rbegin(); it != p.coefficients.rend(); ++it) {
		int power = it->first;
		double value = it->second;

		if (it == p.coefficients.rbegin())
			out << (value < 0 ? "-" : "");
		else
			out << (value < 0 ? " - " : " + ");

		value = std::abs(value);
		if (value != 1 || power == 0)
			out << value;
		if (power >= 1)
			out << "x";
		if (power >= 2)
			out << "^" << power;
	}
	return out;
}
