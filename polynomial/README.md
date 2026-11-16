# polynomial

`Poly` class: a sparse polynomial stored as `std::map<power, coefficient>` holding only non-zero coefficients
(`x^1000 + 6x^350 + 15` stores 3 entries, not 1001).

- `p[n] = c` sets a coefficient (assigning `0` removes it), `p[n]` reads it (`0` if missing).
- `+`, `-`, `*` (also mixed with `double`, e.g. `2.4 + p`), `p(x)` evaluates, `operator<<` prints (`p - p` prints `0`).
- Pass by value works: `std::map` copies itself, so the compiler-generated copy constructor / assignment are correct (rule of zero).

## Function template version

`TestPolyWithFunctionTemplate.cpp` (the course's test, unchanged) calls `display(p2)` with `T = Poly` and `display<const Poly>(p2)`.
The first one reads `p[5]` and `p[3]` through the **non-const** `operator[]`. If that returned `double&` (`return coef[n];`),
just *displaying* the polynomial would insert zero coefficients into the map. That's why non-const `operator[]` returns
a small proxy (`Poly::Ref`): reading never creates an entry, only assignment does.

## Build & run (WSL / Linux)

```
make test       # TestPoly asserts + demo output diffed against expected_output.txt
make valgrind   # the same under valgrind, fails on leaks/errors or output mismatch
```
