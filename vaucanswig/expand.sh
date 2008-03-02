#! /bin/sh

set -e

[ -d "$1" -a -f "$1/expand.sh" -a -f "$1/ChangeLog" ] || \
  { echo "usage: $0 <vaucanswig srcdir>" >&2; exit 1; }

VAUCANSWIG=`cd $1 && pwd`
VAUC=$VAUCANSWIG/../include

mkdir -p "$VAUCANSWIG/src"
mkdir -p "$VAUCANSWIG/python"

MODULES="core $MODULES"
ALGS=""

#### ALGORITHM DATABASE RETRIEVAL ####

ALGDB=$VAUCANSWIG/src/vaucanswig_algorithms.i
dbapp() {
  echo "$@" >>"$ALGDB"
}

start_algorithms() {
  # General database header
  echo "%include vaucanswig_algo_common.i" >"$ALGDB"
  dbapp "%define decl_algorithms(Kind)"
  dbapp "%include vaucanswig_exception.i"
  dbapp "algo_common_decls(Kind)"
}

end_algorithms() {
  dbapp "%inline %{"
  dbapp "struct empty {};"
  dbapp "struct Kind :"
  for af in $ALGS; do
    dbapp "Kind ##_$af,"
  done
  dbapp " empty {};"
  dbapp "%}"
  dbapp "%enddef"
}

# afapp FAMILY-NAME LINES...
afapp() {
  AF=$1
  AFDB=$VAUCANSWIG/src/vaucanswig_alg_$AF.i
  shift
  for i
  do
    echo "$i" >>"$AFDB"
  done
}

start_family() {
  AF=$1
  AFDB=$VAUCANSWIG/src/vaucanswig_alg_$AF.i
  echo >"$AFDB"
  afapp "$AF" "%include vaucanswig_algo_common.i"
  afapp "$AF" "%{"
  afapp "$AF" "#include <vaucanson/algorithms/$AF.hh>"
  afapp "$AF" "%}"
}

do_family_interface_impl() {
  AF=$1
  AFDB=$VAUCANSWIG/src/vaucanswig_alg_$AF.i
  afapp "$AF" "%define alg_${AF}_interface_impl(Automaton, GenAutomaton, Series, Exp, HList)"
  cat "$VAUC/vaucanson/algorithms/$AF.hh" \
     | sed -n -e '/^ *\/\/ INTERFACE:/{s,^ *// INTERFACE:,static ,g;p;}' \
     | sed -e 's/ExpImpl/Exp/' \
     >>"$AFDB"
  afapp "$AF" "%enddef"
}

do_family_interface() {
  AF=$1
  AFDB=$VAUCANSWIG/src/vaucanswig_alg_$AF.i
  afapp "$AF" "%define alg_${AF}_interface(Automaton, GenAutomaton, Series, Exp, HList)"
  cat "$VAUC/vaucanson/algorithms/$AF.hh" \
     | sed -n -e '/^ *\/\/ INTERFACE:/{s,^ *// INTERFACE: \([^{]*\).*$,static \1;,g;p;}' \
     | sed -e 's/ExpImpl/Exp/' \
     >>"$AFDB"
  afapp "$AF" "%enddef"
}

# output FAMILY-NAME
# ------------------
output ()
{
  family_name=$1
  # Create a sub-database with its header
  start_family "$family_name"

  do_family_interface "$family_name"
  do_family_interface_impl "$family_name"

  afapp "$family_name"							  \
    "%define alg_interface_${family_name}(Kind)"			  \
    "%{"								  \
    "struct Kind ##_alg_${family_name} {"				  \
    "alg_${family_name}_interface(Kind ##_types::Kind ##_auto_t, \\"	  \
    "                     Kind ##_types::gen_## Kind ##_auto_t, \\"	  \
    "                     Kind ##_types::Kind ##_series_set_elt_t, \\"	  \
    "                     Kind ##_types::Kind ##_exp_t, std::list<int>)"  \
    "};"								  \
    "%}"								  \
    "%enddef"								  \
    "%define decl_alg_${family_name}(Kind)"				  \
    "algo_common_decls(Kind)"						  \
    "%{"								  \
    "struct Kind ##_alg_${family_name} {"				  \
    "alg_${family_name}_interface_impl(Kind ##_types::Kind ##_auto_t, \\" \
    "                     Kind ##_types::gen_## Kind ##_auto_t, \\"	  \
    "                     Kind ##_types::Kind ##_series_set_elt_t, \\"	  \
    "                     Kind ##_types::Kind ##_exp_t, std::list<int>)"  \
    "};"								  \
    "%}"								  \
    "struct Kind ##_alg_${family_name} {"				  \
    "alg_${family_name}_interface(Kind ##_types::Kind ##_auto_t, \\"	  \
    "                     Kind ##_types::gen_## Kind ##_auto_t, \\"	  \
    "                     Kind ##_types::Kind ##_series_set_elt_t, \\"	  \
    "                     Kind ##_types::Kind ##_exp_t, std::list<int>)"  \
    "};"								  \
    "%enddef"

  # Mention the sub-database in the general database
  dbapp "%import vaucanswig_## Kind ##_alg_${family_name}.i"
  dbapp "%include vaucanswig_alg_${family_name}.i"
  dbapp "alg_interface_${family_name}(Kind)"
}

start_algorithms

if [ "$3" != "noalg" ]; then
# Loop over all algorithm families
for family_header in `cd "$VAUC" && find vaucanson/algorithms -name \*.hh`; do

   # Test whether the file declares some interfaces
   if grep "^ *// INTERFACE:" <"$VAUC/$family_header" >/dev/null 2>&1; then

      # Yes, retrieve the algorithm family name.
      output $(basename "$family_header" .hh)

     # Add the sub-database to the algorithm category
     ALGS="$ALGS alg_${family_name}"
   fi
done
fi

end_algorithms
#### #####


if [ "x$2" = "xshort" ]; then
  kinds="boolean_automaton"
else
  kinds="boolean_automaton z_automaton z_max_plus_automaton z_min_plus_automaton"
fi

for cat in $kinds; do
  for mod in context $ALGS algorithms; do
     cat >"$VAUCANSWIG/src/vaucanswig_${cat}_${mod}.i" <<EOF
%include vaucanswig_${mod}.i
%module vaucanswig_${cat}_${mod}
decl_${mod}(${cat})
EOF
     MODULES="$MODULES ${cat}_${mod}"
  done
  cat >"$VAUCANSWIG/src/vaucanswig_${cat}.i" <<EOF
%include vaucanswig_automaton.i
%module vaucanswig_${cat}
decl_automaton(${cat})
EOF
      MODULES="$MODULES ${cat}"
  echo "${cat}_context" >"$VAUCANSWIG/src/${cat}.deps"
  echo >"$VAUCANSWIG/src/${cat}_algorithms.deps"
  for alg in $ALGS; do
    echo "${cat}" >"$VAUCANSWIG/src/${cat}_${alg}.deps"
    echo "${cat}_${alg}" >>"$VAUCANSWIG/src/${cat}_algorithms.deps"
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

INCLUDES = -I\$(PYTHON_PREFIX)/include/python\$(PYTHON_VERSION) -I\$(srcdir)/../src -I\$(srcdir)/../meta \\
    -I\$(top_srcdir)/include -I\$(top_builddir)/include
AM_CPPFLAGS = -DINTERNAL_CHECKS -DSTRICT -DEXCEPTION_TRAPS -DVCSN_DEFAULT_GRAPH_IMPL=legacy
AM_CXXFLAGS = \$(CXXFLAGS_DEBUG)
AM_LDFLAGS = -avoid-version

EOF
}

# canonical NAME
# Return an Automake canonical name, i.e., non-alphanumerical -> _.
canonical ()
{
  echo "$@" | sed 's/[^a-zA-Z0-9]/_/g'
}

dump_python()
{
    printf "pyexec_LTLIBRARIES ="
    ilist=0
    for mod in $MODULES; do
      if [ `expr $ilist % 4` = 0 ]; then
         echo " \\"; printf "\t"
      fi
      printf " libvs_$mod.la"
      ilist=`expr $ilist + 1`
    done
    echo; echo
    printf "python_PYTHON ="
    ilist=0
    for mod in $MODULES; do
      if [ `expr $ilist % 4` = 0 ]; then
         echo " \\"; printf "\t"
      fi
      printf " vaucanswig_$(canonical $mod).py"
      ilist=`expr $ilist + 1`
    done
    echo; echo
    for mod in $MODULES; do
      echo "libvs_$(canonical $mod)_la_SOURCES = vaucanswig_$(canonical $mod)_wrap.cxx"
      if [ "$mod" = "core" ]; then
        echo "libvs_core_la_LIBADD = ../meta/libvv.la"
      else
        if test -r "$VAUCANSWIG/src/$mod.deps"; then
           printf "libvs_$(canonical $mod)_la_LIBADD ="
           for dep in `cat "$VAUCANSWIG/src/$mod.deps"`; do
              printf " libvs_${dep}.la"
           done
        else
           printf "libvs_$(canonical $mod)_la_LIBADD = libvs_core.la"
        fi
#	case "$mod" in
#	  boolean_automaton*) printf ' $(top_builddir)/lib/libvcsn-b.la';;
#	  z_automaton*) printf ' $(top_builddir)/lib/libvcsn-z.la';;
#	  z_max_plus_automaton*) printf ' $(top_builddir)/lib/libvcsn-z-max.la';;
#	  z_min_plus_automaton*) printf ' $(top_builddir)/lib/libvcsn-z-min.la';;
#	esac
	echo
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
      printf "\t\$(SWIG) -c++ -fcompact -fvirtual -python -I../src -I../meta -I\$(srcdir)/../src -I\$(srcdir)/../meta \$(CPPFLAGS) -o vaucanswig_${mod}_wrap.cxx \$(srcdir)/../$sdir/vaucanswig_${mod}.i\n"
      echo
    done

    echo "install-exec-hook:"
    for mod in $MODULES; do
      printf "\tcd \$(DESTDIR)\$(pyexecdir) && rm -f _vaucanswig_$mod.so && \$(LN_S) libvs_$mod.so _vaucanswig_$mod.so\n"
    done
    echo
    echo "uninstall-hook:"
    for mod in $MODULES; do
      printf "\trm -f \$(DESTDIR)\$(pyexecdir)/_vaucanswig_$mod.so\n"
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
    printf "EXTRA_DIST ="
    ilist=0
    for mod in $MODULES $ALGS algorithms; do
      if [ -r "$VAUCANSWIG/src/vaucanswig_${mod}.i" ]; then
         if [ `expr $ilist % 4` = 0 ]; then
	    echo " \\"
            printf "\t"
	 fi
	 printf " vaucanswig_${mod}.i"
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
