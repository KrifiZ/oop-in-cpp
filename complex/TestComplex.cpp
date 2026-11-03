#include <cassert>
#include <iostream>
#include <stdexcept>
#include "Complex.h"

void testFieldAccess() {
	Complex z(1, 2);
	z.real = 5;
	z.imag = -3;
	std::cout << "access: z = " << z << '\n';
	assert(z.real == 5 && z.imag == -3);
}

void testConstNumbers() {
	const Complex x(1, 1), y(2, -3);
	std::cout << "const: x = " << x << ", y = " << y << '\n';
	assert(x + y == Complex(3, -2));
	assert(x - y == Complex(-1, 4));
	assert(x * y == Complex(5, -1));
	assert(Complex(5, -1) / y == x);
	assert(x != y);
}

void testAmplitudePhase() {
	const Complex z(3, 4);
	std::cout << "|3+4i| = " << z.amplitude() << ", arg(i) = " << Complex(0, 1).phase() << '\n';
	assert(z.amplitude() == 5);
}

void testChainedAdd() {
	Complex a(1, 2), b(3, -1), c(3.5);
	a += b += c;
	std::cout << "a += b += c   : a = " << a << ", b = " << b << '\n';
	assert(b == Complex(6.5, -1) && a == Complex(7.5, 1));

	a = Complex(1, 2); b = Complex(3, -1);
	(a += b) += c;
	std::cout << "(a += b) += c : a = " << a << '\n';
	assert(a == Complex(7.5, 1) && b == Complex(3, -1));
}

void testChainedMultiply() {
	Complex a(1, 2), b(3, -1), c(2);
	a *= b *= c;
	std::cout << "a *= b *= c   : a = " << a << ", b = " << b << '\n';
	assert(b == Complex(6, -2) && a == Complex(10, 10));

	a = Complex(1, 2); b = Complex(3, -1);
	(a *= b) *= c;
	std::cout << "(a *= b) *= c : a = " << a << '\n';
	assert(a == Complex(10, 10) && b == Complex(3, -1));
}

void testMixedWithDouble() {
	Complex a(1, 2), b(3, -1), c(3.5);
	std::cout << std::boolalpha
		<< "a + 7.2  = " << a + 7.2 << '\n'
		<< "7.2 + a  = " << 7.2 + a << '\n'
		<< "b * 5.1  = " << b * 5.1 << '\n'
		<< "5.1 * b  = " << 5.1 * b << '\n'
		<< "c == 3.5 : " << (c == 3.5) << '\n'
		<< "3.5 == c : " << (3.5 == c) << '\n';
	assert(a + 7.2 == Complex(8.2, 2) && 7.2 + a == Complex(8.2, 2));
	assert(b * 5.1 == 5.1 * b);
	assert(c == 3.5 && 3.5 == c);
}

void testDivisionByZero() {
	try {
		Complex(1, 2) / Complex();
		assert(false);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "a / 0 -> " << e.what() << '\n';
	}
}

int main()
{
	testFieldAccess();
	testConstNumbers();
	testAmplitudePhase();
	testChainedAdd();
	testChainedMultiply();
	testMixedWithDouble();
	testDivisionByZero();
	std::cout << "All tests passed\n";
	return 0;
}
