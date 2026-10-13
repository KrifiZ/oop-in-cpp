# stackinc

Dynamically growing stack of `int` values in C.

## API (`Stack.h`)

| Function | Description |
|---|---|
| `void init(Stack* s)` | Initializes an empty stack |
| `void destroy(Stack* s)` | Frees the stack's memory |
| `void push(Stack* s, int element)` | Pushes an element (doubles capacity when full) |
| `int pop(Stack* s)` | Pops the top element; returns `0` on an empty stack (halves capacity at 1/4 usage) |
| `bool isEmpty(const Stack* s)` | Returns `true` if the stack is empty |

## Build and test

```sh
make        # builds ./main
make test   # builds and runs the tests
make clean  # removes the binary
```
