// -*- C++ -*-

%define monoid_ops(MonoidElt)
  %extend {
  MonoidElt& operator*=(const MonoidElt& rhs)
    { return (*self) *= rhs; }

  MonoidElt operator*(const MonoidElt& rhs) const
    { return (*self) * rhs; }

  bool operator==(const MonoidElt& rhs) const
    { return (*self) == rhs; }

  bool operator!=(const MonoidElt& rhs) const
    { return (*self) != rhs; }
  }
%enddef

%define semiring_ops(SemiringElt)
     monoid_ops(SemiringElt)

     %extend {
  SemiringElt& operator+=(const SemiringElt& rhs)
    { return (*self) += rhs; }
  SemiringElt operator+(const SemiringElt& rhs) const
    { return (*self) + rhs; }
}
%enddef

%define series_ops(SeriesElt, SemiringElt, MonoidElt)
     semiring_ops(SeriesElt)

     %extend {
  SeriesElt& operator+=(const SemiringElt& rhs)
    { return (*self) += rhs; }

  SeriesElt operator+(const SemiringElt& rhs) const
    { return (*self) + rhs; }

  SeriesElt ladd(const SemiringElt& lhs) const
    { return lhs + (*self); }

  SeriesElt& operator*=(const SemiringElt& rhs)
    { return (*self) *= rhs; }

  SeriesElt operator*(const SemiringElt& rhs) const
    { return (*self) * rhs; }

  SeriesElt lmul(const SemiringElt& lhs) const
    { return lhs * (*self); }

  SeriesElt& operator+=(const MonoidElt& rhs)
    { return (*self) += rhs; }

  SeriesElt operator+(const MonoidElt& rhs) const
    { return (*self) + rhs; }

  SeriesElt ladd(const MonoidElt& lhs) const
    { return lhs + (*self); }

}
%enddef

%define decl_context(Kind)

%include vaucanswig_exception.i
%include vaucanswig_describe.i
%import vaucanswig_core.i

%{
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/z_automaton.hh>
#include <vaucanson/z_max_plus_automaton.hh>
#include <vaucanson/z_min_plus_automaton.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/automata/implementation/generalized.hh>
#include <vaucanson/algorithms/finite_support_conversion.hh>
#include <vaucanson/algorithms/aci_canonical.hh>
#include <stdexcept>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <list>
#include <string>
#include "context.hh"

  
MAKE_AUTO_TYPES(Kind)
MAKE_GEN_AUTO_TYPES(Kind)
MAKE_CONTEXT_TYPE(Kind)
MAKE_CONTEXT_OPS(Kind)
MAKE_SE_IO(Kind)
using namespace Kind ##_types;
%}

namespace Kind ##_types
{
  /*** Alphabets ***/
  struct Kind ##_alphabet_t {
    %extend {
      Kind ##_alphabet_t(const char *s)
	{
	  return new Kind ##_alphabet_t(Kind ##_types::letters(s));
	}
    }
    EXTEND_DESCRIBE(Kind ##_alphabet_t)
  };

  /*** Monoids ***/

  struct Kind ##_monoid_t;

  struct Kind ##_monoid_elt_t {
    Kind ##_monoid_elt_t(const Kind ##_monoid_elt_t&);
    Kind ##_monoid_elt_t(const Kind ##_monoid_t&);
    Kind ##_monoid_elt_t(const Kind ##_monoid_t&, const std::string&);
    Kind ##_monoid_elt_t(const Kind ##_monoid_t&, char);
    EXTEND_DESCRIBE(Kind ##_monoid_elt_t)
    const Kind ##_monoid_t& structure() const;
    monoid_ops(Kind ##_monoid_elt_t)
  };

  struct Kind ##_monoid_t
  {
    Kind ##_monoid_t(const Kind ##_alphabet_t&);
    const Kind ##_alphabet_t& alphabet () const;
    EXTEND_DESCRIBE(Kind ##_monoid_t)
    %extend {
      Kind ##_monoid_elt_t make(const std::string& s)
	{ return Kind ##_monoid_elt_t(*self, s); }
      Kind ##_monoid_elt_t identity()
	{ return self->identity(SELECT(Kind ## _monoid_elt_value_t)); }
    }
  };

  /*** Semirings ***/

  struct Kind ##_semiring_t;

  struct Kind ##_semiring_elt_t
  {
    Kind ##_semiring_elt_t(const Kind ##_semiring_elt_t&);
    Kind ##_semiring_elt_t(const Kind ##_semiring_t&);
    Kind ##_semiring_elt_t(const Kind ##_semiring_t&, int);
    const Kind ##_semiring_t& structure() const;
    EXTEND_DESCRIBE(Kind ##_semiring_elt_t)
    semiring_ops(Kind ##_semiring_elt_t)
  };

  struct Kind ##_semiring_t
  {
    Kind ##_semiring_t();
    EXTEND_DESCRIBE(Kind ##_semiring_t)
    %extend {
      Kind ##_semiring_elt_t make(int i)
	{ return Kind ##_semiring_elt_t(*self, i); }
      Kind ##_semiring_elt_t identity()
	{ return self->identity(SELECT(Kind ## _semiring_elt_value_t)); }
      Kind ##_semiring_elt_t zero()
	{ return self->zero(SELECT(Kind ## _semiring_elt_value_t)); }
    }
  };

  /*** Series ***/

  struct Kind ##_series_set_t;

  struct Kind ##_series_set_elt_t
  {
    Kind ##_series_set_elt_t(const Kind ##_series_set_elt_t&);
    Kind ##_series_set_elt_t(const Kind ##_series_set_t&);
    Kind ##_series_set_elt_t(const Kind ##_series_set_t&, const Kind ##_semiring_elt_t&);
    Kind ##_series_set_elt_t(const Kind ##_series_set_t&, const Kind ##_monoid_elt_t&);
    const Kind ##_series_set_t& structure() const;
    EXTEND_DESCRIBE(Kind ##_series_set_elt_t)
    series_ops(Kind ##_series_set_elt_t, Kind ##_semiring_elt_t, Kind ##_monoid_elt_t)
  };

  struct Kind ##_exp_t
  {
    Kind ##_exp_t(const Kind ##_exp_t&);
    Kind ##_exp_t(const Kind ##_series_set_t&);
    Kind ##_exp_t(const Kind ##_series_set_t&, const Kind ##_series_set_elt_t&);
    Kind ##_exp_t(const Kind ##_series_set_t&, const Kind ##_semiring_elt_t&);
    Kind ##_exp_t(const Kind ##_series_set_t&, const Kind ##_monoid_elt_t&);
    %extend {
    Kind ##_exp_t star() const
      { return vcsn::star(*self); }
    }
    const Kind ##_series_set_t& structure() const;
    EXTEND_DESCRIBE(Kind ##_exp_t)
    series_ops(Kind ##_exp_t, Kind ##_semiring_elt_t, Kind ##_monoid_elt_t)
  };

  struct Kind ##_series_set_t {
    Kind ##_series_set_t(const Kind ##_semiring_t&, const Kind ##_monoid_t&);
    const Kind ##_monoid_t& monoid() const;
    const Kind ##_semiring_t& semiring() const;
    EXTEND_DESCRIBE(Kind ##_series_set_t)
    %extend {
    Kind ##_series_set_elt_t make(int i) const
    { return Kind ##_series_set_elt_t(*self, Kind ##_semiring_elt_t(self->semiring(), i)); }
    Kind ##_series_set_elt_t make(const std::string& l) const
    { return Kind ##_series_set_elt_t(*self, Kind ##_monoid_elt_t(self->monoid(), l)); }

    Kind ##_series_set_elt_t identity()
    { return self->identity(SELECT(Kind ## _series_set_elt_value_t)); }
    Kind ##_series_set_elt_t zero()
    { return self->zero(SELECT(Kind ## _series_set_elt_value_t)); }
    Kind ##_exp_t exp_identity()
    { return self->identity(SELECT(Kind ## _exp_value_t)); }
    Kind ##_exp_t exp_zero()
    { return self->zero(SELECT(Kind ## _exp_value_t)); }
    }
  };

  /*** Automata set ***/

  struct Kind ##_automata_set_t {
    Kind ##_automata_set_t(const Kind ##_series_set_t&);
    const Kind ##_series_set_t& series() const;
    EXTEND_DESCRIBE(Kind ##_automata_set_t)
  };

  struct Kind ##_context : vcsn::virtual_context
  {
    Kind ##_context(const Kind ##_automata_set_t& set);
    Kind ##_context(const Kind ##_context& other);

    const Kind ##_automata_set_t& automata_structure() const;
    const Kind ##_series_set_t& series() const;
    const Kind ##_monoid_t& monoid() const;
    const Kind ##_alphabet_t& alphabet() const;
    const Kind ##_semiring_t& semiring() const;

    virtual std::list<char> alphabet_letters() const;
    virtual std::string describe_alphabet(bool with_cpp = false) const;
    virtual std::string describe_semiring(bool with_cpp = false) const;
    virtual std::string describe_monoid(bool with_cpp = false) const;
    virtual std::string describe_series(bool with_cpp = false) const;
    virtual std::string describe_automata_structure(bool with_cpp = false) const;
    virtual ~Kind ##_context();


    %extend {
      Kind ##_semiring_elt_t semiring_elt(int i) const
	{ return Kind ##_semiring_elt_t(self->semiring(), i); }
      Kind ##_monoid_elt_t word(const std::string& l) const
	{
	  for (unsigned i = 0; i < l.size(); ++i)
	    if (!self->alphabet().contains(l[i]))
	      throw std::runtime_error("letter not in alphabet");
	  return Kind ##_monoid_elt_t(self->monoid(), l);
	}
      Kind ##_series_set_elt_t series(int i) const
	{ return Kind ##_series_set_elt_t(self->series(), Kind ##_semiring_elt_t(self->semiring(), i)); }
      Kind ##_series_set_elt_t series(const std::string& l) const
	{
	  for (unsigned i = 0; i < l.size(); ++i)
	    if (!self->alphabet().contains(l[i]))
	      throw std::runtime_error("letter not in alphabet");
	  return Kind ##_series_set_elt_t(self->series(), Kind ##_monoid_elt_t(self->monoid(), l));
	}
      Kind ##_series_set_elt_t series(const Kind ##_exp_t& e) const
	{
	  Kind ##_series_set_elt_t ret(self->series());
	  vcsn::finite_support_convert(ret, e);
	  return ret;
	}

      Kind ##_exp_t exp(const Kind ##_series_set_elt_t& s) const
	{
	  Kind ##_exp_t ret(self->series());
	  vcsn::finite_support_convert(ret, s);
	  return vcsn::canonical(ret);
	}

      Kind ##_exp_t exp(const std::string& l) const
	{
	  Kind ##_exp_t ret(self->series());
	  std::pair<bool, std::string> res = vcsn::algebra::parse(l, ret);
	  if (res.first)
	    throw std::runtime_error("parse error: " + res.second);
	  return ret;
	}
    }
  };

  Kind ##_context make_context(const Kind ##_alphabet_t&);
}

%enddef
