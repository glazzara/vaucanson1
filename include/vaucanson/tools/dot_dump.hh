#ifndef DOT_DUMP_HH
# define DOT_DUMP_HH

# include <vaucanson/tools/io.hh>
# include <vaucanson/tools/dot_format.hh>

namespace vcsn
{
  namespace tools
  {
    template<typename Auto>
    void dot_dump(std::ostream& o, const Auto& a, const std::string& name)
    {
      o << automaton_saver(a, io::string_out(), io::dot(name));
    }
  }
}


#endif
