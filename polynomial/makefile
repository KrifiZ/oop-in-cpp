CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g

poly: TestPoly.cpp Poly.cpp Poly.h
	$(CXX) $(CXXFLAGS) TestPoly.cpp Poly.cpp -o poly

test: poly
	./poly

valgrind: poly
	valgrind --leak-check=full --error-exitcode=1 ./poly

clean:
	rm -f poly

.PHONY: test valgrind clean
