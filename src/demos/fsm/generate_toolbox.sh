#!/bin/sh
# generate_toolbox.sh
#
# $Id$

# Check arguments
if [ $# -ne 1 ]; then
    echo "usage: ";
    echo "  generate_toolbox.sh  destination_dir";
    exit 1
fi

# Global variables
DESTDIR=$1

# vcsn_random_generator.cc
FILE=$DESTDIR/vcsn_random_generator.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include "arg.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh>   

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
     tools::fsm_dump(std::cout, automaton);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_kratexp2auto.cc
FILE=$DESTDIR/vcsn_kratexp2auto.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
    #include "arg.hh"
#include <vaucanson/algebra/concrete/series/rat/exp.hh>
#include <vaucanson/algebra/concrete/series/krat.hh>
#include <vaucanson/algorithms/glushkov.hh>
#include <vaucanson/algorithms/thompson.hh>
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
    using namespace vcsn;
    using namespace toolbox;

   int main(int argc, const char **argv)
   {
  AUTOMATON_TYPES_EXACT(automaton_t);
     Options  options[2] =
       {
	 { "-glushkov", o_none, "prefer glushkov construction.", true }
       };
     OptionsValues values(std::vector<Options>(options, options+1),argc,argv);
     std::list<std::string> remainder = values.get_remainder();
     if (remainder.size() < 1)
       {
	 values.usage_msg();
	 exit(EXIT_FAILURE);
       }
     std::string krat_exp_string = remainder.front();
     alphabet_t alpha;
     Element<series_t, rat::exp<monoid_elt_value_t, semiring_elt_value_t> >
       krat_exp(series());
     parse(krat_exp_string, krat_exp);
     automaton_t automaton;
     automaton.create();
     automaton.series() = series();
     if (values.get("-glushkov"))
	glushkov(automaton, krat_exp.value());
    else
	thompson_of(automaton, krat_exp.value());
     tools::fsm_dump(std::cout, automaton);
     return EXIT_SUCCESS;

   }
EOF

# vcsn_determinize.cc
FILE=$DESTDIR/vcsn_determinize.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/determinize.hh>
    using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     automaton_t auto_d = determinize(automaton);
     tools::fsm_dump(std::cout, auto_d);
     return EXIT_SUCCESS;
   }
EOF


# vcsn_minimize.cc
FILE=$DESTDIR/vcsn_minimize.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/hopcroft.hh>
   #include <vaucanson/algorithms/determinize.hh>
    using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     if (!is_deterministic(automaton))
       automaton = determinize(automaton);
     automaton_t auto_m = hopcroft_minimization_det(automaton);
     tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_closure.cc
FILE=$DESTDIR/vcsn_closure.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/forward_closure.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     automaton_t auto_m = forward_closure(automaton);
     tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_realtime.cc
FILE=$DESTDIR/vcsn_realtime.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/realtime.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     automaton_t auto_m = realtime(automaton);
     tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_reverse.cc
FILE=$DESTDIR/vcsn_reverse.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/transpose.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     automaton_t auto_m = transpose(automaton);
     tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_prune.cc
FILE=$DESTDIR/vcsn_prune.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/trim.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     automaton_t auto_m = trim(automaton);
     tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_intersect.cc
FILE=$DESTDIR/vcsn_intersect.cc
cat > $FILE <<EOF
   #include <iostream>
   #include <fstream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/product.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
    if (argc < 2)
      exit(EXIT_FAILURE);
     std::ifstream lhs(argv[1]);
     std::ifstream rhs(argv[2]);
     automaton_t lhs_a;
     tools::fsm_load(lhs, lhs_a);
     automaton_t rhs_a;
     tools::fsm_load(rhs, rhs_a);  
     automaton_t auto_m = product(lhs_a, rhs_a);
	tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_union.cc
FILE=$DESTDIR/vcsn_union.cc
cat > $FILE <<EOF
   #include <iostream>
   #include <fstream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/sum.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
    if (argc < 2)
      exit(EXIT_FAILURE);
     std::ifstream lhs(argv[1]);
     std::ifstream rhs(argv[2]);
     automaton_t lhs_a;
     tools::fsm_load(lhs, lhs_a);
     automaton_t rhs_a;
     tools::fsm_load(rhs, rhs_a);  
     automaton_t auto_m = sum(lhs_a, rhs_a);
	tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
EOF

# vcsn_dotdump.cc
FILE=$DESTDIR/vcsn_dotdump.cc
cat > $FILE <<EOF
   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/misc/dot_dump.hh> 

    using namespace vcsn;

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
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
    vcsn_kratexp2auto	     \
    vcsn_determinize	     \
    vcsn_minimize	     \
    vcsn_closure	     \
    vcsn_prune		     \
    vcsn_reverse	     \
    vcsn_realtime	     \
    vcsn_union		     \
    vcsn_intersect	     \
    vcsn_dotdump
vcsn_union_SOURCES		= vcsn_union.cc arg.cc toolbox.cc
vcsn_random_generator_SOURCES   = vcsn_random_generator.cc arg.cc toolbox.cc
vcsn_kratexp2auto_SOURCES	= vcsn_kratexp2auto.cc arg.cc toolbox.cc
vcsn_determinize_SOURCES        = vcsn_determinize.cc arg.cc toolbox.cc
vcsn_dotdump_SOURCES		= vcsn_dotdump.cc arg.cc toolbox.cc
vcsn_minimize_SOURCES		= vcsn_minimize.cc arg.cc toolbox.cc
vcsn_closure_SOURCES		= vcsn_closure.cc arg.cc toolbox.cc
vcsn_reverse_SOURCES		= vcsn_reverse.cc arg.cc toolbox.cc
vcsn_realtime_SOURCES		= vcsn_realtime.cc arg.cc toolbox.cc
vcsn_intersect_SOURCES		= vcsn_intersect.cc arg.cc toolbox.cc
vcsn_prune_SOURCES		= vcsn_prune.cc arg.cc toolbox.cc
EXTRA_DIST = arg.hh toolbox.hh
EOF
