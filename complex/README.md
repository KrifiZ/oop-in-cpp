# complex

`Complex` number class with public `real` / `imag` fields, compound assignment operators (`+=`, `-=`, `*=`, `/=`),
binary operators, `==` / `!=`, `amplitude()`, `phase()` and `operator<<`.

- Implicit conversion from `double` makes mixed expressions like `7.2 + a` and `3.5 == c` work.
- Division by `0` throws `std::invalid_argument`.

## Build & run (WSL / Linux)

```
make test       # unit tests
make valgrind   # tests under valgrind, fails on leaks/errors
```

## Expected results checked in Wolfram Alpha

| Test | Query | Expected |
|---|---|---|
| `testConstNumbers` | [`{(1+i)+(2-3i), (1+i)-(2-3i), (1+i)*(2-3i), (5-i)/(2-3i)}`](https://www.wolframalpha.com/input?i=%7B%281%2Bi%29%2B%282-3i%29%2C%20%281%2Bi%29-%282-3i%29%2C%20%281%2Bi%29%2A%282-3i%29%2C%20%285-i%29%2F%282-3i%29%7D) | `{3-2i, -1+4i, 5-i, 1+i}` |
| `testAmplitudePhase` | [`{abs(3+4i), arg(i)}`](https://www.wolframalpha.com/input?i=%7Babs%283%2B4i%29%2C%20arg%28i%29%7D) | `{5, π/2}` |
| `testChainedAdd` / `testChainedMultiply` | [`{(1+2i)+((3-i)+3.5), (1+2i)*((3-i)*2), ((1+2i)*(3-i))*2}`](https://www.wolframalpha.com/input?i=%7B%281%2B2i%29%2B%28%283-i%29%2B3.5%29%2C%20%281%2B2i%29%2A%28%283-i%29%2A2%29%2C%20%28%281%2B2i%29%2A%283-i%29%29%2A2%7D) | `{7.5+i, 10+10i, 10+10i}` |
| `testChainedDivide` | [`{(10+10i)/((6-2i)/2), ((10+10i)/(6-2i))/2}`](https://www.wolframalpha.com/input?i=%7B%2810%2B10i%29%2F%28%286-2i%29%2F2%29%2C%20%28%2810%2B10i%29%2F%286-2i%29%29%2F2%7D) | `{2+4i, 0.5+i}` |
| `testMixedWithDouble` | [`{(1+2i)+7.2, (3-i)*5.1}`](https://www.wolframalpha.com/input?i=%7B%281%2B2i%29%2B7.2%2C%20%283-i%29%2A5.1%7D) | `{8.2+2i, 15.3-5.1i}` |
| `testDivisionByZero` | [`(1+2i)/0`](https://www.wolframalpha.com/input?i=%281%2B2i%29%2F0) | complex infinity |
