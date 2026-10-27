# stackcopy

`Stack` from [stackincpp](../stackincpp/) extended with a copy constructor and a copy assignment operator.
`getLength()` / `getSize()` were removed.

- **Copy constructor** allocates exactly `other.length` ints, and nothing when copying an empty stack.
- **Copy assignment** reuses the existing buffer when it is big enough; only when it is too small is it freed and a new one of exactly `other.length` ints allocated. Self-assignment is a no-op.

## Build & run (WSL / Linux)

```
make test       # unit tests
make valgrind   # tests under valgrind, fails on leaks/errors
```
