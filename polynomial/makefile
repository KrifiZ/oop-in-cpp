CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
SHELL = /bin/bash
.SHELLFLAGS = -o pipefail -c
VALGRIND = valgrind --leak-check=full --error-exitcode=1 -q

all: testpoly demo

testpoly: TestPoly.cpp Poly.cpp Poly.h
	$(CXX) $(CXXFLAGS) TestPoly.cpp Poly.cpp -o testpoly

demo: TestPolyWithFunctionTemplate.cpp Poly.cpp Poly.h
	$(CXX) $(CXXFLAGS) TestPolyWithFunctionTemplate.cpp Poly.cpp -o demo

# asserts + demo output compared with expected_output.txt
test: all
	./testpoly
	./demo | diff -u expected_output.txt -
	@echo "Demo output matches expected_output.txt"

# the same, under valgrind (fails on leaks / memory errors)
valgrind: all
	$(VALGRIND) ./testpoly
	$(VALGRIND) ./demo | diff -u expected_output.txt -
	@echo "Valgrind clean, demo output matches expected_output.txt"

clean:
	rm -f testpoly demo

.PHONY: all test valgrind clean
