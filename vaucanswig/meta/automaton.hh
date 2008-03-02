// automaton.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DEMOS_VAUCANSWIG_META_AUTOMATON_HH
# define VCSN_DEMOS_VAUCANSWIG_META_AUTOMATON_HH

#include "context.hh"
#include "vauto.hh"
#include <vaucanson/xml/XML.hh>
#include <vaucanson/tools/io.hh>
#include <vaucanson/tools/usual_io.hh>
#include <vaucanson/tools/simple_format.hh>
#include <vaucanson/tools/dot_format.hh>

/*** Structural element extraction ***/
#define SERIES_OF(Self) (Self)->structure().series()
#define MONOID_OF(Self) (Self)->structure().series().monoid()
#define WEIGHTS_OF(Self) (Self)->structure().series().semiring()
#define ALPHABET_OF(Self) (Self)->structure().series().monoid().alphabet()

/*** Convenient macros ***/
#define CHECK_STATE(Self,State)			\
  if (!(Self)->auto_->has_state(State))		\
    throw std::runtime_error("no such state")

#define CHECK_TRANSITION(Self, Transition)		\
  if (!(Self)->auto_->has_transition(htransition_t(Transition)))	\
    throw std::runtime_error("no such transition")

#define CHECK_LETTER(Self, L)					\
  if (!ALPHABET_OF(Self).contains(L))				\
    throw std::runtime_error("letter not present in alphabet")

#define WORD_OF_LETTER(Self, L) monoid_elt_t(MONOID_OF(Self), L)

#define WEIGHT(Self, W) semiring_elt_t(WEIGHTS_OF(Self), W)


template<typename Auto, typename Converter>
struct vcsn_automaton : vcsn::virtual_automaton
{
    AUTOMATON_TYPES(Auto)
    AUTOMATON_FREEMONOID_TYPES(Auto)



    vcsn_automaton(const Auto& other)
    : ctx_(new vcsn_context<Auto>(other.structure())), auto_(new Auto(other)), conv_()
    {}
    vcsn_automaton(const automata_set_t& other)
      : ctx_(new vcsn_context<Auto>(other)), auto_(new Auto(other)), conv_()
    {}
    vcsn_automaton(const vcsn_automaton& other)
      : ctx_(new vcsn_context<Auto>(*other.ctx_)), auto_(new Auto(*other.auto_)), conv_()
    {}

    vcsn_automaton(const vcsn_context<Auto>& ctx)
      : ctx_(new vcsn_context<Auto>(ctx)), auto_(new Auto(ctx_->automata_structure())), conv_()
    {}

    vcsn_automaton()
      : ctx_(0), auto_(0), conv_()
    {}

    vcsn_automaton& operator=(const vcsn_automaton& other)
    {
      delete auto_;
      delete ctx_;
      ctx_ = new vcsn_context<Auto>(*other.ctx_);
      auto_ = new Auto(*other.auto_);
    }

    vcsn_automaton& operator=(const Auto& other)
    {
      delete auto_;
      delete ctx_;
      ctx_ = new vcsn_context<Auto>(other.structure());
      auto_ = new Auto(other);
    }

    const automaton_t& the_automaton() const { return (*auto_); }

    const automaton_t& operator*() const { return (*auto_); }
    automaton_t& operator*() { return (*auto_); }

    const automata_set_t &structure() const { return (*auto_).structure(); }

    series_set_elt_t series_of(int e) const
    {
      CHECK_TRANSITION(this, e);
      return (*auto_).series_of(htransition_t(e));
    }

    int add_series_transition(int from, int to, const series_set_elt_t& s)
    {
      CHECK_STATE(this, from); CHECK_STATE(this, to);
      return (*auto_).add_series_transition(from, to, s);
    }

    series_set_elt_t get_initial(int state) const
    {
      CHECK_STATE(this, state);
      return (*auto_).get_initial(state);
    }

    series_set_elt_t get_final(int state) const
    {
      CHECK_STATE(this, state);
      return (*auto_).get_final(state);
    }

    void set_initial(int state, const series_set_elt_t& s)
    {
      CHECK_STATE(this, state);
      return (*auto_).set_initial(state, s);
    }

    void set_final(int state, const series_set_elt_t& s)
    {
      CHECK_STATE(this, state);
      return (*auto_).set_final(state, s);
    }


    virtual const vcsn_context<Auto> &context() const
    { return *ctx_; }

    virtual bool has_state(int s) const { return (*auto_).has_state(s); }
    virtual bool has_transition(int e) const { return (*auto_).has_transition(htransition_t(e)); }

    virtual void del_state(int s)
    {
      CHECK_STATE(this, s);
      return (*auto_).del_state(s);
    }

    virtual void del_transition(int e)
    {
      CHECK_TRANSITION(this, e);
      return (*auto_).del_transition(htransition_t(e));
    }

    virtual std::list<int> states() const
    {
      return std::list<int>((*auto_).states().begin(), (*auto_).states().end());
    }

    virtual std::list<int> transitions() const
    {
      return std::list<int>((*auto_).transitions().begin(),
			    (*auto_).transitions().end());
    }

    virtual int add_state() { return (*auto_).add_state(); }

    // Creation of spontaneous transition between two states
    virtual int add_spontaneous(int from, int to)
    {
      CHECK_STATE(this, from); CHECK_STATE(this, to);
      return (*auto_).add_spontaneous(from, to);
    }

    // Creation of transition with single letter label
    virtual int add_letter_transition(int from, int to, char l)
    {
      CHECK_STATE(this, from); CHECK_STATE(this, to);
      CHECK_LETTER(this, l);
      return (*auto_).add_letter_transition(from, to, l);
    }

    // Creation of transition with weight on the left
    virtual int add_lw_transition(int from, int to, int w, const std::string& l)
    {
      CHECK_STATE(this, from); CHECK_STATE(this, to);
      for (std::string::const_iterator c = l.begin(); c != l.end(); ++c)
	CHECK_LETTER(this, *c);

      series_set_elt_t s(SERIES_OF(this));
      s = WORD_OF_LETTER(this, l);
      s = WEIGHT(this, w) * s;
      return (*auto_).add_series_transition(from, to, s);
    }

    // Creation of transition with weight on the right
    virtual int add_rw_transition(int from, int to, const std::string& l, int w)
    {
      CHECK_STATE(this, from); CHECK_STATE(this, to);
      for (std::string::const_iterator c = l.begin(); c != l.end(); ++c)
	CHECK_LETTER(this, *c);

      series_set_elt_t s(SERIES_OF(this));
      s = WORD_OF_LETTER(this, l);
      s = s * WEIGHT(this, w);
      return (*auto_).add_series_transition(from, to, s);
    }

    // Creation of transition with weight on left and right
    virtual int add_lrw_transition(int from, int to, int lw, const std::string& l, int rw)
    {
      CHECK_STATE(this, from); CHECK_STATE(this, to);
      for (std::string::const_iterator c = l.begin(); c != l.end(); ++c)
	CHECK_LETTER(this, *c);

      series_set_elt_t s(SERIES_OF(this));
      s = WORD_OF_LETTER(this, l);
      s = WEIGHT(this, lw) * s * WEIGHT(this, rw);
      return (*auto_).add_series_transition(from, to, s);
    }

    // Transition label retrieval
    virtual std::string label_of(int transition) const
    {
      CHECK_TRANSITION(this, transition);
      std::ostringstream s;
      s << (*auto_).series_of(htransition_t(transition));
      return s.str();
    }

    virtual int src_of(int transition) const
    {
      CHECK_TRANSITION(this, transition);
      return (*auto_).src_of(htransition_t(transition));
    }

    virtual int dst_of(int transition) const
    {
      CHECK_TRANSITION(this, transition);
      return (*auto_).dst_of(htransition_t(transition));
    }

#define DefInitialFinalMembers(InitialFinal)				\
    /* Clear the initial or final set */				\
    virtual void clear_## InitialFinal ()				\
    {									\
      return (*auto_).clear_## InitialFinal ();				\
    }									\
									\
	/* Access to the initial and final sets */			\
	virtual std::list<int> InitialFinal () const			\
    {									\
      std::list<int> ret((*auto_). InitialFinal ().begin(),		\
			 (*auto_). InitialFinal ().end());		\
      return ret;							\
    }									\
									\
	/* Test whether a given state is initial or final */		\
	virtual bool is_## InitialFinal (int state) const		\
    {									\
      CHECK_STATE(this, state);						\
      return (*auto_).is_## InitialFinal(state);			\
    }									\
									\
	/* Unset a state as initial or final */				\
	virtual void unset_## InitialFinal (int state)			\
    {									\
      CHECK_STATE(this, state);						\
      return (*auto_).unset_## InitialFinal(state);			\
    }									\
									\
	/* Set a state initial or final without weight */		\
	virtual void set_## InitialFinal (int state)			\
    {									\
      CHECK_STATE(this, state);						\
      return (*auto_).set_## InitialFinal(state);			\
    }									\
									\
	/*  Set a state initial or final with an associated letter */	\
	virtual void set_## InitialFinal (int state, char letter)	\
    {									\
      CHECK_STATE(this, state);						\
      CHECK_LETTER(this, letter);					\
      series_set_elt_t s (SERIES_OF(this), WORD_OF_LETTER(this, letter)); \
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
									\
	/* Set a state initial or final with an associated weight and letter */	\
	virtual void set_## InitialFinal ##_lw(int state, int weight, char letter) \
    {									\
      CHECK_STATE(this, state);						\
      CHECK_LETTER(this, letter);					\
									\
      series_set_elt_t s(SERIES_OF(this));				\
      s = WORD_OF_LETTER(this, letter);					\
      s = WEIGHT(this, weight) * s;					\
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
	virtual void set_## InitialFinal ##_rw(int state, char letter, int weight) \
    {									\
      CHECK_STATE(this, state);						\
      CHECK_LETTER(this, letter);					\
									\
      series_set_elt_t s(SERIES_OF(this));				\
      s = WORD_OF_LETTER(this, letter);					\
      s = s * WEIGHT(this, weight);					\
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
	virtual void set_## InitialFinal ##_lrw(int state,		\
						int lweight, char letter, int rweight) \
    {									\
      CHECK_STATE(this, state);						\
      CHECK_LETTER(this, letter);					\
									\
      series_set_elt_t s(SERIES_OF(this));				\
      s = WORD_OF_LETTER(this, letter);					\
      s = WEIGHT(this, lweight) * s * WEIGHT(this, rweight);		\
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
									\
	/* Set a state initial or final with an associated weight and identity */ \
	virtual void set_## InitialFinal ##_lw(int state, int weight)	\
    {									\
      CHECK_STATE(this, state);						\
									\
      series_set_elt_t s(SERIES_OF(this));				\
      s = SERIES_OF(this).identity(SELECT(series_set_elt_value_t));	\
      s = WEIGHT(this, weight) * s;					\
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
	virtual void set_## InitialFinal ##_rw(int state, int weight)	\
    {									\
      CHECK_STATE(this, state);						\
									\
      series_set_elt_t s(SERIES_OF(this));				\
      s = SERIES_OF(this).identity(SELECT(series_set_elt_value_t));	\
      s = s * WEIGHT(this, weight);					\
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
	virtual void set_## InitialFinal ##_lrw(int state, int lweight, int rweight) \
    {									\
      CHECK_STATE(this, state);						\
									\
      series_set_elt_t s(SERIES_OF(this));				\
      s = SERIES_OF(this).identity(SELECT(series_set_elt_value_t));	\
      s = WEIGHT(this, lweight) * s * WEIGHT(this, rweight);		\
      return (*auto_).set_## InitialFinal (state, s);			\
    }									\
									\
	virtual std::string InitialFinal ##_label(int state)		\
    {									\
      CHECK_STATE(this, state);						\
									\
      std::ostringstream os;						\
      os << (*auto_).get_## InitialFinal(state);			\
      return os.str();							\
    }

    DefInitialFinalMembers(initial)
    DefInitialFinalMembers(final)

#undef DefInitialFinalMembers

#define DefDeltaMembers(Direction)					\
									\
    virtual std::list<int> Direction(int from, bool states_only = true) const \
    {									\
      CHECK_STATE(this, from);						\
									\
      std::list<int> ret;						\
      std::insert_iterator<std::list<int> > i(ret, ret.begin());	\
									\
      if (states_only)							\
	(*auto_).Direction(i, from, vcsn::delta_kind::states());	\
      else								\
	(*auto_).Direction(i, from, vcsn::delta_kind::transitions());	\
									\
      return ret;							\
    }									\
									\
	std::list<int> letter_## Direction(int from, char l,		\
					   bool states_only = true) const \
    {									\
      CHECK_STATE(this, from);						\
      CHECK_LETTER(this, l);						\
									\
      std::list<int> ret;						\
      std::insert_iterator<std::list<int> > i(ret, ret.begin());	\
									\
      if (states_only)							\
	(*auto_).letter_## Direction(i, from, l, vcsn::delta_kind::states()); \
      else								\
	(*auto_).letter_## Direction(i, from, l, vcsn::delta_kind::transitions()); \
									\
      return ret;							\
    }									\
									\
	std::list<int> spontaneous_## Direction(int from,		\
						bool states_only = true) const \
    {									\
      CHECK_STATE(this, from);						\
									\
      std::list<int> ret;						\
      std::insert_iterator<std::list<int> > i(ret, ret.begin());	\
									\
      if (states_only)							\
	(*auto_).spontaneous_## Direction(i, from, vcsn::delta_kind::states());	\
      else								\
	(*auto_).spontaneous_## Direction(i, from, vcsn::delta_kind::transitions()); \
									\
      return ret;							\
    }

    DefDeltaMembers(delta)
    DefDeltaMembers(rdelta)

    virtual std::string describe(bool cpptype = false) const
    {
      std::ostringstream s;
      if (cpptype)
	s << typeid(Auto).name() << '@' << auto_ << " = ";
      s << (*auto_);
      return s.str();
    }

    virtual void load(std::istream& in, const std::string& format)
    {
      if (format.substr(0, 6) == "simple")
	in >> vcsn::automaton_loader(*auto_, conv_, vcsn::tools::simple());
      else if (format.substr(0, 3) == "XML")
	in >> vcsn::automaton_loader(*auto_, conv_, vcsn::xml::XML());
      else
	throw std::runtime_error("format not supported: " + format);
    }

    virtual void save(std::ostream& out, const std::string& format) const
    {
      if (format.substr(0, 3) == "dot")
      {
	std::string name = format;
	name.erase(name.begin(), name.begin() + 3);
	if (name.size() < 2)
	  name = ":automaton";
	name.erase(name.begin(), name.begin() + 1);
	out << vcsn::automaton_saver(*auto_, vcsn::tools::string_out(), vcsn::tools::dot(name));
      }
      else if (format.substr(0, 6) == "simple")
	out << vcsn::automaton_saver(*auto_, conv_, vcsn::tools::simple());
      else if (format.substr(0, 3) == "XML")
	out << vcsn::automaton_saver(*auto_, conv_, vcsn::xml::XML());
      else
	throw std::runtime_error("format not supported: " + format);
    }

    virtual ~vcsn_automaton() { delete auto_; delete ctx_; }

  protected:
    vcsn_context<Auto>* ctx_;
    Auto *auto_;
    Converter conv_;
};

#define MAKE_VAUTO_TYPES(FAMILY)					\
  namespace FAMILY ##_types						\
  {									\
    typedef vcsn_automaton<automaton_t, vcsn::tools::usual_converter_poly<FAMILY ##_exp_t> > FAMILY ##_auto_t; \
    typedef vcsn_automaton<generalized_automaton_t, vcsn::tools::usual_converter_exp> gen_## FAMILY ##_auto_t; \
  }


#endif // ! VCSN_DEMOS_VAUCANSWIG_META_AUTOMATON_HH
