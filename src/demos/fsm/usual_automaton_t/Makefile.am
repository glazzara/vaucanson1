AUTOMAKE_OPTIONS= foreign 1.6

CXXFLAGS = -Wall -O3 -DNDEBUG -Wno-unused -ftemplate-depth-99
#AM_CPPFLAGS = set by the user with -I/home/lrde/stud/yann/work/vaucanson/vaucanson/include/.

bin_PROGRAMS =     vcsn_random_generator        vcsn_determinize	         vcsn_minimize	         vcsn_dotdump
vcsn_random_generator_SOURCES   = vcsn_random_generator.cc arg.cc
vcsn_determinize_SOURCES        = vcsn_determinize.cc arg.cc
vcsn_dotdump_SOURCES		= vcsn_dotdump.cc arg.cc
vcsn_minimize_SOURCES		= vcsn_minimize.cc arg.cc
EXTRA_DIST = arg.hh toolbox.hh
