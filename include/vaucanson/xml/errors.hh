#ifndef VCSN_XML_ERRORS_HH
# define VCSN_XML_ERRORS_HH

# ifndef FAIL
#  define FAIL WITH_EXIT
# endif

# define WITH_EXIT(X) { warning( X ); exit(-1); }
# define WITH_THROW(X) throw(LoaderException( X ))

# include <string>

namespace vcsn
{
  namespace xml
  {
    class LoaderException {
    private:
      std::string _msg;
    public:
      LoaderException(const std::string& msg) : _msg(msg) { }
      std::string get_msg() const
      {
	return _msg;
      }
    };
  }
}

#endif // VCSN_XML_ERRORS_HH
