CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g

stack: TestStack.cpp Stack.cpp Stack.h
	$(CXX) $(CXXFLAGS) TestStack.cpp Stack.cpp -o stack

test: stack
	./stack

valgrind: stack
	valgrind --leak-check=full --error-exitcode=1 ./stack

clean:
	rm -f stack

.PHONY: test valgrind clean
