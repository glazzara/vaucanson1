# xml.m4

# Macro used in ARC_ARG_ENABLE([xml], ...)
AC_DEFUN([ENABLE_VCSN_XML], 
  [
    xml_check=true
    ac_compile_xerces_check_save=$ac_compile
    ac_cpp_xerces_check_save=$ac_cpp
    ac_compile="$ac_compile -I${XERCESC}/include"
    ac_cpp="$ac_cpp -I${XERCESC}/include"
    AC_CHECK_HEADER(
      [xercesc/util/XercesVersion.hpp],
      [
	AC_MSG_CHECKING([Xerces-C++ version is greater than 2.3])
	AC_COMPILE_IFELSE(
	  [
            AC_LANG_SOURCE([
@%:@include <xercesc/util/XercesVersion.hpp>
@%:@if XERCES_VERSION_MAJOR != 2
@%:@ error "Bad Xerces-C++ major version."
@%:@endif
@%:@if XERCES_VERSION_MINOR < 3
@%:@ error "Bad Xerces-C++ minor version."
@%:@endif])
	  ],
          [
	    AC_MSG_RESULT([ok])
	    LIBS_xerces_check_save=$LIBS
            AC_SUBST(XERCESC)
	  ],
          [AC_ERROR([Bad Xerces-C++ version.])])
        LIBS=$LIBS_xerces_check_save
      ],
      [
	AC_ERROR([Could not find Xerces-C++ headers.])
	ac_compile=$ac_compile_xerces_check_save
	ac_cpp=$ac_cpp_xerces_check_save
      ])
  ])


# Xerces C++
AC_DEFUN([VCSN_XML],
[
AC_ARG_WITH(
  [xerces],
  [AC_HELP_STRING([--with-xerces],
  		   [specify Xerces-C++ location])],
  [XERCESC=$withval],
  [if test "x$prefix" = xNONE; then
     XERCESC=$ac_default_prefix
   else
     XERCESC=$prefix
   fi])
AC_ARG_ENABLE(
  [xml],
  [AC_HELP_STRING([--enable-xml],
		   [Enable XML tests (need Xerces-C++ library >= 2.3)])],
  [if test "x$enableval" = xno; then
	xml_check=false
  else
	ENABLE_VCSN_XML
  fi],
  [ ENABLE_VCSN_XML ]
)
AM_CONDITIONAL(XML_CHECK, test x$xml_check = xtrue)
])
