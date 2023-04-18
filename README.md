# FunctionType
> C++ Metaprogramming Utility

A simple single-file implementation of a metaprogramming utility for function type deduction. <b>FunctionType</b> is a template utility struct implemented using explicit specialization. <i>ISO C++14</i>, <i>ISO C++17</i> and <i>ISO C++20</i> compatible.  
<i>This is a single-include library. No additional dependencies are required.</i>

Characteristics
---------
<b>FunctionType</b> is able to deduce the decayed function's type, arguments and return value for most function types (including lambdas). <b>FunctionType</b> supports the following qualifiers, and their permitted permutations:  
- const qualifier
- volatile qualifier
- mutable specifier
- reference qualifier
- rvalue reference qualifier
- noexcept qualifier (since <i>ISO C++17</i>)

Due to the changes to type deduction in <i>ISO C++17</i>, mainly due to the <i>P0012R1	Exception specification as part of the type system</i> feature, <i>ISO C++17</i> is the current default minimum supported version. If you would like to use the utility with <i>ISO C++14</i>, define <b>FUNCTION_TYPE_CPP14</b> before you include the FunctionType.h header. This workaround is needed due to MSC not initializing <b>__cplusplus</b> variable properly.

Installation
---------
Copy the <b>FunctionType.h</b> header to your project source files, or include directly from cloned path.

Usage
---------
```cpp
// Usage:
// FunctionType<[function type]>

// Example:
#include "FunctionType.h"
#include <functional>
int StaticFunction(int, float) { return 1; }
int main()
{
  FunctionType<decltype(&StaticFunction)>::ReturnType var = 0;
  std::function<FunctionType<decltype(&StaticFunction)>::Type> f = StaticFunction;
  return 0;
}

```
<b>Tests.cpp</b> has the full test suite, please refer to it for additional examples.

Limitations
---------
The following language limitations apply:
- Cannot be used with C-style variadic functions, as we cannot deduce the function argument types from ellipsis.
- Cannot be used with generic lambdas, as we cannot deduce the auto type at declaration.
- Cannot be used with class function overloads, as we cannot deduce the function overload from name alone (Note: it is possible to deduce the overload via a static cast to exact type).

Compatibility
---------
Tested with:
- g++ 7.4.0
- clang 6.0.0
- MSC 1920

Compiled with <i>ISO C++14</i>, <i>ISO C++17</i>, and <i>ISO C++20</i> flags.

License
---------
The MIT License (MIT)  
Copyright (c) 2023 Konstantin Udovickij  

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
