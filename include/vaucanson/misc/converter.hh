// converter.hh
//
// VCSN_HEADER

#ifndef AUTOMATA_MISC_CONVERTER_HH
#define AUTOMATA_MISC_CONVERTER_HH

# include <functional>

namespace utility
{

  template<typename From, typename To>
  struct converter : std::unary_function<From, To>
  {
    To operator()(const From& f) const;
  };

} // utility

# include <vaucanson/misc/converter.hxx>

#endif
