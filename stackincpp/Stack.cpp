#include "Stack.h"
#include <cstdio>
#include <cstdlib>
#define INITIAL_MEMORY 1

Stack::Stack()
{
	values = static_cast<int*>(malloc(sizeof(int) * INITIAL_MEMORY));
	length = 0;
	size = INITIAL_MEMORY;

	if (values == NULL) {
		fprintf(stderr, "Error: Cannot allocate the memory!\n");
		size = 0;
	}
}

Stack::~Stack()
{
	free(values);
}

void Stack::push(int element)
{
	if (size < length + 1) {
		int newSize = size > 0 ? size * 2 : INITIAL_MEMORY;
		int* tmp = static_cast<int*>(realloc(values, sizeof(int) * newSize));

		if (tmp == NULL) {
			fprintf(stderr, "Error: Cannot re-allocate the memory!\n");
			return;
		}

		values = tmp;
		size = newSize;
	}

	values[length] = element;
	length++;
}

int Stack::pop()
{
	if (length == 0) {
		printf("Error: pop from empty Stack\n");
		return 0;
	}

	int lastValue = values[length - 1];
	length--;

	if (size > INITIAL_MEMORY && length <= size / 4) {
		int* tmp = static_cast<int*>(realloc(values, sizeof(int) * (size / 2)));
		if (tmp != NULL) {
			values = tmp;
			size /= 2;
		}
	}

	return lastValue;
}

bool Stack::isEmpty() const
{
	return length == 0;
}
