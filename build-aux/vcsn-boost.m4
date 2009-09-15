AC_DEFUN([VCSN_BOOST],
[
AC_LANG_PUSH([C++])

AC_CHECK_HEADER([boost/version.hpp],, [AC_MSG_ERROR([
Cannot find Boost headers.  If they are installed on an unusuall path on
your system, please run configure with the suitable CPPFLAGS and LDFLAGS
options.  For instance if it is installed in /opt/boost/ please use:

  ./configure CPPFLAGS="-I/opt/boost/include" LDFLAGS="-L/opt/boost/lib"
])])

# Do not require boost::serialization headers.
CPPFLAGS="$CPPFLAGS -DBOOST_MULTI_INDEX_DISABLE_SERIALIZATION"

AC_CACHE_CHECK([whether Boost version is >= $1], [ac_cv_boost_recent],
[AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
@%:@include <boost/version.hpp>
]], [[
#if BOOST_VERSION >= $2
// Everything is okay
#else
#  error Boost version is too old
#endif
]])],[
ac_cv_boost_recent=yes
],[
ac_cv_boost_recent=no
])])
if test "x$ac_cvboost_recent" = xno; then
  AC_MSG_ERROR([Boost appears to be too old.  We need version 1.34 or more recent.])
fi

# FIXME: It would be nice to check the availability of the part of
# Boost we require (boost::graph, boost::multi_index...).  Some
# distribution, like Debian, split Boost in multiple packages.

AC_LANG_POP([C++])
])
