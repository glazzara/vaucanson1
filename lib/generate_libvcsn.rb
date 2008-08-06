#! /usr/bin/ruby
# generate_libvcsn.rb: this file is part of the Vaucanson project.
#
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2007, 2008 The Vaucanson Group.
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
  file !~ /krat_exp_cderivation.hh/ and
  file !~ /thompson.hh/ and
  (
    ! File.exist?(type + "/" + File.basename(file, ".hh") + ".cc") or
    File.new(file, "r").stat > File.new(type + "/" + File.basename(file, ".hh") + ".cc").stat
  ) and
  (
    # FIXME: The following tests shall be removed
    # FIXME: more comments with the some specs on the algorithms must be added to do so
    (
      ( "vcsn-b" == type or "vcsn-r" == type or "vcsn-z" == type or
	"vcsn-z-max" == type or "vcsn-z-min" == type ) and
      file !~ /realtime_decl.hh/ and
      file !~ /composition_cover.hh/ and	# transducer
      file !~ /extension.hh/ and		# transducer
      file !~ /invert.hh/ and			# transducer
      file !~ /is_letterized.hh/ and		# transducer
      file !~ /is_normalized.hh/ and		# transducer
      file !~ /normalized_composition.hh/	# transducer
    ) or
    (
      (
	"vcsn-fmp-tdc" == type or "vcsn-tdc" == type or
	"vcsn-z-fmp-tdc" == type or "vcsn-z-tdc" == type
      ) and
      file !~ /aci_canonical.hh/ and
      file !~ /berry_sethi.hh/ and
      file !~ /brzozowski.hh/ and
      file !~ /complement.hh/ and
      file !~ /composition_cover.hh/ and
      file !~ /derived_term_automaton.hh/ and
      file !~ /determinize.hh/ and
      file !~ /equivalent.hh/ and
      file !~ /eval.hh/ and
      file !~ /extension.hh/ and
      file !~ /finite_support_conversion.hh/ and
      file !~ /is_ambiguous.hh/ and
      file !~ /is_letterized.hh/ and
      file !~ /is_normalized.hh/ and
      file !~ /krat_exp.*.hh/ and
      file !~ /letter_to_letter_composition.hh/ and
      file !~ /minimization_hopcroft.hh/ and
      file !~ /minimization_moore.hh/ and
      file !~ /normalized_composition.hh/ and
      file !~ /realtime_decl.hh/ and
      file !~ /realtime.hh/ and
      file !~ /standard.hh/ and
      file !~ /standard_of.hh/ and
      (
        ("vcsn-fmp-tdc" == type and "vcsn-z-fmp-tdc" == type) or
          (
	   file !~ /complete.hh/ and
	   file !~ /is_deterministic.hh/ and
           file !~ /product.hh/
          )
      )
    )
  )
end

# write a *.mk for `type`
def write_makefile(type, context)
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
	     "## NOTE: this file was generated automatically with generate_libvcsn.rb",
	     "##",
	     "",
	     "lib_LTLIBRARIES\t+= lib" + type + ".la",
	     "lib" + type.gsub(/-/, "_") + "_la_CXXFLAGS\t= $(CXXFLAGS) -DVCSN_CONTEXT=" + context,
	     "lib" + type.gsub(/-/, "_") + "_la_LIBADD\t= $(LIBOBJS)")
    out.print "lib" + type.gsub(/-/, "_") + "_la_SOURCES\t= "
    files = Dir.glob(type + "/*cc").sort!
    files.each { |filename|
      if File.exist?("../include/vaucanson/algorithms/" + File.basename(filename, ".cc") + ".hh")
	out.print "\\\n\t\t\t", filename, "\t"
      else
	File.unlink(filename)
	puts "Removing " + filename
      end
    }
    out.print "\n\n"
    out.puts("MAINTAINERCLEANFILES += $(lib" + type.gsub(/-/, "_") + "_la_SOURCES) " +
	      type + "/lib" + type + ".mk")
  }
  puts("Generating " + type + "/lib" + type + ".mk")
end

# write the output file `type`/`fname` with `contents`
# headers are written according to the `type`
def write_src(type, context, fname, contents)
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
	     "// NOTE: this file was generated automatically with generate_libvcsn.rb",
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
files = Dir.glob("../include/vaucanson/algorithms/*.hh").sort!

# read the directory
files.each { |file|
  empty = true
  File.open(file, "r") { |f|
    contents = f.readlines
    output = Array.new
    empty = true

    output.push("namespace vcsn", "{")
    i = 0
    while i < contents.length
      # `// INTERFACE` has been found
      # process the file declaration
      if contents[i] =~ /\/\/\s*INTERFACE/
	empty = false
	# GenAutomaton is ignored to avoid multiple definitions
	if contents[i] !~ /GenAutomaton/
	  tmp = contents[i].gsub(/^\s*\/\/\s*INTERFACE:\s*(.*)\s+\{.*/, '  \1;')
          if file =~ /eval\.hh/
            tmp = tmp.gsub(/int/, 'Automaton::semiring_elt_t')
          end
	  tmp = tmp.gsub(/Automaton/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t')
	  tmp = tmp.gsub(/HList/, 'std::set<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::hstate_t>')
	  tmp = tmp.gsub(/ExpImpl/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::rat_exp_impl_t')
	  tmp = tmp.gsub(/Exp/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::rat_exp_t')
	  tmp = tmp.gsub(/Series/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::series_set_elt_t')
	  tmp = tmp.gsub(/Word/, 'std::basic_string<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::letter_t>')
	  output.push("  template", tmp)
	end
      end
      i = i.next
    end
    output.push("} // End of namespace vcsn", "")

    vcsn.each { |type, context|
      if create?(type, file) and ! empty
	# file has template to instanciate, write it down!
	# checking if there was any declaration kept from the current header
	write_src(type, context, File.basename(file, ".hh") + ".cc", output)
      end
    }
  }
}

# writing */lib*.mk files which are included in Makefile.am
vcsn.each { |type, context| write_makefile(type, context) }
