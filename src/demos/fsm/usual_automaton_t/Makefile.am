AUTOMAKE_OPTIONS= foreign 1.6

CXXFLAGS = -Wall -O3 -DNDEBUG -Wno-unused -ftemplate-depth-99
#AM_CPPFLAGS = set by the user with -I ~/work/vaucanson/vaucanson/include.

bin_PROGRAMS =     vcsn_random_generator        vcsn_determinize	         vcsn_minimize	         vcsn_closure	         vcsn_prune		         vcsn_reverse	         vcsn_intersect	         vcsn_dotdump
vcsn_random_generator_SOURCES   = vcsn_random_generator.cc arg.cc
vcsn_determinize_SOURCES        = vcsn_determinize.cc arg.cc
vcsn_dotdump_SOURCES		= vcsn_dotdump.cc arg.cc
vcsn_minimize_SOURCES		= vcsn_minimize.cc arg.cc
vcsn_closure_SOURCES		= vcsn_closure.cc arg.cc
vcsn_reverse_SOURCES		= vcsn_reverse.cc arg.cc
vcsn_intersect_SOURCES		= vcsn_intersect.cc arg.cc
vcsn_prune_SOURCES		= vcsn_prune.cc arg.cc
EXTRA_DIST = arg.hh toolbox.hh
