// -*- C++ -*-

%define decl_automaton(Kind)

%include vaucanswig_exception.i
%include vaucanswig_describe.i

%import vaucanswig_core.i
%import vaucanswig_## Kind ##_context.i

%{
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
#include <vaucanson/automata/concrete/generalized.hh>
#include <vaucanson/misc/dot_dump.hh>
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

    Kind ##_serie_t serie_of(int) const;
    int add_serie_edge(int, int, const Kind ##_serie_t&);

    Kind ##_serie_t get_initial(int) const;
    Kind ##_serie_t get_final(int) const;
    
    virtual void set_initial(int);
    void set_initial(int, const Kind ##_serie_t&);

    virtual void set_final(int);
    void set_final(int, const Kind ##_serie_t&);

    const Kind ##_automata_set_t& set() const;
  };

  struct gen_## Kind ##_auto_t : vcsn::virtual_automaton
  {
    gen_## Kind ##_auto_t(const Kind ##_automata_set_t&);
    gen_## Kind ##_auto_t(const Kind ##_context&);
    gen_## Kind ##_auto_t(const gen_## Kind ##_auto_t&);

    %extend {
    gen_## Kind ##_auto_t(const Kind ##_auto_t& a)
      {
	return new gen_## Kind ##_auto_t(vcsn::generalized(a));
      }
    }

    Kind ##_exp_t serie_of(int) const;
    int add_serie_edge(int, int, const Kind ##_exp_t&);

    Kind ##_exp_t get_initial(int) const;
    Kind ##_exp_t get_final(int) const;
    
    virtual void set_initial(int);
    void set_initial(int, const Kind ##_exp_t&);

    virtual void set_final(int);
    void set_final(int, const Kind ##_exp_t&);

    const Kind ##_automata_set_t& set() const;
  };

}

%enddef

