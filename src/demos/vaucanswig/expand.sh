#! /bin/sh

[ -d "$1" -a -f "$1/expand.sh" -a -f "$1/ChangeLog" ] || \
  { echo "usage: $0 <vaucanswig srcdir>" >&2; exit 1; }

VAUCANSWIG=`cd $1 && pwd`

mkdir -p "$VAUCANSWIG/src"
mkdir -p "$VAUCANSWIG/python"

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
AM_CPPFLAGS = -DEXCEPTION_TRAPS
# AM_CXXFLAGS = \$(CXXFLAGS_OPTIMIZE) 
AM_LDFLAGS = -shared -lswigpy -L../meta -lvv

EOF
}

dump_python()
{
    echo -n "pyexec_PROGRAMS ="
    ilist=0
    for mod in $MODULES; do
      if [ `expr $ilist % 4` = 0 ]; then
         echo " \\"; echo -ne "\t"
      fi
      echo -n " _vaucanswig_$mod.so" 
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
      echo "_vaucanswig_${mod}_so_SOURCES = vaucanswig_${mod}_wrap.cxx"
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
