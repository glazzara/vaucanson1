// bitset.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003 The Vaucanson Group.
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
#include <vaucanson/misc/bitset.hh>
#include <sstream>
#include <cassert>

using namespace utility;

int main()
{
  const Bitset::value_type	thearray[] = {42, 51, 505, 33, 806};
  const Bitset::size_type	thesize = sizeof (thearray) / sizeof (int);
  const Bitset::data_type	data[] = { 0x0000F000, 0x0000000F };

  Bitset	set0(51);
  Bitset	set1(64, data);
  Bitset	set2(set1);
  Bitset	set3(thearray, thearray + thesize);

  // Test the copy constructor and operator ==.
  assert(set1 == set2);

  // Test operator =.
  set2 = set3;
  assert(set2 == set3);

  // Test iterators.
  unsigned i = 0;
  for (Bitset::iterator it = set3.begin(); it != set3.end(); ++it)
    ++i;
  assert(i == thesize);

  i = 0;
  for (Bitset::const_iterator it = set3.begin(); it != set3.end(); ++it)
    ++i;
  assert(i == thesize);

  // Test reverse iterators.
  Bitset::reverse_iterator rit = set3.rbegin();
  assert(*rit == 806);
  ++rit;
  assert(*rit == 505);

  // Tricky test on iterators.
  Bitset::const_iterator cit = set3.begin(); // 33
  ++cit; // 42
  ++cit; // 51
  assert(*cit == 51);
  --cit; // 42
  assert(*cit == 42);
  ++cit; // 51
  ++cit; // 505
  ++cit; // 806
  --cit; // 505
  --cit; // 51
  assert(*cit == 51);

  // This is ugly and should be avoided for normal use, but the actual Bitset
  // implementation should behave like this.
  assert(static_cast<unsigned int> (*set0.end()) == set0.max_size());

  // Test empty().
  assert(set0.empty());
  assert(!set1.empty());

  // Test size().
  assert(set3.size() == thesize);
  assert(set3.max_size() == 807);

  // Test insert().
  std::pair<Bitset::iterator, bool> p = set0.insert(6);
  assert(*p.first == 6);
  assert(p.second);
  assert(set0.count(6) > 0);

  p = set0.insert(6);
  assert(!p.second);

  Bitset::iterator it = set0.insert(p.first, 7);
  assert(*it == 7);
  assert(set0.count(7) > 0);

  set0.insert(set1.begin(), set1.end());
  assert(set0.count(13) > 0);

  // Test erase().
  assert(set0.erase(13) > 0);
  assert(set0.erase(1) == 0);

  set0.erase(set1.begin(), set1.end());
  assert(set0.size() == 2);
  
  it = set0.begin();
  set0.erase(it);
  it = set0.begin();
  set0.erase(it);
  assert(set0.empty());

  // Test swap().
  set0.swap(set1);
  assert(!set0.empty());
  assert(set1.empty());

  // Test clear().
  set0.clear();
  assert(set0.empty());

  // Test find() and count().
  assert(set3.find(42) != set3.end());
  assert(set3.find(43) == set3.end());
  assert(set3.count(505) == 1);
  assert(set3.count(504) == 0);
  for (unsigned int i = 0; i < set3.max_size(); ++i)
    if (set3.find(i) == set3.end())
      assert(set3.count(i) == 0);
    else
      assert(set3.count(i) > 0);
      
  // Test lower_bound(), upper_bound() and equal_range().
  Bitset::iterator lower = set3.lower_bound(400);
  Bitset::iterator upper = set3.upper_bound(69);
  assert(*lower == 505);
  assert(*upper == 51);
  assert(set3.equal_range(69) == std::make_pair(lower, upper));
  
  lower = set3.lower_bound(505);
  upper = set3.upper_bound(51);
  assert(*lower == 505);
  assert(*upper == 42);

  // Test operator == and operator !=.
  assert(set0 == set1);
  assert(set2 == set3);

  assert(set0 != set2);
  assert(set0 != set3);

  assert(set1 != set2);
  assert(set1 != set3);

  assert(set2 != set0);
  assert(set2 != set1);

  assert(set3 != set0);
  assert(set3 != set1);

  // Verify that >, >=, < and <= constitute a true ordering relation.
  if (set0 < set1)
    assert(set1 > set0);
  else
    assert(set0 >= set1);

  if (set2 > set3)
    assert(set3 < set2);
  else
    assert(set2 <= set3);

  // Test operator & and operator |.
  assert((set0 & set3) == set0);
  assert((set0 | set3) == set3);

  // Test operator [].
  for (unsigned int i = 0; i < set3.max_size(); ++i)
    if (set3[i])
      assert(set3.count(i) > 0);
    else
      assert(set3.count(i) == 0);

  // Test project() and unproject().
  Bitset b(46);
  b.insert(42);
  b.insert(44);
  
  Bitset projected = set3.project(b);
  assert(projected.size() == 1);
  assert(projected.max_size() == 2);
  assert(projected[0]);
  assert(!projected[1]);

  Bitset unprojected = projected.unproject(b);
  assert(unprojected.size() == 1);
  assert(unprojected.max_size() == b.max_size());
  for (unsigned int i = 0; i < unprojected.max_size(); ++i)
    if (i == 42)
      assert(unprojected[i]);
    else
      assert(!unprojected[i]);

  // Test to_unsigned() and cast().
  assert(set0.to_unsigned() == 0);
  assert(Bitset (64, data).to_unsigned() == data[0]);

  assert(set0.cast<int>() == 0);
  assert(Bitset (64, data).cast<int>() == static_cast<int> (data[0]));

  // Test print().
  std::ostringstream ostr1;
  ostr1 << set0;
  assert(ostr1.str() == "{ }");

  std::ostringstream ostr2;
  ostr2 << set3;
  assert(ostr2.str() == "{ 33 42 51 505 806 }");

  // Great! All tests have been passed.
  return 0;
}

