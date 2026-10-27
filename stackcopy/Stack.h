#pragma once

class Stack {
public:
	Stack();
	Stack(const Stack& other);
	~Stack();

	Stack& operator=(const Stack& other);

	void push(int element);
	int pop();
	bool isEmpty() const;

private:
	int* values;
	int length;
	int size;
};
