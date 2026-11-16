// Course's TestPolyWithFunctionTemplate.cpp with asserts added after every printed result.
// Class Poly is defined in file Poly.h
#include "Poly.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T> void display(T& p);
void test(const Poly& p1, const Poly& p2);
void testAddition(const Poly& p1, const Poly& p2);
void testSubtraction(const Poly& p1, const Poly& p2);
void testMultiplication(const Poly& p1, const Poly& p2);
void testValue(const Poly& p1, const Poly& p2);

static string str(const Poly& p)
{
	ostringstream out;
	out << p;
	return out.str();
}

int main()
{
	// Declare object representing polynomial p1
	Poly p1;

	// Specify coefficients of p1 = -2.3x^3 + 5x^2 - 4.5
	p1[3] = -2.3;
	p1[2] = 5;
	p1[0] = -4.5;

	cout << "======= Polynomial p1 =======" << endl;
	cout << p1 << endl;
	assert(str(p1) == "-2.3x^3 + 5x^2 - 4.5");

	// Declare object representing polynomial p2 = 2.6
	Poly p2 = 2.6;
	assert(str(p2) == "2.6");

	// Specify additional coefficient of p2 = x^4 - 7x^2 + 3x + 2.6
	p2[1] = 3;
	p2[2] = -7;
	p2[4] = 1;

	cout << "\n======= Polynomial p2 =======" << endl;
	display(p2);
	display<const Poly>(p2);
	// display(p2) read missing coefficients through non-const operator[]; no zeros may be stored
	assert(str(p2) == "x^4 - 7x^2 + 3x + 2.6");

	test(p1, p2);

	cout << "\nAll tests passed" << endl;
}

template <typename T> void display(T& p)
{
	cout << p << endl;

	// Display coefficients. If coefficient does not exist, display 0.
	const double expected[] = { 2.6, 3, -7, 0, 1, 0 };
	for (int i = 5; i >= 0; --i) {
		cout << "\tCoefficient " << i << ": " << p[i] << endl;
		assert(p[i] == expected[i]);
	}
}

void test(const Poly& p1, const Poly& p2)
{
	testAddition(p1, p2);
	testSubtraction(p1, p2);
	testMultiplication(p1, p2);
	testValue(p1, p2);
}

void testAddition(const Poly& p1, const Poly& p2)
{
	cout << "\n======= Addition =======" << endl;

	Poly p = p1 + p2;
	cout << "Sum of polynomials p1 and p2: " << p << endl;
	assert(str(p) == "x^4 - 2.3x^3 - 2x^2 + 3x - 1.9");

	p = p1 + 2.4;
	cout << "Sum of polynomial p1 and 2.4: " << p << endl;
	assert(str(p) == "-2.3x^3 + 5x^2 - 2.1");

	p = 2.4 + p1;
	cout << "Sum of 2.4 and polynomial p1: " << p << endl;
	assert(str(p) == "-2.3x^3 + 5x^2 - 2.1");
}

void testSubtraction(const Poly& p1, const Poly& p2)
{
	cout << "\n======= Subtraction =======" << endl;

	cout << "Difference of polynomials p1 and p2: " << p1 - p2 << endl;
	assert(str(p1 - p2) == "-x^4 - 2.3x^3 + 12x^2 - 3x - 7.1");

	// The following should display 0 (not 0x^3 + 0x^2 + 0)
	cout << "Difference of polynomials p1 and p1: " << p1 - p1 << endl;
	assert(str(p1 - p1) == "0");

	cout << "Difference of polynomial p1 and 5.3: " << p1 - 5.3 << endl;
	assert(str(p1 - 5.3) == "-2.3x^3 + 5x^2 - 9.8");

	cout << "Difference of 5.3 and polynomial p1: " << 5.3 - p1 << endl;
	assert(str(5.3 - p1) == "2.3x^3 - 5x^2 + 9.8");
}

void testMultiplication(const Poly& p1, const Poly& p2)
{
	cout << "\n======= Multiplication =======" << endl;

	cout << "Product of polynomials p1 and p2: " << p1 * p2 << endl;
	assert(str(p1 * p2) == "-2.3x^7 + 5x^6 + 16.1x^5 - 46.4x^4 + 9.02x^3 + 44.5x^2 - 13.5x - 11.7");

	cout << "6.7 multiplied by polynomial p1: " << 6.7 * p1 << endl;
	assert(str(6.7 * p1) == "-15.41x^3 + 33.5x^2 - 30.15");

	cout << "Polynomial p1 multiplied by 6.7: " << p1 * 6.7 << endl;
	assert(str(p1 * 6.7) == "-15.41x^3 + 33.5x^2 - 30.15");
}

void testValue(const Poly& p1, const Poly& p2)
{
	cout << "\n======= Value =======" << endl;

	cout << "Value of polynomial p1 at point  3.9: " << p1(3.9) << endl;
	assert(abs(p1(3.9) - -64.8837) < 1e-9);

	cout << "Value of polynomial p2 at point -2.8: " << p2(-2.8) << endl;
	assert(abs(p2(-2.8) - 0.7856) < 1e-9);
}
