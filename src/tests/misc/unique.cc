// unique.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2006 The Vaucanson Group.
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
#include <vaucanson/misc/unique.hh>
#include <cassert>
#include <set>
#include <string>

#define MAXITER 10000

using namespace vcsn::misc;

struct I : public unique::unifiable
{
  I(int x) : x_(x) {}

  int x_;
};
bool operator==(const I& i1, const I& i2)
{ return i1.x_ == i2.x_; }

struct A : public unique::unifiable
{ };

std::string tag;
bool operator==(const A&, const A&)
{
  tag += "A";
  return true;
}

int main()
{
  std::set<const I*> s;

  for (int i = 0; i < MAXITER; ++i)
    {
      const I *p = & unique::get(I(i));
      assert(s.find(p) == s.end());
      s.insert(p);
    }

  const A *p1 = & unique::get(A());
  const A *p2 = & unique::get(A());
  const A *p3 = & unique::get(A());
  assert(tag.size() != 0);
  assert(p1 == p2 && p2 == p3);
  return 0;
}

