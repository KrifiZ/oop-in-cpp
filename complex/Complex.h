#pragma once
#include <ostream>

class Complex {
public:
	double real, imag;

	Complex(double real = 0.0, double imag = 0.0) : real(real), imag(imag) {}

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	double amplitude() const;
	double phase() const;
};

Complex operator+(Complex lhs, const Complex& rhs);
Complex operator-(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, const Complex& rhs);
Complex operator/(Complex lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& out, const Complex& z);
