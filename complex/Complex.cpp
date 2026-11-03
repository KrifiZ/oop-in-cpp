#include "Complex.h"
#include <cmath>
#include <stdexcept>

Complex& Complex::operator+=(const Complex& other) {
	real += other.real;
	imag += other.imag;
	return *this;
}

Complex& Complex::operator-=(const Complex& other) {
	real -= other.real;
	imag -= other.imag;
	return *this;
}

Complex& Complex::operator*=(const Complex& other) {
	double newReal = real * other.real - imag * other.imag;
	double newImag = real * other.imag + imag * other.real;
	real = newReal;
	imag = newImag;
	return *this;
}

Complex& Complex::operator/=(const Complex& other) {
	double denominator = other.real * other.real + other.imag * other.imag;
	if (denominator == 0.0) {
		throw std::invalid_argument("Division by 0");
	}
	double newReal = (real * other.real + imag * other.imag) / denominator;
	double newImag = (imag * other.real - real * other.imag) / denominator;
	real = newReal;
	imag = newImag;
	return *this;
}

double Complex::amplitude() const { return std::hypot(real, imag); }
double Complex::phase() const { return std::atan2(imag, real); }

Complex operator+(Complex lhs, const Complex& rhs) { return lhs += rhs; }
Complex operator-(Complex lhs, const Complex& rhs) { return lhs -= rhs; }
Complex operator*(Complex lhs, const Complex& rhs) { return lhs *= rhs; }
Complex operator/(Complex lhs, const Complex& rhs) { return lhs /= rhs; }

bool operator==(const Complex& lhs, const Complex& rhs) {
	return lhs.real == rhs.real && lhs.imag == rhs.imag;
}

bool operator!=(const Complex& lhs, const Complex& rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& out, const Complex& z) {
	out << z.real;
	if (z.imag >= 0)
		out << " + " << z.imag << "i";
	else
		out << " - " << -z.imag << "i";
	return out;
}
