// -*- C++ -*-

%define decl_automaton(Kind)

  %include vaucanswig_exception.i
  %include vaucanswig_describe.i

  %import vaucanswig_core.i
  %import vaucanswig_## Kind ##_context.i

  %{
#include <vaucanson/boolean_automaton_structures.hh>
#include <vaucanson/z_automaton_structures.hh>
#include <vaucanson/z_max_plus_automaton_structures.hh>
#include <vaucanson/z_min_plus_automaton_structures.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <stdexcept>
#include <sstream>
#include <fstream>
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

#include "automaton.hh"
    MAKE_VAUTO_TYPES(Kind)

    using namespace Kind ##_types;
  %}

namespace Kind ##_types
{
  struct Kind ##_auto_t : vcsn::virtual_automaton
  {
      Kind ##_auto_t(const Kind ##_automata_set_t&);
      Kind ##_auto_t(const Kind ##_context&);
      Kind ##_auto_t(const Kind ##_auto_t&);

      Kind ##_series_set_elt_t series_of(int) const;
      int add_series_transition(int, int, const Kind ##_series_set_elt_t&);

      Kind ##_series_set_elt_t get_initial(int) const;
      Kind ##_series_set_elt_t get_final(int) const;

      void set_initial(int, const Kind ##_series_set_elt_t&);

      void set_final(int, const Kind ##_series_set_elt_t&);

      const Kind ##_automata_set_t& structure() const;

      virtual const vcsn::virtual_context &context() const;

      virtual bool has_state(int) const;
      virtual bool has_transition(int) const;
      virtual void del_state(int);
      virtual void del_transition(int);

      virtual std::list<int> states() const;
      virtual std::list<int> transitions() const;

      virtual int add_state();
      void add_states(int);
      virtual int add_spontaneous(int, int);
      virtual int add_letter_transition(int, int, char);
      virtual int add_lw_transition(int, int, int, const std::string&);
      virtual int add_rw_transition(int, int, const std::string&, int);
      virtual int add_lrw_transition(int, int, int, const std::string&, int);

      virtual std::string label_of(int) const;

      virtual int src_of(int) const;
      virtual int dst_of(int) const;

      virtual void clear_initial();
      virtual std::list<int> initial() const;
      virtual bool is_initial(int) const;
      virtual void unset_initial(int);
      virtual void set_initial(int);
      virtual void set_initial(int, char);
      virtual void set_initial_lw(int, int, char);
      virtual void set_initial_lw(int, int);
      virtual void set_initial_rw(int, char, int);
      virtual void set_initial_rw(int, int);
      virtual void set_initial_lrw(int, int, char, int);
      virtual void set_initial_lrw(int, int, int);
      virtual std::string initial_label(int);

      virtual void clear_final();
      virtual std::list<int> final() const;
      virtual bool is_final(int) const;
      virtual void unset_final(int);
      virtual void set_final(int);
      virtual void set_final(int, char);
      virtual void set_final_lw(int, int, char);
      virtual void set_final_lw(int, int);
      virtual void set_final_rw(int, char, int);
      virtual void set_final_rw(int, int);
      virtual void set_final_lrw(int, int, char, int);
      virtual void set_final_lrw(int, int, int);
      virtual std::string final_label(int);

      virtual std::list<int> delta(int, bool states_only = true) const;
      virtual std::list<int> letter_delta(int, char, bool states_only = true) const;
      virtual std::list<int> spontaneous_delta(int, bool states_only = true) const;

      virtual std::list<int> rdelta(int, bool states_only = true) const;
      virtual std::list<int> letter_rdelta(int, char, bool states_only = true) const;
      virtual std::list<int> spontaneous_rdelta(int, bool states_only = true) const;

      virtual std::string describe(bool cpptype = false) const;

      virtual void load(std::istream&, const std::string&);
      virtual void save(std::ostream&, const std::string&) const;

      %extend {
	void load(const char* fname)
	{
	  std::ifstream in(fname);
	  if (!in)
	    throw std::runtime_error(std::string("cannot open file: ") + fname);
	  self->load(in, "XML");
	}
	void save(const char* fname) const
	{
	  std::ofstream out(fname);
	  if (!out)
	    throw std::runtime_error(std::string("cannot open file: ") + fname);
	  self->save(out, "XML");
	}
      }

      virtual ~Kind ##_auto_t();
  };

  struct gen_## Kind ##_auto_t : vcsn::virtual_automaton
  {
      gen_## Kind ##_auto_t(const Kind ##_automata_set_t&);
      gen_## Kind ##_auto_t(const gen_## Kind ##_auto_t&);

      %extend {
	gen_## Kind ##_auto_t(const Kind ##_context& c)
	{
	  return new gen_## Kind ##_auto_t(vcsn_context<generalized_automaton_t>(c));
	}
	gen_## Kind ##_auto_t(const Kind ##_auto_t& a)
	{
	  return new gen_## Kind ##_auto_t(vcsn::generalized(a.the_automaton()));
	}
      }

      Kind ##_exp_t series_of(int) const;
      int add_series_transition(int, int, const Kind ##_exp_t&);

      Kind ##_exp_t get_initial(int) const;
      Kind ##_exp_t get_final(int) const;

      void set_initial(int, const Kind ##_exp_t&);

      void set_final(int, const Kind ##_exp_t&);

      const Kind ##_automata_set_t& structure() const;


      virtual const vcsn::virtual_context &context() const;

      virtual bool has_state(int) const;
      virtual bool has_transition(int) const;
      virtual void del_state(int);
      virtual void del_transition(int);

      virtual std::list<int> states() const;
      virtual std::list<int> transitions() const;

      virtual int add_state();
      virtual int add_spontaneous(int, int);
      virtual int add_letter_transition(int, int, char);
      virtual int add_lw_transition(int, int, int, const std::string&);
      virtual int add_rw_transition(int, int, const std::string&, int);
      virtual int add_lrw_transition(int, int, int, const std::string&, int);

      virtual std::string label_of(int) const;

      virtual int src_of(int) const;
      virtual int dst_of(int) const;

      virtual void clear_initial();
      virtual std::list<int> initial() const;
      virtual bool is_initial(int) const;
      virtual void unset_initial(int);
      virtual void set_initial(int);
      virtual void set_initial(int, char);
      virtual void set_initial_lw(int, int, char);
      virtual void set_initial_lw(int, int);
      virtual void set_initial_rw(int, char, int);
      virtual void set_initial_rw(int, int);
      virtual void set_initial_lrw(int, int, char, int);
      virtual void set_initial_lrw(int, int, int);
      virtual std::string initial_label(int);

      virtual void clear_final();
      virtual std::list<int> final() const;
      virtual bool is_final(int) const;
      virtual void unset_final(int);
      virtual void set_final(int);
      virtual void set_final(int, char);
      virtual void set_final_lw(int, int, char);
      virtual void set_final_lw(int, int);
      virtual void set_final_rw(int, char, int);
      virtual void set_final_rw(int, int);
      virtual void set_final_lrw(int, int, char, int);
      virtual void set_final_lrw(int, int, int);
      virtual std::string final_label(int);

      virtual std::list<int> delta(int, bool states_only = true) const;
      virtual std::list<int> letter_delta(int, char, bool states_only = true) const;
      virtual std::list<int> spontaneous_delta(int, bool states_only = true) const;

      virtual std::list<int> rdelta(int, bool states_only = true) const;
      virtual std::list<int> letter_rdelta(int, char, bool states_only = true) const;
      virtual std::list<int> spontaneous_rdelta(int, bool states_only = true) const;

      virtual std::string describe(bool cpptype = false) const;

      virtual void load(std::istream&, const std::string&);
      virtual void save(std::ostream&, const std::string&) const;

      %extend {
	bool load(const std::string& fname)
	{
	  std::ifstream in(fname.c_str());
	  if (!in)
	    throw std::runtime_error("cannot open file: " + fname);
	  self->load(in, "XML");
	}
	bool save(const std::string& fname) const
	{
	  std::ofstream out(fname.c_str());
	  if (!out)
	    throw std::runtime_error("cannot open file: " + fname);
	  self->save(out, "XML");
	}
      }
  };

}

%enddef

