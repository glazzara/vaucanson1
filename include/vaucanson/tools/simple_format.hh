#ifndef SIMPLE_FORMAT_HH
# define SIMPLE_FORMAT_HH

# include <iostream>

namespace vcsn 
{
  namespace io
  {
    struct simple
    {
      template<typename Saver, typename Conv>
      void operator()(std::ostream& out, const Saver& s, const Conv& conv) const;

      template<typename Loader>
      void operator()(std::istream& in, Loader& l) const;
    };
  }

}

# include <vaucanson/tools/simple_format.hxx>

#endif
