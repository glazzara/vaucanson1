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

# Array filled with the supported types of automaton
vcsn = [ "vcsn-b", "vcsn-r", "vcsn-z", "vcsn-z-max", "vcsn-z-min",
	 "vcsn-fmp-tdc", "vcsn-tdc", "vcsn-z-fmp-tdc", "vcsn-z-tdc" ]

# testing if a source file needs to be created
def create?(type, file)
  (
    ! File.exist?(type + "/" + File.basename(file, ".hh") + ".cc") or
    File.new(file, "r").stat > File.new(type + "/" + File.basename(file, ".hh") + ".cc").stat
  ) and
  # FIXME list of ignored files for each shall be removed later
  file !~ /krat_exp_linearize.hh/ and	# weird parsing which shall be done soon
  (
    (
      ( "vcsn-b" == type or "vcsn-r" == type or "vcsn-z" == type or
	"vcsn-z-max" == type or "vcsn-z-min" == type ) and
      file !~ /backward_realtime.hh/ and	# realtime 
      file !~ /realtime_decl.hh/ and		# realtime
      file !~ /composition_cover.hh/ and	# transducer
      file !~ /extension.hh/ and		# transducer
      file !~ /invert.hh/ and			# transducer
      file !~ /is_letterized.hh/ and		# transducer
      file !~ /is_normalized.hh/ and		# transducer
      file !~ /normalized_composition.hh/	# transducer
    ) or
    (
      "vcsn-tdc" == type and
      file !~ /accessible.hh/ and
      file !~ /aut_to_exp.hh/ and
      file !~ /backward_realtime.hh/ and	# should work ?
      file !~ /complement.hh/ and
      file !~ /complete.hh/ and
      file !~ /composition_cover.hh/ and	# should work ?
      file !~ /determinize.hh/ and
      file !~ /extension.hh/ and
      file !~ /invert.hh/ and			# should work ?
      file !~ /is_letterized.hh/ and
      file !~ /is_normalized.hh/ and
      file !~ /minimization_hopcroft.hh/ and
      file !~ /normalized_composition.hh/ and
      file !~ /realtime_decl.hh/ and		# should work ?
      file !~ /standard.hh/
    ) or
    (
      "vcsn-fmp-tdc" == type and
      file !~ /backward_realtime.hh/ and	# should work ?
      file !~ /complement.hh/ and
      file !~ /complete.hh/ and
      file !~ /composition_cover.hh/ and	# should work ?
      file !~ /determinize.hh/ and
      file !~ /extension.hh/ and
      file !~ /forward_realtime.hh/ and	 	# should work ?
      file !~ /is_letterized.hh/ and
      file !~ /is_normalized.hh/ and
      file !~ /minimization_hopcroft.hh/ and
      file !~ /minimization_moore.hh/ and
      file !~ /normalized_composition.hh/ and
      file !~ /realtime.hh/ and			# should work ?
      file !~ /realtime_decl.hh/		# should work ?
    ) or
    (
      "vcsn-z-fmp-tdc" == type and
      file !~ /backward_realtime.hh/ and	# should work ?
      file !~ /complement.hh/ and
      file !~ /complete.hh/ and
      file !~ /composition_cover.hh/ and	# should work ?
      file !~ /determinize.hh/ and
      file !~ /extension.hh/ and
      file !~ /forward_realtime.hh/ and	 	# should work ?
      file !~ /is_letterized.hh/ and
      file !~ /is_normalized.hh/ and
      file !~ /minimization_hopcroft.hh/ and
      file !~ /minimization_moore.hh/ and
      file !~ /normalized_composition.hh/ and
      file !~ /realtime.hh/ and			# should work ?
      file !~ /realtime_decl.hh/		# should work ?
    ) or
    (
      "vcsn-z-tdc" == type and
      file !~ /aut_to_exp.hh/ and
      file !~ /backward_realtime.hh/ and	# should work ?
      file !~ /composition_cover.hh/ and	# should work ?
      file !~ /extension.hh/ and
      file !~ /invert.hh/ and			# should work ?
      file !~ /is_letterized.hh/ and
      file !~ /is_normalized.hh/ and
      file !~ /minimization_hopcroft.hh/ and
      file !~ /normalized_composition.hh/ and
      file !~ /realtime_decl.hh/ and		# should work ?
      file !~ /standard.hh/
    )
  )
end

# write a Makefile for `type`
def write_makefile(type)
  File.open(type + "/Makefile.am.tmp", "w") { |out|
    out.puts("## Vaucanson, a generic library for finite state machines.",
	     "## Copyright (C) " + Time.now.strftime("%Y") + " The Vaucanson Group.",
	     "##",
	     "## This program is free software; you can redistribute it and/or",
	     "## modify it under the terms of the GNU General Public License",
	     "## as published by the Free Software Foundation; either version 2",
	     "## of the License, or (at your option) any later version.",
	     "##",
	     "## The complete GNU General Public Licence Notice can be found as the",
	     "## `COPYING' file in the root directory.",
	     "##",
	     "## The Vaucanson Group consists of people listed in the `AUTHORS' file.",
	     "##",
	     "",
	     "INCLUDES\t\t=  -I$(top_builddir)/include -I$(top_srcdir)/include -I.",
	     "noinst_LTLIBRARIES\t= ../lib" + type + ".la",
	     "___lib" + type.gsub(/-/, "_") + "_la_LIBADD\t= @LIBOBJS@")
    out.print "___lib" + type.gsub(/-/, "_") + "_la_SOURCES\t= "
    files = Dir.glob(type + "/*cc").sort!
    files.each { |filename| out.print "\\\n\t\t\t", File.basename(filename), "\t" }
    out.print "\n\n"
    out.puts("distclean-local:", "\trm -f *.cc")
  }
end

# write the output file `type`/`fname` with `contents`
# headers are written according to the `type`
def write_src(type, fname, contents)
  puts "Generating " + type + "/" + fname
  File.open(type + '/' + fname, "w") { |out|
    out.puts("// " + fname + ": this file is part of the Vaucanson project.",
	     "//",
	     "// Vaucanson, a generic library for finite state machines.",
	     "//",
	     "// Copyright (C) " + Time.now.strftime("%Y") + " The Vaucanson Group.",
	     "//",
	     "// This program is free software; you can redistribute it and/or",
	     "// modify it under the terms of the GNU General Public License",
	     "// as published by the Free Software Foundation; either version 2",
	     "// of the License, or (at your option) any later version.",
	     "//",
	     "// The complete GNU General Public Licence Notice can be found as the",
	     "// `COPYING' file in the root directory.",
	     "//",
	     "// The Vaucanson Group consists of people listed in the `AUTHORS' file.",
	     "//",
	     "",
	     "#include <" + type.gsub(/-/, "_") + ".hh>",
	     "#include <vaucanson/algorithms/" + File.basename(fname, ".cc") + ".hh>",
	     "")
    out.puts(contents)
  }
end

# retrieve an array with all the headers contained
# in ./include/vaucanson/algorithms
files = Dir.glob("../include/vaucanson/algorithms/*.hh")

# read the directory
files.each { |file|
#  if create?("vcsn-b", file)
  empty = true
  File.open(file, "r") { |f|
    contents = f.readlines
    output = Array.new
    empty = true

    i = 0
    while i < contents.length
      # template has been found
      # process the file declaration
      if contents[i] =~ /template\s*<typename\s*[A-Z]*,\s*typename\s*[A-Z]*>/
	empty = false
	output.push(contents[i].gsub(/\s*<.*>/, ""))
	while i < contents.length and contents[i] !~ />/
	  i = i.next
	end
	i = i.next
	while i < contents.length
	  output.push(contents[i].gsub(/(typename\s*)*Element<\w*,\s*\w*>/, "VCSN_CONTEXT::automaton_t"))
	  if contents[i] =~ /;/
	    output.push("")
	    break
	  end
	  i = i.next
	end
      elsif ( contents[i] =~ /namespace/ or contents[i] =~ /(\{|\})/ ) and
	    ( contents[i] !~ /(\};|\*)/ )
	output.push(contents[i])
      end

      i = i.next
    end

    vcsn.each { |type|
      if create?(type, file) and ! empty
	# file has template to instanciate, write it down!
	# checking if there was any declaration kept from the current header
	write_src(type, File.basename(file, ".hh") + ".cc", output)
      end
    }
  }
}

# writing Makefiles
vcsn.each { |type|
  write_makefile(type)
  if File.exist?(type + "/Makefile.am")
    system("diff " + type + "/Makefile.am " + type + "/Makefile.am.tmp > /dev/null")
    if $? != 0
      puts "Generating " + type + "/Makefile.am"
      system("mv -f " + type + "/Makefile.am.tmp " + type + "/Makefile.am")
    else
      File.delete(type + "/Makefile.am.tmp")
    end
  else
    puts "Generating " + type + "/Makefile.am"
    system("mv " + type + "/Makefile.am.tmp " + type + "/Makefile.am")
  end
}
