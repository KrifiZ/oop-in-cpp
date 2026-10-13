#include "Stack.h"
#include <stdio.h>
#include <limits.h>

static int failures = 0;

#define CHECK(cond) if (!(cond)) failures++

void testInit(void) {
    Stack s; init(&s);
    CHECK(isEmpty(&s));
    CHECK(s.length == 0);
    CHECK(s.size == 1);
    destroy(&s);
}

void testPopEmpty(void) {
    Stack s; init(&s);
    CHECK(pop(&s) == 0);
    CHECK(isEmpty(&s));
    CHECK(s.length == 0);
    destroy(&s);
}

void testPushEmpty(void) {
    Stack s; init(&s);
    push(&s, 42);
    CHECK(!isEmpty(&s));
    CHECK(s.length == 1);
    CHECK(pop(&s) == 42);
    CHECK(isEmpty(&s));
    destroy(&s);
}

void testPushZero(void) {
    Stack s; init(&s);
    push(&s, 0);
    CHECK(!isEmpty(&s));
    CHECK(pop(&s) == 0);
    CHECK(isEmpty(&s));
    destroy(&s);
}

void testExtremeValues(void) {
    Stack s; init(&s);
    push(&s, INT_MIN);
    push(&s, -1);
    push(&s, INT_MAX);
    CHECK(pop(&s) == INT_MAX);
    CHECK(pop(&s) == -1);
    CHECK(pop(&s) == INT_MIN);
    destroy(&s);
}

void testInterleaved(void) {
    Stack s; init(&s);
    push(&s, 1);
    push(&s, 2);
    CHECK(pop(&s) == 2);
    push(&s, 3);
    push(&s, 4);
    CHECK(pop(&s) == 4);
    CHECK(pop(&s) == 3);
    CHECK(pop(&s) == 1);
    CHECK(isEmpty(&s));
    destroy(&s);
}

void testReuseAfterEmpty(void) {
    Stack s; init(&s);
    for (int round = 0; round < 3; round++) {
        for (int i = 0; i < 1000; i++) push(&s, i);
        for (int i = 999; i >= 0; i--) CHECK(pop(&s) == i);
        CHECK(isEmpty(&s));
        CHECK(s.size == 1);
    }
    destroy(&s);
}

void testManyElements(void) {
    Stack s; init(&s);
    const int MAX = 100000;
    for (int i = 0; i < MAX; i++) push(&s, i);
    CHECK(s.length == MAX);

    int ok = 1;
    for (int i = MAX - 1; i >= 0; i--) {
        if (pop(&s) != i) { ok = 0; break; }
    }
    CHECK(ok);
    CHECK(isEmpty(&s));
    destroy(&s);
}

void testNull(void) {
    CHECK(pop(NULL) == 0);
    push(NULL, 5);       
    CHECK(isEmpty(NULL));
}

int main(void) {
    testInit();
    testPopEmpty();
    testPushEmpty();
    testPushZero();
    testExtremeValues();
    testInterleaved();
    testReuseAfterEmpty();
    testManyElements();
    testNull();

    if (failures == 0) printf("All tests passes\n");
    else printf("Failures: %d\n", failures);
    return failures != 0;
}
