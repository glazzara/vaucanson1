// context.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_DEMOS_VAUCANSWIG_META_CONTEXT_HH
# define VCSN_DEMOS_VAUCANSWIG_META_CONTEXT_HH

# include "vcontext.hh"
# include <string>
# include <sstream>

template<typename Auto>
struct vcsn_context : vcsn::virtual_context
{
    AUTOMATON_TYPES(Auto)
    AUTOMATON_FREEMONOID_TYPES(Auto)

    vcsn_context(const automata_set_t& set)
    : vcsn::virtual_context(), set_(& vcsn::misc::unique::get(set))
    {}
    vcsn_context(const vcsn_context& other)
      : vcsn::virtual_context(other), set_(other.set_)
    {}

    template<typename OtherAuto>
    vcsn_context(const vcsn_context<OtherAuto>& other)
      : vcsn::virtual_context(), set_(& other.automata_structure())
    {}

    const automata_set_t& automata_structure() const
    { return *set_; }

    const series_set_t& series() const
    { return set_->series(); }

    const monoid_t& monoid() const
    { return set_->series().monoid(); }

    const alphabet_t& alphabet() const
    { return set_->series().monoid().alphabet(); }

    const semiring_t& semiring() const
    { return set_->series().semiring(); }

    virtual std::list<char> alphabet_letters() const
    { return std::list<char>(alphabet().begin(), alphabet().end()); }

    virtual std::string describe_alphabet(bool cpp) const
    {
      std::ostringstream ret;
      ret << "Alphabet (" << alphabet() << ')';
      if (cpp)
	ret << " <" << typeid(alphabet_t).name() << '>';
      return ret.str();
    }

    virtual std::string describe_semiring(bool cpp) const
    {
      std::string ret = "Semiring";
      if (cpp)
	ret = ret + " <" + typeid(semiring_t).name() + '>';
      return ret;
    }

    virtual std::string describe_monoid(bool cpp) const
    {
      std::string ret = "Monoid (" + describe_alphabet(cpp) + ')';
      if (cpp)
	ret = ret + " <" + typeid(monoid_t).name() + '>';
      return ret;
    }

    virtual std::string describe_series(bool cpp) const
    {
      std::string ret = "Series (" + describe_semiring(cpp)
	+ ", " + describe_monoid(cpp) + ')';
      if (cpp)
	ret = ret + " <" + typeid(series_set_t).name() + '>';
      return ret;
    }

    virtual std::string describe_automata_structure(bool cpp) const
    {
      std::string ret = "AutomataSet (" + describe_series(cpp) + ')';
      if (cpp)
	ret = ret + " <" + typeid(automata_set_t).name() + '>';
      return ret;
    }

    virtual ~vcsn_context() {}

  protected:
    const automata_set_t* set_;
};

# define MAKE_AUTO_TYPES(FAMILY)					\
  namespace FAMILY ##_types						\
  {									\
    typedef vcsn::FAMILY::automaton_t automaton_t;			\
    AUTOMATON_TYPES_EXACT_(automaton_t, FAMILY ##_)			\
      AUTOMATON_FREEMONOID_TYPES_EXACT_(automaton_t, FAMILY ##_)	\
      }

# define MAKE_GEN_AUTO_TYPES(FAMILY)					\
  namespace FAMILY ##_types						\
  {									\
    typedef vcsn::generalized_traits<automaton_t>::automaton_t generalized_automaton_t;	\
    AUTOMATON_TYPES_EXACT_(generalized_automaton_t, gen_## FAMILY ##_)	\
      AUTOMATON_FREEMONOID_TYPES_EXACT_(generalized_automaton_t, gen_## FAMILY ##_) \
      typedef gen_## FAMILY ##_series_set_elt_t FAMILY ##_exp_t;	\
    typedef gen_## FAMILY ##_series_set_elt_value_t FAMILY ##_exp_value_t; \
  }


# define MAKE_CONTEXT_TYPE(FAMILY)				\
  namespace FAMILY ##_types					\
  {								\
    typedef vcsn_context<automaton_t> FAMILY ##_context;	\
  }

# define MAKE_CONTEXT_OPS(FAMILY)				\
  namespace FAMILY ##_types					\
  {								\
    FAMILY ##_alphabet_t letters(const char *s)			\
    {								\
      FAMILY ##_alphabet_t alpha;				\
      while (*s)						\
	alpha.insert(*s++);					\
      return alpha;						\
    }								\
								\
    FAMILY ##_context						\
      make_context(const FAMILY ##_alphabet_t& alpha)		\
    {								\
      FAMILY ##_semiring_t semiring;				\
      FAMILY ##_monoid_t monoid(alpha);				\
      FAMILY ##_series_set_t series(semiring, monoid);		\
      FAMILY ##_automata_set_t automata_structure(series);	\
      return FAMILY ##_context(automata_structure);		\
    }								\
  }

# define MAKE_SE_IO(FAMILY)						\
  namespace FAMILY ##_types						\
  {									\
    inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_monoid_t& m) \
    { return o << '<' << typeid(m).name() << "> FreeMonoid (" << m.alphabet() << ')'; }	\
									\
    inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_semiring_t& w) \
    { return o << '<' << typeid(w).name() << "> Semiring"; }		\
									\
    inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_series_set_t& s) \
    { return o << '<' << typeid(s).name() << "> Series (" << s.semiring() << ", " << s.monoid() << ')'; } \
									\
    inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_automata_set_t& a)	\
    { return o << '<' << typeid(a).name() << "> AutomataSet (" << a.series() << ')'; } \
									\
  }

#endif // ! VCSN_DEMOS_VAUCANSWIG_META_CONTEXT_HH