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

# Hash table filled with the supported types of automaton
vcsn = Hash[
  "vcsn-b" => "boolean_automaton",
  "vcsn-r" => "r_automaton",
  "vcsn-z" => "z_automaton",
  "vcsn-z-max" => "z_max_plus_automaton",
  "vcsn-z-min" => "z_min_plus_automaton",
  "vcsn-fmp-tdc" => "fmp_transducer",
  "vcsn-tdc" => "boolean_transducer",
  "vcsn-z-fmp-tdc" => "z_fmp_transducer",
  "vcsn-z-tdc" => "z_transducer"
]

# Creating directories in lib/
vcsn.each_key { |type| system("mkdir -p " + type) }

# testing if a source file needs to be created
def create?(type, file)
  (
    ! File.exist?(type + "/" + type + "_" + File.basename(file, ".hh") + ".cc") or
    File.new(file, "r").stat > File.new(type + "/" + type + "_" + File.basename(file, ".hh") + ".cc").stat
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

# write a *.mk for `type`
def write_makefile(type)
  puts("Generating " + type + "/lib" + type + ".mk")
  File.open(type + "/lib" + type + ".mk", "w") { |out|
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
#	     "INCLUDES\t\t=  -I$(top_builddir)/include -I$(top_srcdir)/include",
	     "noinst_LTLIBRARIES\t+= lib" + type + ".la",
	     "lib" + type.gsub(/-/, "_") + "_la_LIBADD\t= $(LIBOBJS)")
    out.print "lib" + type.gsub(/-/, "_") + "_la_SOURCES\t= "
    files = Dir.glob(type + "/*cc").sort!
    files.each { |filename| out.print "\\\n\t\t\t", filename, "\t" }
    out.print "\n\n"
    out.puts("MAINTAINERCLEANFILES += $(lib" + type.gsub(/-/, "_") + "_la_SOURCES) " +
	      type + "/lib" + type + ".mk")
  }
end

# write the output file `type`/`fname` with `contents`
# headers are written according to the `type`
def write_src(type, context, fname, contents)
  puts "Generating " + type + "/" + type + "_" + fname
  File.open(type + '/' + type + "_" + fname, "w") { |out|
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
	     "#include <vaucanson/" + context + "_structures.hh>",
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

    vcsn.each { |type, context|
      if create?(type, file) and ! empty
	# file has template to instanciate, write it down!
	# checking if there was any declaration kept from the current header
	write_src(type, context, File.basename(file, ".hh") + ".cc", output)
      end
    }
  }
}

# writing Makefiles
vcsn.each_key { |type| write_makefile(type) }

