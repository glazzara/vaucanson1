#!/bin/sh
# generate_toolbox.sh
#
# $Id$

# Global variables
DESTDIR=$1

# vcsn_random_generator.cc
FILE=$DESTDIR/vcsn_random_generator.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include "arg.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh>   

   using namespace toolbox;
    using namespace vcsn;

   int main(int argc, const char **argv)
   {
     Options  options[2] =
     {
       { "-s", o_int, "number of states. [default is 10]", true },
       { "-e", o_int, "number of edges.  [default is 20]" , true }
     };
     OptionsValues values(std::vector<Options>(options, options+2),argc,argv);
     int nb_states = 10;
     int nb_edges  = 20;
     if (values.get_int("-s") != 0)
       nb_states = *values.get_int("-s");
     if (values.get_int("-e") != 0)
       nb_edges = *values.get_int("-e");
     srand(time(0));
     GenRandomAutomata<automaton_t> gen;
     automaton_t automaton = gen.generate(nb_states, nb_edges);
     misc::fsm_dump(std::cout, automaton);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_determinize.cc
FILE=$DESTDIR/vcsn_determinize.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/algorithms/determinize.hh>
    using namespace vcsn;

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     misc::fsm_load(std::cin, automaton);
     automaton_t auto_d = determinize(automaton);
     misc::fsm_dump(std::cout, auto_d);
     return EXIT_SUCCESS;
   }
EOF


# vcsn_minimize.cc
FILE=$DESTDIR/vcsn_minimize.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/algorithms/hopcroft.hh>
   #include <vaucanson/algorithms/determinize.hh>
    using namespace vcsn;

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     misc::fsm_load(std::cin, automaton);
     if (!is_deterministic(automaton))
       automaton = determinize(automaton);
     automaton_t auto_m = hopcroft_minimization_det(automaton);
     misc::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF


# vcsn_dotdump.cc
FILE=$DESTDIR/vcsn_dotdump.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/misc/dot_dump.hh> 

    using namespace vcsn;

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     misc::fsm_load(std::cin, automaton);
     misc::dot_dump(std::cout, automaton, "automaton");
     return EXIT_SUCCESS;
   }
EOF

# installing include files

cp arg.hh $DESTDIR
cp arg.cc $DESTDIR

# configure.ac
FILE=$DESTDIR/configure.ac
cat > $FILE <<EOF
AC_PREREQ([2.50])
AC_INIT([vcsn-generated], [1.0], [])
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_PROG_CXX
AC_LANG(C++)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

EOF

# Makefile.am
FILE=$DESTDIR/Makefile.am
cat > $FILE <<EOF
AUTOMAKE_OPTIONS= foreign 1.6

CXXFLAGS = -Wall -O3 -DNDEBUG -Wno-unused -ftemplate-depth-99
#AM_CPPFLAGS = set by the user with $CPPFLAGS.

bin_PROGRAMS = \
    vcsn_random_generator    \
    vcsn_determinize	     \
    vcsn_minimize	     \
    vcsn_dotdump
vcsn_random_generator_SOURCES   = vcsn_random_generator.cc arg.cc
vcsn_determinize_SOURCES        = vcsn_determinize.cc arg.cc
vcsn_dotdump_SOURCES		= vcsn_dotdump.cc arg.cc
vcsn_minimize_SOURCES		= vcsn_minimize.cc arg.cc
EXTRA_DIST = arg.hh toolbox.hh
EOF
