# Makefile
# vcsn-Makefile: this file is part of the Vaucanson project.
# 
# Vaucanson, a generic library for finite state machines.
# 
# Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
# 
# The Vaucanson Group consists of people listed in the `AUTHORS' file.
#


# This Makefile can be used to develop a standalone program in
# Vaucanson. It uses a trick to enhance the compilation speed (you can
# gain a factor 5).  The trick is based on the fact that Vaucanson
# does not have to be analysed and instanciated at each modifications
# of your code.  During the first compilation, Vaucanson's code is
# collected in a compilation unit. In the next compilation, only the
# interface of Vaucanson will be used on the condition that no new
# Vaucanson code is instanciated. Otherwise, the system must collect
# the new code i.e.  it must recompile the two compilation units.

# System options.
CXX=g++
CXXFLAGS= # your compilation options (do not forget -DXXX for system
          # compliance).
CPPFLAGS= # -I your_vaucanson_directory
MAKE=make
GREP=grep
RM=rm -f

# Your program variables.
TARGET= # your program.
SOURCES= # its sources.
FAKE_SOURCES=$(SOURCES:.cc=.unitcc)
FAKE_UNITS=$(FAKE_SOURCES:.cc=.o)
OBJECTS=$(FAKE_SOURCES:.unitcc=.unito) $(SOURCES:.cc=.o)

all: $(TARGET)

# No dependency with the source.
%.unitcc: 
	@ SOURCE=`echo $@ | sed 's,.unitcc,.cc,'` \
	  && echo Collecting Vaucanson code in $$SOURCE. \
	  && $(GREP) '#include' $$SOURCE > $@ \
	  &&  echo 'namespace __instanciator_code {' >> $@ \
	  && $(GREP) -v '#include' $$SOURCE >> $@ \
	  && echo '}' >> $@

# The fake unit is compiled using all Vaucanson's code.
# It is very slow.
%.unito:%.unitcc
	$(CXX) -x c++ -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@ 

# Your source may only need the interface of Vaucanson if you do
# not use a code that is not already in the fake unit.
# Well, it is always slow (but less), this is due to C++ now.
%.o:%.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@ -DINTERFACE_ONLY

# The t-time: will your code be compiled quickly ?
$(TARGET): $(OBJECTS) 
	@ echo "Try to link."
	@ $(CXX) -o $@ $^ \
	  || (echo 'Sorry, it failed: we must recompile everything.' \
	  && ($(RM) $(FAKE_UNITS) && $(MAKE)))

clean:
	$(RM) $(OBJECTS) $(TARGET)