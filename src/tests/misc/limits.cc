// limits.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <vaucanson/misc/limits.hh>
#include <tests/check/tester.hh>

template <typename T>
void print_attr(T attr)
{
  std::cout << attr << std::endl;
}

template <>
void print_attr<signed char>(signed char attr)
{
  std::cout << static_cast<int>(attr) << std::endl;
}

template <>
void print_attr<unsigned char>(unsigned char attr)
{
  std::cout << static_cast<unsigned>(attr) << std::endl;
}

#define NATTR(Attr)  \
  std::cout << #Attr "\t:"; print_attr(vcsn::misc::limits<T>::Attr);

template<typename T>
void test_limits()
{
  TEST_GROUP(std::string("numeric limits for ") + typeid(T).name());
  NATTR(digits);
  NATTR(digits10);
  NATTR(is_specialized);
  NATTR(min());
  NATTR(max());
  NATTR(has_infinity);
  NATTR(has_quiet_NaN);
  NATTR(is_signed);
  NATTR(is_integer);
  NATTR(is_exact);
  NATTR(radix);
  NATTR(is_iec559);
  NATTR(is_bounded);
  NATTR(is_modulo);
}

int main()
{
  test_limits<bool>();
  test_limits<signed char>();
  test_limits<unsigned char>();
  test_limits<int>();
  test_limits<unsigned int>();
  test_limits<float>();
}
