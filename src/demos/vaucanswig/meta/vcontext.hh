#ifndef VCONTEXT_HH
# define VCONTEXT_HH

#include <list>
#include <string>

namespace vcsn
{
  struct virtual_context 
  {
    virtual std::list<char> alphabet_letters() const = 0;
    virtual std::string describe_alphabet(bool with_cpp = false) const = 0;
    virtual std::string describe_weights(bool with_cpp = false) const = 0;
    virtual std::string describe_monoid(bool with_cpp = false) const = 0;
    virtual std::string describe_series(bool with_cpp = false) const = 0;
    virtual std::string describe_automata_set(bool with_cpp = false) const = 0;
    virtual ~virtual_context();
  };
}

#endif
