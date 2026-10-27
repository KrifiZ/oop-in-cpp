#include "Stack.h"
#include <climits>
#include <cstdio>

static int failures = 0;

#define CHECK(cond)                                                            \
	if (!(cond))                                                               \
	failures++

static void fill(Stack& s, int n, int offset = 0)
{
	for (int i = 0; i < n; i++)
		s.push(offset + i);
}

static bool holds(Stack& s, int n, int offset = 0)
{
	for (int i = n - 1; i >= 0; i--)
		if (s.isEmpty() || s.pop() != offset + i)
			return false;
	return s.isEmpty();
}

void testConstructor()
{
	Stack s;
	CHECK(s.isEmpty());
}

void testPopEmpty()
{
	Stack s;
	CHECK(s.pop() == 0);
	CHECK(s.isEmpty());
}

void testPushEmpty()
{
	Stack s;
	s.push(42);
	CHECK(!s.isEmpty());
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
		fill(s, 1000);
		CHECK(holds(s, 1000));
	}
}

void testManyElements()
{
	Stack s;
	fill(s, 100000);
	CHECK(holds(s, 100000));
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
	fill(s, 50);
}


void testCopyEmpty()
{
	Stack a;
	Stack b(a);
	CHECK(b.isEmpty());
	CHECK(b.pop() == 0);
	b.push(7);
	CHECK(b.pop() == 7);
	CHECK(a.isEmpty());
}

void testCopyNonEmpty()
{
	Stack a;
	fill(a, 100);
	Stack b(a);
	CHECK(holds(b, 100));
	CHECK(holds(a, 100));
}

void testCopyIsIndependent()
{
	Stack a;
	fill(a, 3);
	Stack b(a);
	b.push(99);
	a.pop();
	CHECK(b.pop() == 99);
	CHECK(holds(b, 3));
	CHECK(holds(a, 2));
}

void testCopyThenGrowAndShrink()
{
	Stack a;
	fill(a, 5);
	Stack b(a);
	fill(b, 1000, 5);
	CHECK(holds(b, 1005));
	b.push(1);
	CHECK(b.pop() == 1);
}

void testCopyOfCopy()
{
	Stack a;
	fill(a, 10);
	Stack b(a);
	Stack c(b);
	CHECK(holds(c, 10));
	CHECK(holds(b, 10));
	CHECK(holds(a, 10));
}

void testCopyInitSyntax()
{
	Stack a;
	fill(a, 4);
	Stack b = a;
	CHECK(holds(b, 4));
	CHECK(holds(a, 4));
}

static bool popAllByValue(Stack s, int n)
{
	return holds(s, n);
}

void testPassByValue()
{
	Stack a;
	fill(a, 20);
	CHECK(popAllByValue(a, 20));
	CHECK(holds(a, 20));
}


void testAssignLargerToSmaller()
{
	Stack big, small;
	fill(big, 1000);
	fill(small, 2, 500);
	small = big;
	CHECK(holds(small, 1000));
	CHECK(holds(big, 1000));
}

void testAssignSmallerToLarger()
{
	Stack big, small;
	fill(big, 1000);
	fill(small, 2, 500);
	big = small;
	CHECK(holds(big, 2, 500));
	CHECK(holds(small, 2, 500));
}

void testAssignEqualSize()
{
	Stack a, b;
	fill(a, 64);
	fill(b, 64, 1000);
	a = b;
	CHECK(holds(a, 64, 1000));
	CHECK(holds(b, 64, 1000));
}

void testAssignEmptyToNonEmpty()
{
	Stack empty, s;
	fill(s, 10);
	s = empty;
	CHECK(s.isEmpty());
	CHECK(s.pop() == 0);
	fill(s, 3);
	CHECK(holds(s, 3));
}

void testAssignNonEmptyToEmpty()
{
	Stack empty, s;
	fill(s, 10);
	empty = s;
	CHECK(holds(empty, 10));
	CHECK(holds(s, 10));
}

void testAssignEmptyToEmpty()
{
	Stack a, b;
	a = b;
	CHECK(a.isEmpty());
	CHECK(b.isEmpty());
}

void testAssignToEmptyCopy()
{
	Stack empty;
	Stack noBuffer(empty);
	Stack s;
	fill(s, 5);
	noBuffer = s;
	CHECK(holds(noBuffer, 5));
	noBuffer = empty;
	CHECK(noBuffer.isEmpty());
}

void testSelfAssign()
{
	Stack s;
	fill(s, 10);
	Stack& ref = s;
	s = ref;
	CHECK(holds(s, 10));

	Stack e;
	Stack& eref = e;
	e = eref;
	CHECK(e.isEmpty());
}

void testAssignIsIndependent()
{
	Stack a, b;
	fill(a, 3);
	b = a;
	b.push(99);
	a.pop();
	CHECK(b.pop() == 99);
	CHECK(holds(b, 3));
	CHECK(holds(a, 2));
}

void testChainedAssign()
{
	Stack a, b, c;
	fill(a, 7);
	c = b = a;
	CHECK(holds(c, 7));
	CHECK(holds(b, 7));
	CHECK(holds(a, 7));
}

void testAssignRepeatedly()
{
	Stack a, b, dst;
	fill(a, 500);
	fill(b, 3, 900);
	for (int i = 0; i < 10; i++) {
		dst = a;
		dst = b;
	}
	CHECK(holds(dst, 3, 900));
	dst = a;
	CHECK(holds(dst, 500));
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

	testCopyEmpty();
	testCopyNonEmpty();
	testCopyIsIndependent();
	testCopyThenGrowAndShrink();
	testCopyOfCopy();
	testCopyInitSyntax();
	testPassByValue();

	testAssignLargerToSmaller();
	testAssignSmallerToLarger();
	testAssignEqualSize();
	testAssignEmptyToNonEmpty();
	testAssignNonEmptyToEmpty();
	testAssignEmptyToEmpty();
	testAssignToEmptyCopy();
	testSelfAssign();
	testAssignIsIndependent();
	testChainedAssign();
	testAssignRepeatedly();

	if (failures == 0)
		printf("All tests pass\n");
	else
		printf("Failures: %d\n", failures);
	return failures != 0;
}
