
%define algo_common_decls(Kind)
%include vaucanswig_exception.i
%import vaucanswig_core.i
%import vaucanswig_## Kind ##_context.i
%import vaucanswig_## Kind ##_automaton.i

%{
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/automata/implementation/generalized.hh>
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

template<typename T>
static inline
  std::list<int> list_of_structure(const std::set<T>& set_)
  { return std::list<int>(set_.begin(), set_.end()); }
%}
%enddef

