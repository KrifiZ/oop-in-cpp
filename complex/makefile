CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g

complex: TestComplex.cpp Complex.cpp Complex.h
	$(CXX) $(CXXFLAGS) TestComplex.cpp Complex.cpp -o complex

test: complex
	./complex

valgrind: complex
	valgrind --leak-check=full --error-exitcode=1 ./complex

clean:
	rm -f complex

.PHONY: test valgrind clean
