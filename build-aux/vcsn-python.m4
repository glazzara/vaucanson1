AC_DEFUN([VCSN_CHECK_PYTHON],
 [AM_PATH_PYTHON([2.2])
  AC_CACHE_CHECK([for $am_display_PYTHON includes directory],
    [vcsn_cv_python_inc],
    [vcsn_cv_python_inc=`$PYTHON -c "from distutils import sysconfig; print sysconfig.get_python_inc()" 2>/dev/null`])
  AC_SUBST([PYTHON_INCLUDEDIR], [$vcsn_cv_python_inc])])
