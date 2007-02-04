// char_traits.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#include <vaucanson/misc/special_char_traits.hh>

#include <iostream>
#include <string>
#include <utility>
#include <cassert>

template <class Letter>
void
test_char_traits_for(Letter a, Letter b)
{
  typedef std::char_traits<Letter> traits;

  std::cout << "Checking char_traits<"
	    << typeid (Letter).name()
	    << ">." << std::endl;

  Letter l (a);

  // asign()
  traits::assign(l, b);
  assert(l == b);

  // eq()
  assert(traits::eq(l, b));
  assert(traits::eq(b, l));
  assert(not traits::eq(a, b));
  assert(not traits::eq(b, a));

  // lt()
  assert(traits::lt(a, b));
  assert(not traits::lt(a, a));
  assert(not traits::lt(b, a));

  // Tests with arrays.
  {
    Letter	t[] = { a, a, Letter () };
    Letter	u[] = { a, b, Letter () };
    Letter	z[] = { Letter () };

    // compare()
    assert(traits::compare(z, t, 0) == 0);
    assert(traits::compare(t, u, 2) < 0);
    assert(traits::compare(u, t, 2) > 0);
    assert(traits::compare(t, t, 2) == 0);

    // length()
    assert(traits::length(z) == 0);
    assert(traits::length(t) == 2);
    assert(traits::length(u) == 2);

    // find()
    assert(traits::find(t, 2, b) == 0);
    assert(traits::find(u, 2, b) == u + 1);
    assert(traits::find(z, 0, a) == 0);

    Letter	v[] = { a, b, a, b, a, Letter() };
    Letter	w[] = { a, b, a, b, a, Letter() };

    // move()
    traits::move(v, v + 1, 3);
    // v is now { b, a, b, b, a }.
    assert(traits::compare(v, w + 1, 3) == 0);
    assert(traits::compare(v, w, 5) != 0);
    traits::move(v, v, 5);
    assert(traits::compare(v, w + 1, 3) == 0);
    assert(traits::compare(v, w, 5) != 0);

    // copy()
    traits::copy(v, w, 5);
    assert(traits::compare(v, w, 5) == 0);
    traits::copy(v, w, 0);
    assert(traits::compare(v, w, 5) == 0);

    // assign()
    traits::assign(v, 5, a);
    traits::assign(w, 5, b);
    for (int i = 0; i < 5; ++i)
      {
	assert(v[i] == a);
	assert(w[i] == b);
      }
  } // End of tests on arrays.

  // FIXME: The following tests assume traits::eq_int_type() is correct.
  // FIXME: However, if it is not, some of the tests will fail and we will
  // FIXME: get an error.
  Letter			z = Letter ();

  // to_int_type() and eq_int_type()
  typename traits::int_type	ia = traits::to_int_type(a);
  typename traits::int_type	ib = traits::to_int_type(b);
  typename traits::int_type	iz = traits::to_int_type(z);
  typename traits::int_type	il = traits::to_int_type(l);
  assert(traits::eq_int_type(ia, ia));
  assert(traits::eq_int_type(ib, il));
  assert(traits::eq_int_type(il, ib));
  assert(not traits::eq_int_type(ia, ib));
  assert(not traits::eq_int_type(ib, ia));
  assert(not traits::eq_int_type(iz, ia));
  assert(not traits::eq_int_type(ia, iz));
  assert(not traits::eq_int_type(iz, ib));
  assert(not traits::eq_int_type(ib, iz));

  // to_char_type()
  assert(traits::to_char_type(ia) == a);
  assert(traits::to_char_type(ib) == b);
  assert(traits::to_char_type(iz) == z);
  assert(traits::to_char_type(il) == l);

  // eof() and eq_int_type() with eof.
  typename traits::int_type	eof = traits::eof();
  assert(traits::eq_int_type(eof, traits::eof()));
  assert(not traits::eq_int_type(eof, iz));
  assert(not traits::eq_int_type(iz, eof));
  assert(not traits::eq_int_type(eof, ia));
  assert(not traits::eq_int_type(ia, eof));
  assert(not traits::eq_int_type(eof, ib));
  assert(not traits::eq_int_type(ib, eof));

  // not_eof()
  typename traits::int_type	neof = traits::not_eof(eof);
  typename traits::int_type	nia = traits::not_eof(ia);
  typename traits::int_type	nib = traits::not_eof(ib);
  typename traits::int_type	niz = traits::not_eof(iz);
  assert(not traits::eq_int_type(neof, eof));
  assert(not traits::eq_int_type(nia, eof));
  assert(not traits::eq_int_type(nib, eof));
  assert(not traits::eq_int_type(niz, eof));
  assert(traits::eq_int_type(nia, ia));
  assert(traits::eq_int_type(nib, ib));
  assert(traits::eq_int_type(niz, iz));
}

int main()
{
  test_char_traits_for<char>(1, 10); // Ensures the tests are corrects.
  test_char_traits_for<int>(1, 10);
  test_char_traits_for<long int>(1, 10);
  test_char_traits_for<unsigned int>(1, 10);
  test_char_traits_for<unsigned long int>(1, 10);
  test_char_traits_for<float>(1, 10);
  test_char_traits_for<double>(1, 10);
  test_char_traits_for<long double>(1, 10);
  test_char_traits_for<int*>(reinterpret_cast<int*> (1),
			     reinterpret_cast<int*> (10));
  test_char_traits_for< std::pair<char, int> >(std::make_pair('a', 1),
					       std::make_pair('b', 10));
}

