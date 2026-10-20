#pragma once

class Stack {
public:
	Stack();
	~Stack();

	void push(int element);
	int pop();
	bool isEmpty() const;

	int getLength() const { return length; }
	int getSize() const { return size; }

private:
	int* values;
	int length;
	int size;
};
