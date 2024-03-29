// intrinsics.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_DESIGN_PATTERN_INTRINSICS_HH
# define VCSN_TESTS_DESIGN_PATTERN_INTRINSICS_HH

#include <vaucanson/design_pattern/design_pattern.hh>
#include <cassert>
#include <string>
#include "tests/check/tester.hh"


static std::string tag;

namespace vcsn_test {


  // empty singleton structure
  struct eS : vcsn::Structure<eS> { };

  // empty implementation type equipped with operator identification
  struct eT {
    eT() { tag += "eT"; }
    eT(const eT&) { tag += "eTc"; }
    template<typename T>
    eT(const T&) { tag += "eTc"; tag += typeid(T).name(); }
    eT& operator=(const eT& ) { tag += "eTa"; return *this; }
    template<typename T>
    eT& operator=(const T& ) { tag += "eTa"; tag += typeid(T).name(); return *this; }

    bool operator==(const eT& ) { tag += "eTe"; return true; }
    template<typename T>
    bool operator==(const T& ) { tag += "eTe"; tag += typeid(T).name(); return true; }
    bool operator<(const eT& ) { tag += "eTl"; return true; }
    template<typename T>
    bool operator<(const T& ) { tag += "eTl"; tag += typeid(T).name(); return true; }
 };

  // simple non-singleton structure with attribute
  struct S : vcsn::Structure<S> {
    int s_;
    S() : s_(0) {}
    S(const S& other) : vcsn::Structure<S>(other), s_(other.s_) {}
  };
  bool operator==(const S& s1, const S& s2)
  { return s1.s_ == s2.s_; }

  bool operator==(const eT&, const eS&)
  { return true; }

  // simple non-singleton structure without attribute

  struct Sna : vcsn::Structure<Sna> {
    Sna() {}
    Sna(const Sna& other) : vcsn::Structure<Sna>(other) {}
  };

  // simple implementation type with attribute
  struct T {
    int t_;
    T& operator=(int x) { t_ = x; return *this; }
  };

}

namespace vcsn {

  // specialization for simple singleton structure
  template<>
  struct dynamic_traits<vcsn_test::eS>
    : dynamic_traits<Structure<vcsn_test::eS> >
  { };
  template<typename T>
  struct MetaElement<vcsn_test::eS, T>
    : MetaElement<Structure<vcsn_test::eS>, T>
  {
    void foo() const
    { op_foo(this->structure(), this->value()); }
  protected:
    MetaElement() : MetaElement<Structure<vcsn_test::eS>, T>() {}
    MetaElement(const MetaElement& other) : MetaElement<Structure<vcsn_test::eS>, T>(other) {}
  };


  // specializations for non-singleton structures
  template<>
  struct dynamic_traits<vcsn_test::S>
    : dynamic_traits<Structure<vcsn_test::S> >
  {
    static const bool ret = true;
  };

  template<>
  struct dynamic_traits<vcsn_test::Sna>
    : dynamic_traits<Structure<vcsn_test::Sna> >
  {
    static const bool ret = false;
  };

  // additional operator provided by any structure on type T
  template <class S>
  void op_foo(const S& s, const vcsn_test::T& )
  {
    if (&s)
      tag += "set";
    tag += "foo";
  }

  template<typename T>
  struct MetaElement<vcsn_test::S, T>
    : MetaElement<Structure<vcsn_test::S>, T>
  {
    void foo() const
    { op_foo(this->structure(), this->value()); }

  protected:
    MetaElement() : MetaElement<Structure<vcsn_test::S>, T>() {}
    MetaElement(const MetaElement& other) : MetaElement<Structure<vcsn_test::S>, T>(other) {}
  };

  template<typename T>
  struct MetaElement<vcsn_test::Sna, T>
    : MetaElement<Structure<vcsn_test::Sna>, T>
  {

  protected:
    MetaElement() : MetaElement<Structure<vcsn_test::Sna>, T>() {}
    MetaElement(const MetaElement& other) : MetaElement<Structure<vcsn_test::Sna>, T>(other) {}
  };

  // Operators to build an eS structural element from Sna.
  vcsn_test::eS
  op_convert(const vcsn_test::eS&, const vcsn_test::Sna&)
  {
    return vcsn_test::eS ();
  }

}

// shortcut to types

typedef vcsn::Element<vcsn_test::S, vcsn_test::T> t;
typedef vcsn::Element<vcsn_test::eS, vcsn_test::eT> et;

#endif // ! VCSN_TESTS_DESIGN_PATTERN_INTRINSICS_HH
