// converter.hxx
//
// VCSN_HEADER

#ifndef AUTOMATA_MISC_CONVERTER_HXX
#define AUTOMATA_MISC_CONVERTER_HXX

# include <vaucanson/misc/converter.hh>
# include <functional>

namespace utility
{
  
  template<typename From, typename To>
  To converter<From, To>::operator()(const From& f) const
  { 
    return To(f); 
  }
  
} // utility


#endif
