/* ************************************************************************* */
/* The MIT License(MIT)                                                      */
/* Copyright(c) 2023 Konstantin Udovickij                                    */
/*                                                                           */
/* Permission is hereby granted, free of charge, to any person obtaining a   */
/* copy of this software and associated documentation files (the "Software"),*/
/* to deal in the Software without restriction, including without limitation */
/* the rights to use, copy, modify, merge, publish, distribute, sublicense,  */
/* and /or sell copies of the Software, and to permit persons to whom the    */
/* Software is furnished to do so, subject to the following conditions:      */
/*                                                                           */
/* The above copyright notice and this permission notice shall be included   */
/* in all copies or substantial portions of the Software.                    */
/*                                                                           */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN */
/* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,  */
/* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR     */
/* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE */
/* USE OR OTHER DEALINGS IN THE SOFTWARE.                                    */
/* ************************************************************************* */

// Define this for ISO C++14 support
// #define FUNCTION_TYPE_CPP14
#include "FunctionType.h"
#include <iostream>
#include <typeinfo>

// Name printer
template <typename T> void PrintT() { std::cout << typeid(T).name() << std::endl; };

// Explicit deduction
template <typename Fn>
void Tester()
{
  // Please note: typeid(x).name() is not required to produce a meaningful string
  // by the standard. Refer to your compiler's settings to determine how to get
  // a "nice" string from typeid.
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "Function: " << typeid(Fn).name() << std::endl;
  PrintT<typename FunctionType<Fn>::Type>();
  PrintT<typename FunctionType<Fn>::ArgumentsType>();
  PrintT<typename FunctionType<Fn>::ReturnType>();
  std::cout << "------------------------------------------" << std::endl;
}

// Implicit deduction
template <typename Fn>
void Tester(Fn)
{
  Tester<Fn>();
}

struct Class
{
  short overload(int, float) { return 1; }
  short overload(int, float) const { return 1; }
  short overload(int, float) volatile { return 1; }
  short overload_noexcept(int, float) noexcept { return 1; }
  short rc(int, float)& { return 1; }
  short rc(int, float) const& { return 1; }
  short overload(int, float) const volatile { return 1; }
  short overload_noexcept(int, float) const noexcept { return 1; }
  short overload_noexcept(int, float) volatile noexcept { return 1; }
  short rc(int, float) volatile& { return 1; }
  short rc_noexcept(int, float) & noexcept { return 1; }
  short rc(int, float) const volatile& { return 1; }
  short rc_noexcept(int, float) const& noexcept { return 1; }
  short overload_noexcept(int, float) const volatile noexcept { return 1; }
  short rc_noexcept(int, float) volatile& noexcept { return 1; }
  short rc_noexcept(int, float) const volatile& noexcept { return 1; }
  template <typename ...Args>
  short variadic_template(Args... args) { return 1; }

  short overload_variadic(...) { return 1; }
  short overload_variadic(...) const { return 1; }
  short overload_variadic(...) volatile { return 1; }
  short overload_noexcept_variadic(...) noexcept { return 1; }
  short rc_variadic(...)& { return 1; }
  short rc_variadic(...) const& { return 1; }
  short overload_variadic(...) const volatile { return 1; }
  short overload_noexcept_variadic(...) const noexcept { return 1; }
  short overload_noexcept_variadic(...) volatile noexcept { return 1; }
  short rc_variadic(...) volatile& { return 1; }
  short rc_noexcept_variadic(...) & noexcept { return 1; }
  short rc_variadic(...) const volatile& { return 1; }
  short rc_noexcept_variadic(...) const& noexcept { return 1; }
  short overload_noexcept_variadic(...) const volatile noexcept { return 1; }
  short rc_noexcept_variadic(...) volatile& noexcept { return 1; }
  short rc_noexcept_variadic(...) const volatile& noexcept { return 1; }
};

float static_mutable(double, float) { return 1.0f; }
float static_mutable_variadic(...) { return 1.0f; }
float static_mutable_noexcept(double, float) noexcept { return 1.0f; }
float static_mutable_variadic_noexcept(...) noexcept { return 1.0f; }
template <typename ...Args>
float static_mutable_variadic_template(Args... args) noexcept { return 1.0f; }

int main(void)
{
  auto lambda = [](int) { return 1.0f; };
  auto lambda_mutable = [](int) mutable { return 1.0f; };
  auto lambda_variadic = [](...) { return 1.0f; };
  auto lambda_mutable_variadic = [](...) mutable { return 1.0f; };
  auto lambda_noexcept = [](int) noexcept { return 1.0f; };
  auto lambda_mutable_noexcept = [](int) mutable noexcept { return 1.0f; };
  auto lambda_noexcept_variadic = [](...) noexcept { return 1.0f; };
  auto lambda_mutable_noexcept_variadic = [](...) mutable noexcept { return 1.0f; };
  auto lambda_generic = [](auto var0, auto var1) -> auto { return var0 + var1; };

  std::cout << std::endl << "Explicit functor's operator, implicit deduction" << std::endl << std::endl;

  Tester(&decltype(lambda)::operator());
  Tester(&decltype(lambda_mutable)::operator());
  //Tester(&decltype(lambda_variadic)::operator()); // not supported
  //Tester(&decltype(lambda_mutable_variadic)::operator()); // not supported
  Tester(&decltype(lambda_noexcept)::operator());
  Tester(&decltype(lambda_mutable_noexcept)::operator());
  //Tester(&decltype(lambda_noexcept_variadic)::operator()); // not supported
  //Tester(&decltype(lambda_mutable_noexcept_variadic)::operator()); // not supported
  //Tester(&decltype(lambda_generic)::operator()); // not supported

  std::cout << std::endl << "Explicit functor's operator, explicit deduction" << std::endl << std::endl;

  Tester<decltype(&decltype(lambda)::operator())>();
  Tester<decltype(&decltype(lambda_mutable)::operator())>();
  //Tester<decltype(&decltype(lambda_variadic)::operator())>(); // not supported
  //Tester<decltype(&decltype(lambda_mutable_variadic)::operator())>(); // not supported
  Tester<decltype(&decltype(lambda_noexcept)::operator())>();
  Tester<decltype(&decltype(lambda_mutable_noexcept)::operator())>();
  //Tester(&decltype(lambda_noexcept_variadic)::operator()); // not supported
  //Tester(&decltype(lambda_mutable_noexcept_variadic)::operator()); // not supported
  //Tester<decltype(&decltype(lambda_generic)::operator())>(); // not supported

  std::cout << std::endl << "Implicit functor's operator deduction, implicit deduction" << std::endl << std::endl;

  Tester(lambda);
  Tester(lambda_mutable);
  //Tester(lambda_variadic); // not supported
  //Tester(lambda_mutable_variadic); // not supported
  Tester(lambda_noexcept);
  Tester(lambda_mutable_noexcept);
  //Tester(lambda_noexcept_variadic); // not supported
  //Tester(lambda_mutable_noexcept_variadic); // not supported
  //Tester(lambda_generic); // not supported

  std::cout << std::endl << "Implicit functor's operator deduction, explicit deduction" << std::endl << std::endl;

  Tester<decltype(lambda)>();
  Tester<decltype(lambda_mutable)>();
  //Tester<decltype(lambda_variadic)>(); // not supported
  //Tester<decltype(lambda_mutable_variadic)>(); // not supported
  Tester<decltype(lambda_noexcept)>();
  Tester<decltype(lambda_mutable_noexcept)>();
  //Tester<decltype(lambda_noexcept_variadic)>(); // not supported
  //Tester<decltype(lambda_mutable_noexcept_variadic)>(); // not supported
  //Tester<decltype(lambda_generic)>(); // not supported

  std::cout << std::endl << "Statics, implicit deduction" << std::endl << std::endl;

  Tester(&static_mutable);
  //Tester(&static_mutable_variadic); // not supported
  Tester(&static_mutable_noexcept);
  //Tester(&static_mutable_variadic_noexcept); // not supported
  Tester(&static_mutable_variadic_template<int, float>);

  std::cout << std::endl << "Statics, explicit deduction" << std::endl << std::endl;

  Tester<decltype(&static_mutable)>();
  //Tester<decltype(&static_mutable_variadic)>(); // not supported
  Tester<decltype(&static_mutable_noexcept)>();
  //Tester<decltype(&static_mutable_variadic_noexcept)>(); // not supported
  Tester<decltype(&static_mutable_variadic_template<int, float>)>();

  std::cout << std::endl << "Class methods, explicit deduction" << std::endl << std::endl;

  Tester<decltype(static_cast<short(Class::*)(int, float)>(&Class::overload))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const>(&Class::overload))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)volatile>(&Class::overload))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)noexcept>(&Class::overload_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)&>(&Class::rc))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const&>(&Class::rc))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const volatile>(&Class::overload))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const noexcept>(&Class::overload_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)volatile noexcept>(&Class::overload_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)volatile&>(&Class::rc))>();
  Tester<decltype(static_cast<short(Class::*)(int, float) & noexcept>(&Class::rc_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const volatile&>(&Class::rc))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const& noexcept>(&Class::rc_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const volatile noexcept>(&Class::overload_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)volatile& noexcept>(&Class::rc_noexcept))>();
  Tester<decltype(static_cast<short(Class::*)(int, float)const volatile& noexcept>(&Class::rc_noexcept))>();
  Tester<decltype(&Class::variadic_template<int, float>)>();

  //Tester<decltype(static_cast<short(Class::*)(...)>(&Class::overload_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const>(&Class::overload_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)volatile>(&Class::overload_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)noexcept>(&Class::overload_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)&>(&Class::rc_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const&>(&Class::rc_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const volatile>(&Class::overload_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const noexcept>(&Class::overload_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)volatile noexcept>(&Class::overload_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)volatile&>(&Class::rc_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...) & noexcept>(&Class::rc_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const volatile&>(&Class::rc_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const& noexcept>(&Class::rc_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const volatile noexcept>(&Class::overload_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)volatile& noexcept>(&Class::rc_noexcept_variadic))>(); // not supported
  //Tester<decltype(static_cast<short(Class::*)(...)const volatile& noexcept>(&Class::rc_noexcept_variadic))>(); // not supported

  std::cout << std::endl << "Class methods, implicit deduction" << std::endl << std::endl;

  Tester(static_cast<short(Class::*)(int, float)>(&Class::overload));
  Tester(static_cast<short(Class::*)(int, float)const>(&Class::overload));
  Tester(static_cast<short(Class::*)(int, float)volatile>(&Class::overload));
  Tester(static_cast<short(Class::*)(int, float)noexcept>(&Class::overload_noexcept));
  Tester(static_cast<short(Class::*)(int, float)&>(&Class::rc));
  Tester(static_cast<short(Class::*)(int, float)const&>(&Class::rc));
  Tester(static_cast<short(Class::*)(int, float)const volatile>(&Class::overload));
  Tester(static_cast<short(Class::*)(int, float)const noexcept>(&Class::overload_noexcept));
  Tester(static_cast<short(Class::*)(int, float)volatile noexcept>(&Class::overload_noexcept));
  Tester(static_cast<short(Class::*)(int, float)volatile&>(&Class::rc));
  Tester(static_cast<short(Class::*)(int, float) & noexcept>(&Class::rc_noexcept));
  Tester(static_cast<short(Class::*)(int, float)const volatile&>(&Class::rc));
  Tester(static_cast<short(Class::*)(int, float)const& noexcept>(&Class::rc_noexcept));
  Tester(static_cast<short(Class::*)(int, float)const volatile noexcept>(&Class::overload_noexcept));
  Tester(static_cast<short(Class::*)(int, float)volatile& noexcept>(&Class::rc_noexcept));
  Tester(static_cast<short(Class::*)(int, float)const volatile& noexcept>(&Class::rc_noexcept));
  Tester(&Class::variadic_template<int, float>);

  //Tester(static_cast<short(Class::*)(...)>(&Class::overload_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const>(&Class::overload_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)volatile>(&Class::overload_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)noexcept>(&Class::overload_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)&>(&Class::rc_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const&>(&Class::rc_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const volatile>(&Class::overload_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const noexcept>(&Class::overload_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)volatile noexcept>(&Class::overload_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)volatile&>(&Class::rc_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...) & noexcept>(&Class::rc_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const volatile&>(&Class::rc_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const& noexcept>(&Class::rc_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const volatile noexcept>(&Class::overload_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)volatile& noexcept>(&Class::rc_noexcept_variadic)); // not supported
  //Tester(static_cast<short(Class::*)(...)const volatile& noexcept>(&Class::rc_noexcept_variadic)); // not supported

  return 0;
}