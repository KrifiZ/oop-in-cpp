#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include "Poly.h"

// p has exactly these non-zero coefficients (power -> value)
bool same(const Poly& p, const std::map<unsigned, double>& expected)
{
	if (p.terms() != expected.size())
		return false;
	for (const auto& [n, c] : expected)
		if (std::abs(p[n] - c) > 1e-9)
			return false;
	return true;
}

std::string str(const Poly& p)
{
	std::ostringstream out;
	out << p;
	return out.str();
}

Poly makeP1()
{
	Poly p;
	p[3] = -2.3;
	p[2] = 5;
	p[0] = -4.5;
	return p;
}

Poly makeP2()
{
	Poly p = 2.6;
	p[1] = 3;
	p[2] = -7;
	p[4] = 1;
	return p;
}

void testSparseStorage()
{
	Poly p;
	p[1000] = 1;
	p[350] = 6;
	p[0] = 15;
	assert(p.terms() == 3);
	assert(str(p) == "x^1000 + 6x^350 + 15");

	// reading through non-const operator[] must not store zeros
	double sum = 0;
	for (int i = 0; i <= 1000; ++i)
		sum += p[i];
	assert(sum == 22 && p.terms() == 3);

	p[350] = 0;
	assert(p.terms() == 2);
	assert(Poly().terms() == 0 && Poly(0).terms() == 0);
}

void testPrinting()
{
	assert(str(makeP1()) == "-2.3x^3 + 5x^2 - 4.5");
	assert(str(makeP2()) == "x^4 - 7x^2 + 3x + 2.6");
	assert(str(Poly()) == "0");
	Poly p;
	p[1] = -1;
	assert(str(p) == "-x");
}

void testArithmetic()
{
	const Poly p1 = makeP1(), p2 = makeP2();

	assert(same(p1 + p2, {{4, 1}, {3, -2.3}, {2, -2}, {1, 3}, {0, -1.9}}));
	assert(same(p1 + 2.4, {{3, -2.3}, {2, 5}, {0, -2.1}}));
	assert(same(2.4 + p1, {{3, -2.3}, {2, 5}, {0, -2.1}}));

	assert(same(p1 - p2, {{4, -1}, {3, -2.3}, {2, 12}, {1, -3}, {0, -7.1}}));
	assert(same(p1 - p1, {}) && str(p1 - p1) == "0");
	assert(same(5.3 - p1, {{3, 2.3}, {2, -5}, {0, 9.8}}));

	assert(same(p1 * p2, {{7, -2.3}, {6, 5}, {5, 16.1}, {4, -46.4}, {3, 9.02}, {2, 44.5}, {1, -13.5}, {0, -11.7}}));
	assert(same(6.7 * p1, {{3, -15.41}, {2, 33.5}, {0, -30.15}}));
	assert(same(p1 * 6.7, {{3, -15.41}, {2, 33.5}, {0, -30.15}}));
	assert(same(p1 * 0, {}));
}

void testValue()
{
	assert(std::abs(makeP1()(3.9) - -64.8837) < 1e-9);
	assert(std::abs(makeP2()(-2.8) - 0.7856) < 1e-9);
	assert(Poly()(5) == 0);
}

void modifyCopy(Poly p) // by value: works on a copy
{
	p[0] = 100;
	p[7] = 1;
}

void testPassByValue()
{
	Poly p = makeP1();
	modifyCopy(p);
	assert(same(p, {{3, -2.3}, {2, 5}, {0, -4.5}}));

	Poly q;
	q = p;
	q[3] = 0;
	assert(p.terms() == 3 && q.terms() == 2);
}

int main()
{
	testSparseStorage();
	testPrinting();
	testArithmetic();
	testValue();
	testPassByValue();
	std::cout << "All tests passed\n";
}
