#include "vauto.hh"
#include <vaucanson/misc/unique.hcc>
#include <fstream>
#include <stdexcept>
#include <cstdlib>

namespace vcsn
{
  void virtual_automaton::dot_run(const char *fname, const char *cmd, const char *name) const
  {
    {
      std::ofstream of(fname);
      if (!of)
	throw std::runtime_error("could not open file for writing");
      of << this->as_dot(name);
    }
    system((std::string(cmd) + ' ' + fname).c_str());
  }

  virtual_automaton::~virtual_automaton() {}
}
