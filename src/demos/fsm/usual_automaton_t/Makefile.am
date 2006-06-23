AUTOMAKE_OPTIONS= foreign 1.6

CXXFLAGS = -Wall -O3 -DNDEBUG -Wno-unused -ftemplate-depth-99
#AM_CPPFLAGS = set by the user with .

bin_PROGRAMS =     vcsn_random_generator        vcsn_kratexp2auto	         vcsn_determinize	         vcsn_minimize	         vcsn_closure	         vcsn_prune		         vcsn_reverse	         vcsn_realtime	         vcsn_union		         vcsn_intersect	         vcsn_dotdump
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
