#ifndef VCSN_XML_CALLBACK_HH
# define VCSN_XML_CALLBACK_HH

# include <vaucanson/xml/dynamic.hh>
# include <iostream>

namespace vcsn
{
  namespace xml
  {
    template <template <typename I> class Callback,
	      typename User>
    int
    apply(std::istream&, User&);
  }
}

# include <vaucanson/xml/callback.hxx>

#endif // VCSN_XML_CALLBACK_HH
