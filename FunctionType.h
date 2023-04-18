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

#ifndef FUNCTION_TYPE
#define FUNCTION_TYPE
#pragma once

#include <tuple>
#include <cstddef>

template <class>
constexpr bool AlwaysFalse = false;

template <class Return, typename ...Args>
struct FunctionTypeSupported
{
  using Type = Return(Args...);
  using ArgumentsType = std::tuple<Args...>;
  using ReturnType = Return;
};

template <class Return>
struct FunctionTypeUnsupported
{
  using Type = std::nullptr_t;
  using ArgumentsType = std::nullptr_t;
  using ReturnType = std::nullptr_t;
  static_assert(AlwaysFalse<Return>, "FunctionType does not support non-template (C-style) variadic functions.");
};

// Lambda pass-through

template <class Lambda>
struct FunctionType
{
  using LambdaType = decltype(&Lambda::operator());
  using Type = typename FunctionType<LambdaType>::Type;
  using ArgumentsType = typename FunctionType<LambdaType>::ArgumentsType;
  using ReturnType = typename FunctionType<LambdaType>::ReturnType;
};

#define FUNCTION_TYPE_BOILERPLATE(...) template <class Return, typename ...Args>\
struct FunctionType <Return(*)(Args...)__VA_ARGS__> : public FunctionTypeSupported<Return, Args...> {};
#define FUNCTION_TYPE_CLASS_BOILERPLATE(...) template <class Return, class Class, typename ...Args>\
struct FunctionType <Return(Class::*)(Args...)__VA_ARGS__> : public FunctionTypeSupported<Return, Args...> {};
#define FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(...) template <class Return, class Class>\
struct FunctionType <Return(Class::*)(...)__VA_ARGS__> : public FunctionTypeUnsupported<Return> {};
#define FUNCTION_TYPE_UNSUPPORTED_BOILERPLATE(...) template <class Return>\
struct FunctionType <Return(*)(...)__VA_ARGS__> : public FunctionTypeUnsupported<Return> {};

// Supported types

FUNCTION_TYPE_CLASS_BOILERPLATE();
FUNCTION_TYPE_CLASS_BOILERPLATE(const);
FUNCTION_TYPE_CLASS_BOILERPLATE(volatile);
FUNCTION_TYPE_CLASS_BOILERPLATE(const volatile);
FUNCTION_TYPE_CLASS_BOILERPLATE(&);
FUNCTION_TYPE_CLASS_BOILERPLATE(const&);
FUNCTION_TYPE_CLASS_BOILERPLATE(volatile&);
FUNCTION_TYPE_CLASS_BOILERPLATE(const volatile&);
FUNCTION_TYPE_CLASS_BOILERPLATE(&&);
FUNCTION_TYPE_CLASS_BOILERPLATE(const&&);
FUNCTION_TYPE_CLASS_BOILERPLATE(volatile&&);
FUNCTION_TYPE_CLASS_BOILERPLATE(const volatile&&);
FUNCTION_TYPE_BOILERPLATE();

#if !defined(FUNCTION_TYPE_CPP14)
FUNCTION_TYPE_CLASS_BOILERPLATE(noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(const noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(volatile noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(const volatile noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(&noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(const& noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(volatile& noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(const volatile& noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(&& noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(const&& noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(volatile&& noexcept);
FUNCTION_TYPE_CLASS_BOILERPLATE(const volatile&& noexcept);
FUNCTION_TYPE_BOILERPLATE(noexcept);
#endif // !FUNCTION_TYPE_CPP14

// Unsupported types

FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE();
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(volatile);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const volatile);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(volatile&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const volatile&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(&&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const&&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(volatile&&);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const volatile&&);
FUNCTION_TYPE_UNSUPPORTED_BOILERPLATE();

#if !defined(FUNCTION_TYPE_CPP14)
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(volatile noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const volatile noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(volatile& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const volatile& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(&& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const&& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(volatile&& noexcept);
FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE(const volatile&& noexcept);
FUNCTION_TYPE_UNSUPPORTED_BOILERPLATE(noexcept);
#endif // !FUNCTION_TYPE_CPP14

#undef FUNCTION_TYPE_BOILERPLATE
#undef FUNCTION_TYPE_CLASS_BOILERPLATE
#undef FUNCTION_TYPE_CLASS_UNSUPPORTED_BOILERPLATE
#undef FUNCTION_TYPE_UNSUPPORTED_BOILERPLATE

#endif // FUNCTION_TYPE
