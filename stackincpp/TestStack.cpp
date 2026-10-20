#include "Stack.h"
#include <climits>
#include <cstdio>

static int failures = 0;

#define CHECK(cond)                                                            \
	if (!(cond))                                                               \
	failures++

void testConstructor()
{
	Stack s;
	CHECK(s.isEmpty());
	CHECK(s.getLength() == 0);
	CHECK(s.getSize() == 1);
}

void testPopEmpty()
{
	Stack s;
	CHECK(s.pop() == 0);
	CHECK(s.isEmpty());
	CHECK(s.getLength() == 0);
}

void testPushEmpty()
{
	Stack s;
	s.push(42);
	CHECK(!s.isEmpty());
	CHECK(s.getLength() == 1);
	CHECK(s.pop() == 42);
	CHECK(s.isEmpty());
}

void testPushZero()
{
	Stack s;
	s.push(0);
	CHECK(!s.isEmpty());
	CHECK(s.pop() == 0);
	CHECK(s.isEmpty());
}

void testExtremeValues()
{
	Stack s;
	s.push(INT_MIN);
	s.push(-1);
	s.push(INT_MAX);
	CHECK(s.pop() == INT_MAX);
	CHECK(s.pop() == -1);
	CHECK(s.pop() == INT_MIN);
}

void testInterleaved()
{
	Stack s;
	s.push(1);
	s.push(2);
	CHECK(s.pop() == 2);
	s.push(3);
	s.push(4);
	CHECK(s.pop() == 4);
	CHECK(s.pop() == 3);
	CHECK(s.pop() == 1);
	CHECK(s.isEmpty());
}

void testReuseAfterEmpty()
{
	Stack s;
	for (int round = 0; round < 3; round++) {
		for (int i = 0; i < 1000; i++)
			s.push(i);
		for (int i = 999; i >= 0; i--)
			CHECK(s.pop() == i);
		CHECK(s.isEmpty());
		CHECK(s.getSize() == 1);
	}
}

void testManyElements()
{
	Stack s;
	const int MAX = 100000;
	for (int i = 0; i < MAX; i++)
		s.push(i);
	CHECK(s.getLength() == MAX);

	bool ok = true;
	for (int i = MAX - 1; i >= 0; i--) {
		if (s.pop() != i) {
			ok = false;
			break;
		}
	}
	CHECK(ok);
	CHECK(s.isEmpty());
}

void testMultipleStacks()
{
	Stack s1, s2;
	s1.push(1);
	s2.push(2);
	CHECK(s1.pop() == 1);
	CHECK(s2.pop() == 2);
	CHECK(s1.isEmpty());
	CHECK(s2.isEmpty());
}

void testDestroyNonEmpty()
{
	Stack s;
	for (int i = 0; i < 50; i++)
		s.push(i);
}

int main()
{
	testConstructor();
	testPopEmpty();
	testPushEmpty();
	testPushZero();
	testExtremeValues();
	testInterleaved();
	testReuseAfterEmpty();
	testManyElements();
	testMultipleStacks();
	testDestroyNonEmpty();

	if (failures == 0)
		printf("All tests pass\n");
	else
		printf("Failures: %d\n", failures);
	return failures != 0;
}
