#! /usr/bin/ruby
# generate_libvcsn.rb: this file is part of the Vaucanson project.
#
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2007 The Vaucanson Group.
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

# retrieve an array with all the headers contained
# in ./include/vaucanson/algorithms
files = Dir.glob("../include/vaucanson/algorithms/*.hh")

# get current time (needed for headers)
t = Time.now

# read the directory
files.each { |file|
  empty = true
  # checking for last update
  if ( ! File.exist?("vcsn-b/" + File.basename(file, ".hh") + ".cc") or
       File.new(file, "r").stat > File.new("vcsn-b/" + File.basename(file, ".hh") + ".cc").stat ) and
       # FIXME list of ignored files shall be removed later
       file !~ /invert.hh/ and			# transducer
       file !~ /composition_cover.hh/ and	# transducer
       file !~ /backward_realtime.hh/ and	# (co)accessible are missing? seems to be related to realtime.hh
       file !~ /normalized_composition.hh/ and	# transducer
       file !~ /is_letterized.hh/ and		# transducer
       file !~ /is_normalized.hh/ and		# transducer
       file !~ /realtime_decl.hh/ and		# do_(is_)realtime are missing?
       file !~ /krat_exp_linearize.hh/ and	# weird parsing which shall be done soon
       file !~ /extension.hh/			# transducer
    File.open(file, "r") {|f|
      # open the output file
      File.open("vcsn-b/" + File.basename(file, ".hh") + ".cc", "w") { |out|
	contents = f.readlines

	# print the header
	out.print "// ", File.basename(file, ".hh"), ".cc: this file is part of the Vaucanson project.\n"
	out.print "//\n"
	out.print "// Vaucanson, a generic library for finite state machines.\n"
	out.print "//\n"
	out.print "// Copyright (C) ", t.year, " The Vaucanson Group.\n"
	out.print "//\n"
	out.print "// This program is free software; you can redistribute it and/or\n"
	out.print "// modify it under the terms of the GNU General Public License\n"
	out.print "// as published by the Free Software Foundation; either version 2\n"
	out.print "// of the License, or (at your option) any later version.\n"
	out.print "//\n"
	out.print "// The complete GNU General Public Licence Notice can be found as the\n"
	out.print "// `COPYING' file in the root directory.\n"
	out.print "//\n"
	out.print "// The Vaucanson Group consists of people listed in the `AUTHORS' file.\n"
	out.print "//\n\n"
	out.print "#define VCSN_CONTEXT_NAMESPACE namespace boolean_automaton\n"
	out.print "#include <vaucanson/contexts/char_letter.thh>\n"
	out.print "#include <vaucanson/contexts/dynamic_alphabet.thh>\n"
	out.print "#include <vaucanson/contexts/free_monoid.thh>\n"
	out.print "#include <vaucanson/contexts/boolean_semiring.thh>\n"
	out.print "#include <vaucanson/contexts/generic_series.thh>\n"
	out.print "#include <vaucanson/contexts/generic_automaton_impl.thh>\n"
	out.print "#include <vaucanson/contexts/automaton.thh>\n"
	out.print "#include <vaucanson/algorithms/", File.basename(file), ">\n\n"
	out.print "namespace vcsn\n{\n"
	out.print "  VCSN_CONTEXT_NAMESPACE\n  {\n"
	out.print "    typedef vcsn::Automata<series_set_elt_t::set_t>	       automata_set_t;\n"
	out.print "    typedef vcsn::Element<automata_set_t, automaton_impl_t>    automaton_t;\n"
	out.print "    typedef vcsn::generalized_traits<automaton_t>::automaton_t gen_automaton_t;\n"
	out.print "  }\n\n"

	# read the file
	i = 0
	while i < contents.length
	  # template has been found
	  # process the file declaration
	  if contents[i] =~ /template\s*<typename\s*[A-Z]*,\s*typename\s*[A-Z]*>/
	    empty = false
	    out.print contents[i].gsub(/\s*<.*>/, "")
	    while i < contents.length and contents[i] !~ />/
	      i = i.next
	    end
	    i = i.next
	    while i < contents.length
	      out.print "", contents[i].gsub(/(typename\s*)*Element<\w*,\s*\w*>/, "boolean_automaton::automaton_t")
	      if contents[i] =~ /;/
		out.print "\n"
		break
	      end
	      i = i.next
	    end
	  elsif ( contents[i] =~ / namespace/ or contents[i] =~ /^\s+\}/ ) and
		( contents[i] !~ /vcsn/ and contents[i] !~ /\};/ )
	    out.puts contents[i]
	  end

	  i = i.next
	end
	out.print "}\n"
      }
    }
    # checking if there was any declaration kept from the current header
    if empty
      File.delete("vcsn-b/" + File.basename(file, ".hh") + ".cc")
    else
      print "Generating vcsn-b/", File.basename(file, ".hh"), ".cc\n"
    end
  end
}

# Generating the new Makefile.am
File.open("vcsn-b/Makefile.am.tmp", "w") { |out|
  out.puts("INCLUDES\t\t=  -I$(top_builddir)/include -I$(top_srcdir)/include",
	   "noinst_LIBRARIES\t= libvcsn-b.a",
	   "libvcsn_b_a_LIBADD\t= @LIBOBJS@")
  out.print "libvcsn_b_a_SOURCES\t=\t\t"
  files = Dir.glob("vcsn-b/*cc").sort!
  files.each { |filename| out.print "\\\n\t\t\t", File.basename(filename), "\t" }
  out.print "\n\n"
  out.puts("distclean-local:", "\trm -f *.cc")
}

# Checking if the new Makefile.am is really needed e.g. some modification has to be done
if File.exist?("vcsn-b/Makefile.am")
  `diff vcsn-b/Makefile.am vcsn-b/Makefile.am.tmp`
  if $? != 0
    print "Generating vcsn-b/Makefile.am\n"
    `mv vcsn-b/Makefile.am.tmp vcsn-b/Makefile.am`
  else
    File.delete("vcsn-b/Makefile.am.tmp")
  end
else
  print "Generating vcsn-b/Makefile.am\n"
  `mv vcsn-b/Makefile.am.tmp vcsn-b/Makefile.am`
end
