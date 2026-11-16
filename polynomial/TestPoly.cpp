#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Poly.h"

static std::string str(const Poly& p) {
	std::ostringstream out;
	out << p;
	return out.str();
}

// p1 = -2.3x^3 + 5x^2 - 4.5
static Poly makeP1() {
	Poly p1;
	p1[3] = -2.3;
	p1[2] = 5;
	p1[0] = -4.5;
	return p1;
}

// p2 = x^4 - 7x^2 + 3x + 2.6
static Poly makeP2() {
	Poly p2 = 2.6;
	p2[1] = 3;
	p2[2] = -7;
	p2[4] = 1;
	return p2;
}

// display() from the course's TestPolyWithFunctionTemplate.cpp. With T = Poly it reads
// coefficients through the non-const operator[], with T = const Poly through the const one.
template <typename T> void display(T& p) {
	std::cout << p << '\n';
	for (int i = 5; i >= 0; --i)
		std::cout << "\tCoefficient " << i << ": " << p[i] << '\n';
}

void testConstruction() {
	const Poly zero, constant = 2.6;
	std::cout << "construction: Poly() = " << zero << ", Poly p = 2.6 -> " << constant << '\n';
	assert(str(zero) == "0" && str(Poly(0)) == "0");
	assert(str(constant) == "2.6" && constant[0] == 2.6 && constant[1] == 0);
}

void testSetCoefficients() {
	const Poly p1 = makeP1(), p2 = makeP2();
	std::cout << "p1 = " << p1 << ", p2 = " << p2 << '\n';
	assert(str(p1) == "-2.3x^3 + 5x^2 - 4.5");
	assert(str(p2) == "x^4 - 7x^2 + 3x + 2.6");
	assert(p1[3] == -2.3 && p1[2] == 5 && p1[1] == 0 && p1[0] == -4.5);
}

void testPrintUnitCoefficients() {
	Poly p;
	p[1] = 1;
	assert(str(p) == "x");
	p[1] = -1;
	assert(str(p) == "-x");
	p[0] = 1;
	assert(str(p) == "-x + 1");
	p[2] = -1;
	assert(str(p) == "-x^2 - x + 1");
	std::cout << "unit coefficients: " << p << '\n';
}

void testSparseStorage() {
	Poly p;
	p[1000] = 1;
	p[350] = 6;
	p[0] = 15;

	// operator<< prints every stored coefficient, so a stored zero would show up as "0x^..."
	double sum = 0;
	for (int i = 0; i <= 1000; ++i)
		sum += p[i];
	std::cout << "sparse: p = " << p << ", sum of coefficients = " << sum << '\n';
	assert(sum == 22);
	assert(str(p) == "x^1000 + 6x^350 + 15");

	p[350] = 0;
	assert(str(p) == "x^1000 + 15");
}

void testFunctionTemplate() {
	Poly p2 = makeP2();
	std::cout << "display<Poly>(p2): ";
	display(p2);
	std::cout << "display<const Poly>(p2): ";
	display<const Poly>(p2);
	assert(str(p2) == "x^4 - 7x^2 + 3x + 2.6");
}

void testAddition() {
	const Poly p1 = makeP1(), p2 = makeP2();
	std::cout << "p1 + p2 = " << p1 + p2 << ", p1 + 2.4 = " << p1 + 2.4 << '\n';
	assert(str(p1 + p2) == "x^4 - 2.3x^3 - 2x^2 + 3x - 1.9");
	assert(str(p1 + 2.4) == "-2.3x^3 + 5x^2 - 2.1");
	assert(str(2.4 + p1) == "-2.3x^3 + 5x^2 - 2.1");
}

void testSubtraction() {
	const Poly p1 = makeP1(), p2 = makeP2();
	std::cout << "p1 - p2 = " << p1 - p2 << ", p1 - p1 = " << p1 - p1 << '\n';
	assert(str(p1 - p2) == "-x^4 - 2.3x^3 + 12x^2 - 3x - 7.1");
	assert(str(p1 - p1) == "0");
	assert(str(p1 - 5.3) == "-2.3x^3 + 5x^2 - 9.8");
	assert(str(5.3 - p1) == "2.3x^3 - 5x^2 + 9.8");
}

void testMultiplication() {
	const Poly p1 = makeP1(), p2 = makeP2();
	std::cout << "p1 * p2 = " << p1 * p2 << '\n';
	assert(str(p1 * p2) == "-2.3x^7 + 5x^6 + 16.1x^5 - 46.4x^4 + 9.02x^3 + 44.5x^2 - 13.5x - 11.7");
	assert(str(6.7 * p1) == "-15.41x^3 + 33.5x^2 - 30.15");
	assert(str(p1 * 6.7) == "-15.41x^3 + 33.5x^2 - 30.15");
	assert(str(p1 * 0) == "0");
}

void testChainedCompoundAssignment() {
	Poly a = makeP1(), b = makeP2(), c = 1;
	a += b -= c;
	std::cout << "a += b -= c : a = " << a << ", b = " << b << '\n';
	assert(str(b) == "x^4 - 7x^2 + 3x + 1.6");
	assert(str(a) == "x^4 - 2.3x^3 - 2x^2 + 3x - 2.9");

	a = makeP1();
	(a *= c) *= 2;
	assert(str(a) == "-4.6x^3 + 10x^2 - 9");
}

void testValue() {
	const Poly p1 = makeP1(), p2 = makeP2();
	std::cout << "p1(3.9) = " << p1(3.9) << ", p2(-2.8) = " << p2(-2.8) << '\n';
	assert(std::abs(p1(3.9) - -64.8837) < 1e-9);
	assert(std::abs(p2(-2.8) - 0.7856) < 1e-9);
	assert(Poly()(5) == 0);
}

static std::string modifyCopy(Poly p) {
	p[0] = 100;
	p[7] = 1;
	return str(p);
}

void testPassByValue() {
	Poly p = makeP1();
	std::cout << "by value: modified copy = " << modifyCopy(p) << ", original = " << p << '\n';
	assert(modifyCopy(p) == "x^7 - 2.3x^3 + 5x^2 + 100");
	assert(str(p) == "-2.3x^3 + 5x^2 - 4.5");
}

void testCopyIsIndependent() {
	Poly a = makeP1();
	Poly b = a;
	Poly c;
	c = a;
	b[3] = 0;
	c[1] = 2;
	assert(str(a) == "-2.3x^3 + 5x^2 - 4.5");
	assert(str(b) == "5x^2 - 4.5");
	assert(str(c) == "-2.3x^3 + 5x^2 + 2x - 4.5");
}

void testCoefficientToCoefficient() {
	Poly p = makeP1();
	p[5] = p[3];
	p[3] = p[1];
	std::cout << "p[5] = p[3]; p[3] = p[1] : " << p << '\n';
	assert(str(p) == "-2.3x^5 + 5x^2 - 4.5");
}

void testNegativePower() {
	Poly p;
	const Poly& cp = p;
	try {
		p[-1] = 3;
		assert(false);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "p[-1] -> " << e.what() << '\n';
	}
	try {
		cp[-1];
		assert(false);
	}
	catch (const std::invalid_argument&) {
	}
}

int main()
{
	testConstruction();
	testSetCoefficients();
	testPrintUnitCoefficients();
	testSparseStorage();
	testFunctionTemplate();
	testAddition();
	testSubtraction();
	testMultiplication();
	testChainedCompoundAssignment();
	testValue();
	testPassByValue();
	testCopyIsIndependent();
	testCoefficientToCoefficient();
	testNegativePower();
	std::cout << "All tests passed\n";
	return 0;
}
