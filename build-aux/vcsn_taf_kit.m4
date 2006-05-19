
## Terminal library test, taken from GNU Texinfo configure.ac
AC_DEFUN([VCSN_CHECK_TERMLIB],
[dnl
  AC_CHECK_HEADERS(ncurses/termcap.h termcap.h)

  # Some GNU/Linux systems (e.g., SuSE 4.3, 1996) don't have curses, but
  # rather ncurses.  So we check for it.
  TERMLIBS=
  # Check for termlib before termcap because Solaris termcap needs libucb.
  TERMLIB_VARIANTS="ncurses curses termlib termcap terminfo"
  for termlib in ${TERMLIB_VARIANTS}; do
    AC_CHECK_LIB(${termlib}, tgetent,
       [TERMLIBS="${TERMLIBS} -l${termlib}"; break])
  done
  AC_SUBST([TERMLIBS])
])

## TAF Kit enabling
AC_DEFUN([VCSN_TAF_KIT],
[dnl

  AC_ARG_ENABLE([taf-kit],
		[AC_HELP_STRING([--disable-taf-kit],
		  [disable TAF-Kit (binary toolkit) compilation])],
		[enable_taf_kit=$enableval],
		[enable_taf_kit=yes])

  if test x$enable_taf_kit = xyes; then
    if test x$enable_vcsn_xml = xno; then
      AC_MSG_WARN([XML support should be enabled for TAF-Kit to be compiled,
      		   it will not be built])
      enable_taf_kit=no
    else
      VCSN_CHECK_TERMLIB
      if test -z "$TERMLIBS"; then
        AC_MSG_WARN([need a terminal library (${TERMLIB_VARIANTS}), TAF-Kit
		     will not be built])
    	enable_taf_kit=no
      fi
    fi
  else
    enable_taf_kit=no
  fi
m4_pattern_allow([^VCSN_TAF_KIT$])dnl Hum... Dangerous.
  AM_CONDITIONAL([VCSN_TAF_KIT], [test x$enable_taf_kit = xyes])
])
