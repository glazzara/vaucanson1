# xml.m4

# Xerces C++
AC_DEFUN([VCSN_XML],
[
AC_ARG_WITH(
  [xerces],
  [  --with-xerces           specify Xerces-C++ location],
  [XERCESC=$withval],
  [if test "x$prefix" = xNONE; then
     XERCESC=$ac_default_prefix
   else
     XERCESC=$prefix
   fi])
AC_ARG_ENABLE(
  [xml],
  [  --enable-xml            enable xml tests (need Xerces-C++ 2.3.x library)],
  [ac_compile_xerces_check_save=$ac_compile
  ac_cpp_xerces_check_save=$ac_cpp
  ac_compile="$ac_compile -I${XERCESC}/include"
  ac_cpp="$ac_cpp -I${XERCESC}/include"
  AC_CHECK_HEADER(
    [xercesc/util/XercesVersion.hpp],
    [AC_MSG_CHECKING([Xerces-C++ version])
    AC_COMPILE_IFELSE(
      [AC_LANG_SOURCE(
        [
@%:@include <xercesc/util/XercesVersion.hpp>
@%:@if XERCES_VERSION_MAJOR != 2
@%:@ error "Bad Xerces-C++ major version."
@%:@endif
@%:@if XERCES_VERSION_MINOR != 3
@%:@ error "Bad Xerces-C++ minor version."
@%:@endif
        ])
      ],
      [
      AC_MSG_RESULT([2.3.x])
      LIBS_xerces_check_save=$LIBS
      AC_CHECK_LIB([xerces-c],[_ZN11xercesc_2_316XMLPlatformUtils9TerminateEv],
        AC_SUBST(XERCESC),
        AC_ERROR([Could not link to Xerces-C++ library.]),
        [-L${XERCESC}/lib])],
      AC_ERROR([Bad Xerces-C++ version.]))
      LIBS=$LIBS_xerces_check_save],
    AC_ERROR([Could not find Xerces-C++. Did you set --with-xerces argument?]))
  ac_compile=$ac_compile_xerces_check_save
  ac_cpp=$ac_cpp_xerces_check_save
  xml_check=true],
  xml_check=false
)
AM_CONDITIONAL(XML_CHECK, test x$xml_check = xtrue)
])
