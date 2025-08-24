# punter

A header-only C++ library to parse mathematical expressions as represented by strings. To do so we use the [shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm).

The library is the single `shunt.hpp` header file.

For example:

```cpp
#include "shunt.hpp"
using namespace std;

string postfix = shunt::parse("3 + 3 + 5 / 200")  // returns "33+5200/+"
```

## Build and test

We use [CMake](https://cmake.org/cmake/help/latest/index.html) to build and test the project. Strictly speaking, building is not needed as it is header-only.

To build and test the project (from the `build` directory):

```bash
cmake ..
cmake --build .
ctest --verbose
```
