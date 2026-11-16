# polynomial

`Poly` class representing a polynomial. Only non-zero coefficients are stored, in a `std::map<power, coefficient>`
(`x^1000 + 6x^350 + 15` stores 3 coefficients, not 1001).

- `p[n] = c` sets a coefficient (assigning `0` removes it), `p[n]` reads it (`0` if it is not stored). A negative power throws `std::invalid_argument`.
- Compound assignment operators (`+=`, `-=`, `*=`), binary `+`, `-`, `*`, evaluation `p(x)` and `operator<<` (`p1 - p1` prints `0`).
- Implicit conversion from `double` makes mixed expressions like `2.4 + p1` and `Poly p2 = 2.6` work.
- **Pass by value:** `std::map` copies itself, so the compiler-generated copy constructor, copy assignment and destructor are correct. No manual memory management as in [stackcopy](../stackcopy/).

## Function template version

`display(T& p)` from the course's `TestPolyWithFunctionTemplate.cpp` (copied into `TestPoly.cpp`) is called as `display(p2)` (`T = Poly`) and `display<const Poly>(p2)` (`T = const Poly`).
With `T = Poly` the coefficients are read through the **non-const** `operator[]`. If it returned `double&` (`return coefficients[power];`),
reading `p2[5]` and `p2[3]` would insert zero coefficients into the map just by displaying the polynomial.
That's why the non-const `operator[]` returns `Poly::Coefficient`: reading through it never stores anything, only assignment does.
`testFunctionTemplate` and `testSparseStorage` check this.

## Build & run (WSL / Linux)

```
make test       # unit tests
make valgrind   # tests under valgrind, fails on leaks/errors
```

## Expected results checked in Wolfram Alpha

`p1 = -2.3x^3 + 5x^2 - 4.5`, `p2 = x^4 - 7x^2 + 3x + 2.6`

| Test | Query | Expected |
|---|---|---|
| `testAddition` / `testSubtraction` | [`expand({p1+p2, p1-p2})`](https://www.wolframalpha.com/input?i=expand%28%7B%28-2.3x%5E3%2B5x%5E2-4.5%29%2B%28x%5E4-7x%5E2%2B3x%2B2.6%29%2C%20%28-2.3x%5E3%2B5x%5E2-4.5%29-%28x%5E4-7x%5E2%2B3x%2B2.6%29%7D%29) | `{x^4 - 2.3x^3 - 2x^2 + 3x - 1.9, -x^4 - 2.3x^3 + 12x^2 - 3x - 7.1}` |
| `testAddition` / `testSubtraction` / `testMultiplication` | [`expand({p1+2.4, 5.3-p1, 6.7*p1})`](https://www.wolframalpha.com/input?i=expand%28%7B%28-2.3x%5E3%2B5x%5E2-4.5%29%2B2.4%2C%205.3-%28-2.3x%5E3%2B5x%5E2-4.5%29%2C%206.7%2A%28-2.3x%5E3%2B5x%5E2-4.5%29%7D%29) | `{-2.3x^3 + 5x^2 - 2.1, 2.3x^3 - 5x^2 + 9.8, -15.41x^3 + 33.5x^2 - 30.15}` |
| `testMultiplication` | [`expand(p1*p2)`](https://www.wolframalpha.com/input?i=expand%28%28-2.3x%5E3%2B5x%5E2-4.5%29%2A%28x%5E4-7x%5E2%2B3x%2B2.6%29%29) | `-2.3x^7 + 5x^6 + 16.1x^5 - 46.4x^4 + 9.02x^3 + 44.5x^2 - 13.5x - 11.7` |
| `testValue` | [`{p1(3.9), p2(-2.8)}`](https://www.wolframalpha.com/input?i=%7B-2.3%2A3.9%5E3%2B5%2A3.9%5E2-4.5%2C%20%28-2.8%29%5E4-7%28-2.8%29%5E2%2B3%28-2.8%29%2B2.6%7D) | `{-64.8837, 0.7856}` |
