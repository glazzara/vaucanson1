#! /bin/sh

[ -d "$1" -a -f "$1/expand.sh" -a -f "$1/ChangeLog" ] || \
  { echo "usage: $0 <vaucanswig srcdir>" >&2; exit 1; }

VAUCANSWIG=`cd $1 && pwd`

mkdir -p "$VAUCANSWIG/src"
mkdir -p "$VAUCANSWIG/python"
cp -f "$VAUCANSWIG"/meta/vauto.cc "$VAUCANSWIG"/meta/vcontext.cc "$VAUCANSWIG/python"

MODULES="core $MODULES"

for cat in usual numerical tropical_max tropical_min; do
  for mod in context automaton; do
     cat >"$VAUCANSWIG/src/vaucanswig_${cat}_${mod}.i" <<EOF
%include vaucanswig_${mod}.i
%module vaucanswig_${cat}_${mod}
decl_${mod}(${cat})
EOF
     MODULES="$MODULES ${cat}_${mod}"
  done
done

#################### Python stuff #######################

PYMODS=''
PYTHON=''

header_python()
{
cat <<EOF
## Process this file through Automake to produce Makefile.in -*- Makefile -*-
##
## Makefile.am for vaucanswig/python
## NOTE: this file was generated automatically by expand.sh
##

INCLUDES = -I/usr/include/python2.2 -I\$(srcdir)/../src -I\$(srcdir)/../meta \\
    -I\$(top_srcdir)/include -I\$(top_builddir)/include
AM_CPPFLAGS = -DINTERNAL_CHECKS -DSTRICT -DEXCEPTION_TRAPS
# AM_CXXFLAGS = \$(CXXFLAGS_OPTIMIZE) 
AM_LDFLAGS = -module -avoid-version

EOF
}

dump_python()
{
    echo -n "pyexec_LTLIBRARIES ="
    ilist=0
    for mod in $MODULES; do
      if [ `expr $ilist % 4` = 0 ]; then
         echo " \\"; echo -ne "\t"
      fi
      echo -n " libvs_$mod.la" 
      ilist=`expr $ilist + 1`
    done
    echo; echo
    echo -n "python_PYTHON ="
    ilist=0
    for mod in $MODULES; do
      if [ `expr $ilist % 4` = 0 ]; then 
         echo " \\"; echo -ne "\t" 
      fi 
      echo -n " vaucanswig_${mod}.py"
      ilist=`expr $ilist + 1` 
    done
    echo; echo
    for mod in $MODULES; do
      echo "libvs_${mod}_la_SOURCES = vaucanswig_${mod}_wrap.cxx"
      if [ "$mod" = "core" ]; then
        echo "libvs_core_la_LIBADD = ../meta/libvv.la -lswigpy"
      else
        if echo "$mod" | grep "_automaton" >/dev/null 2>&1; then
           ctx=`echo "$mod" | sed -e 's,_automaton,,g'`
           echo "libvs_${mod}_la_LIBADD = libvs_${ctx}_context.la"
        else
           echo "libvs_${mod}_la_LIBADD = libvs_core.la"
        fi
      fi
    done
    echo
    ilist=0
    for mod in $MODULES; do
      if [ -r "$VAUCANSWIG/src/vaucanswig_${mod}.i" ]; then 
         sdir=src
      else
         sdir=meta
      fi
      echo "vaucanswig_${mod}_wrap.cxx vaucanswig_${mod}.py: \$(srcdir)/../$sdir/vaucanswig_${mod}.i"
      echo -e "\t\$(SWIG) -c -c++ -python -I\$(srcdir)/../src -I\$(srcdir)/../meta \$(CPPFLAGS) -o vaucanswig_${mod}_wrap.cxx \$(srcdir)/../$sdir/vaucanswig_${mod}.i"
      echo
    done

    echo "install-exec-hook:"
    for mod in $MODULES; do
      echo -e "\tcd \$(pyexecdir) && rm -f _vaucanswig_$mod.so && \$(LN_S) libvs_$mod.so _vaucanswig_$mod.so"
    done
    echo
    echo "uninstall-hook:"
    for mod in $MODULES; do
      echo -e "\trm -f \$(pyexecdir)/_vaucanswig_$mod.so"
    done
    echo  
}

############ Generic stuff ###########

header_src() {
    cat <<EOF
## Process this file through Automake to produce Makefile.in -*- Makefile -*- 
## 
## Makefile.am for vaucanswig/src
## NOTE: this file was generated automatically by expand.sh 
## 
EOF
}

dump_src() {
    echo -n "EXTRA_DIST ="
    ilist=0
    for mod in $MODULES; do
      if [ -r "$VAUCANSWIG/src/vaucanswig_${mod}.i" ]; then 
         if [ `expr $ilist % 4` = 0 ]; then
	    echo " \\"
            echo -ne "\t"
	 fi
	 echo -n " vaucanswig_${mod}.i"
	 ilist=`expr $ilist + 1`
      fi
    done
    echo
}

############ Output ###############


header_src >"$VAUCANSWIG/src/Makefile.am"
dump_src >>"$VAUCANSWIG/src/Makefile.am"
header_python >"$VAUCANSWIG/python/Makefile.am"
dump_python >>"$VAUCANSWIG/python/Makefile.am"
