#ifndef VCSN_XML_ERRORS_HH
# define VCSN_XML_ERRORS_HH

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file errors.hh
 * @brief Error treatment for XML tools.
 * @author Valentin David <valentin@lrde.epita.fr>
 */

# ifndef FAIL
#  define FAIL WITH_EXIT
# endif

/// Errors make exits, use with @c #define @c FAIL @c WITH_EXIT
# define WITH_EXIT(X) { warning( X ); exit(-1); }
/// Errors make throws, use with @c #define @c FAIL @c WITH_THROW
# define WITH_THROW(X) throw(LoaderException( X ))

# include <string>

namespace vcsn
{
  namespace xml
  {
    /// Exception thrown by XML read operation.
    class LoaderException {
    private:
      std::string _msg;
    public:
      LoaderException(const std::string& msg) : _msg(msg) { }
      /// Get the error message.
      std::string get_msg() const
      {
	return _msg;
      }
    };
  }
}

/** @} */

#endif // VCSN_XML_ERRORS_HH
