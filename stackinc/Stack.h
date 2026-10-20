#pragma once

typedef struct {
	int* values;
	int length;
	int size;
} Stack;

void init(Stack* s);
void destroy(Stack* s);
void push(Stack* s, int element);
int pop(Stack* s);
bool isEmpty(const Stack* s);
