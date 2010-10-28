#! /usr/bin/ruby
# generate_libvcsn.rb: this file is part of the Vaucanson project.
#
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2007, 2008, 2009, 2010 The Vaucanson Group.
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
  "vcsn-int-b" => "int_boolean_automaton",
  "vcsn-r" => "r_automaton",
  "vcsn-z" => "z_automaton",
  "vcsn-int-z" => "int_z_automaton",
  "vcsn-z-max" => "z_max_plus_automaton",
  "vcsn-z-min" => "z_min_plus_automaton",
  "vcsn-fmp-tdc" => "fmp_transducer",
  "vcsn-int-fmp-tdc" => "int_fmp_transducer",
  "vcsn-tdc" => "boolean_transducer",
  "vcsn-z-fmp-tdc" => "z_fmp_transducer",
  "vcsn-int-z-fmp-tdc" => "int_z_fmp_transducer",
  "vcsn-z-tdc" => "z_transducer",
  "vcsn-char-char-b" => "char_char_boolean_automaton",
  "vcsn-char-char-z" => "char_char_z_automaton",
  "vcsn-char-int-b" => "char_int_boolean_automaton",
  "vcsn-int-int-b" => "int_int_boolean_automaton",
  "vcsn-int-int-z" => "int_int_z_automaton",
]

# Creating directories in lib/
vcsn.each_key { |type| system("mkdir -p " + type) }

# testing if a source file needs to be created
def create?(type, file)
  file !~ /krat_exp_cderivation.hh/ and # FIXME: Why is this file omitted?
  (
    ! File.exist?(type + "/" + File.basename(file, ".hh") + ".cc") or
    File.new(file, "r").stat > File.new(type + "/" + File.basename(file, ".hh") + ".cc").stat
  ) and
  (
    # FIXME: The following tests shall be removed
    # FIXME: more comments with the some specs on the algorithms must be added to do so
    ( # Automata filters.
      ( "vcsn-b" == type or "vcsn-r" == type or "vcsn-z" == type or
        "vcsn-int-b" == type or "vcsn-int-z" == type or
	"vcsn-z-max" == type or "vcsn-z-min" == type or
	"vcsn-char-char-b" == type or "vcsn-char-char-z" == type or
	"vcsn-char-int-b" == type or "vcsn-int-int-b" == type or
	"vcsn-int-int-z" == type
      ) and
      file !~ /realtime_decl.hh/ and
      file !~ /extension.hh/ and		# transducer
      file !~ /invert.hh/ and			# transducer
      file !~ /is_normalized.hh/ and		# transducer
      file !~ /normalized_composition.hh/ and	# transducer
      file !~ /rw_composition.hh/ and           # transducer
      file !~ /domain.hh/ and			# transducer
      file !~ /image.hh/ and			# transducer
      file !~ /evaluation_fmp.hh/ and		# FMP transducer
      file !~ /sub_normalize.hh/ and		# FMP transducer
      file !~ /composition_cover.hh/ and	# FMP transducer
      file !~ /\/projection.hh/ and		# FMP transducer (identity)
      file !~ /ltl_to_pair.hh/ and		# FMP transducer
      file !~ /is_ltl.hh/ and			# FMP transducer
      ( # Real Semiring only
	("vcsn-r" == type
	) or
	(
	  file !~ /reduce.hh/
	)
      ) and
      ( # Pair letters only filters.
	not ( "vcsn-char-char-b" == type or
	      "vcsn-char-char-z" == type or
	      "vcsn-char-int-b" == type or
	      "vcsn-int-int-b" == type or
              "vcsn-int-int-z" == type
	    ) or
	    (
	      file !~ /berry_sethi.hh/		# algorithm not generic with letter_t
	    )
      ) and
      ( # Simple letters only filters.
	not ( "vcsn-b" == type or "vcsn-r" == type or "vcsn-z" == type or
	      "vcsn-int-b" == type or "vcsn-int-z" == type or
	      "vcsn-z-max" == type or "vcsn-z-min" == type
	    ) or
	    (
	      file !~ /aut_projection.hh/ and		# Pair letters only
	      file !~ /pair_to_fmp.hh/			# Pair letters only
	    )
      )
    ) or
    ( # Transducers only filters.
      (
	"vcsn-fmp-tdc" == type or "vcsn-tdc" == type or
	"vcsn-z-fmp-tdc" == type or "vcsn-z-tdc" == type or
	"vcsn-int-fmp-tdc" == type or "vcsn-int-z-fmp-tdc" == type
      ) and
      file !~ /aci_canonical.hh/ and
      file !~ /aut_projection.hh/ and
      file !~ /pair_to_fmp.hh/ and
      file !~ /berry_sethi.hh/ and
      file !~ /brzozowski.hh/ and
      file !~ /complement.hh/ and
      file !~ /derived_term_automaton.hh/ and
      file !~ /determinize.hh/ and
      file !~ /equivalent.hh/ and
      file !~ /eval.hh/ and
      file !~ /extension.hh/ and
      file !~ /finite_support_conversion.hh/ and
      file !~ /is_ambiguous.hh/ and
      file !~ /krat_exp.*.hh/ and
      file !~ /letter_to_letter_composition.hh/ and
      file !~ /minimization_hopcroft.hh/ and
      file !~ /minimization_moore.hh/ and
      file !~ /realtime_decl.hh/ and
      file !~ /realtime.hh/ and
      file !~ /reduce.hh/ and
      file !~ /standard_of.hh/ and
      file !~ /shortest.hh/ and
      file !~ /thompson.hh/ and
      ( # FMP transducers only filters.
        not ( "vcsn-fmp-tdc" == type or "vcsn-z-fmp-tdc" == type or
	      "vcsn-int-fmp-tdc" == type or "vcsn-int-z-fmp-tdc" == type
	    ) or
	    (
	      file !~ /complete.hh/ and
	      file !~ /is_deterministic.hh/ and
              file !~ /rw_composition.hh/ and
	      file !~ /product.hh/
	    )
      ) and
      ( # RW transducers only filters.
        not ( "vcsn-tdc" == type or "vcsn-z-tdc" == type
	    ) or
	    (
	      file !~ /normalized_composition.hh/ and	# FMP transducer
	      file !~ /evaluation_fmp.hh/ and		# FMP transducer
	      file !~ /sub_normalize.hh/ and		# FMP transducer
	      file !~ /ltl_to_pair.hh/ and		# FMP transducer
	      file !~ /is_ltl.hh/ and			# FMP transducer
	      file !~ /\/projection.hh/ and		# FMP transducer (identity)
	      file !~ /composition_cover.hh/		# FMP transducer
	    )
      )
    )
  )
end


# write a all.cc, including all other *.cc files.
def write_all_cc(type,files)
  puts "Generating " + type + "/all.cc"
  l=type.length
  File.open(type + "/all.cc", "w") { |out|
    out.puts("// " + type + "/all.cc: this file is part of the Vaucanson project.",
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
	     "")
    files.each { |file| out.puts('#include "' + file[l+1..-1] + '"') }
  }
end


# write a *.mk for `type`
def write_makefile(type, context)
  type_ = type.gsub(/-/, "_")
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
	     "lib" + type_ + "_la_CXXFLAGS\t= $(CXXFLAGS) -DVCSN_CONTEXT=" + context,
	     "lib" + type_ + "_la_LIBADD\t= $(LIBOBJS) $(LIBADD) $(benchlib)",
             "lib" + type_ + "_la_SOURCES\t= " + type + "/all.cc",
	     "## all.cc includes all the source files below.  We declare them",
	     "## as EXTRA_*_SOURCES so they are distributed and so we can",
	     "## build a single object file on demand.")
    out.print "EXTRA_lib" + type_ + "_la_SOURCES = "
    files = Dir.glob(type + "/*.cc").sort!
    files.reject! { |filename| filename == type + "/all.cc" }
    real_files = Array.new
    files.each { |filename|
      if File.exist?("../include/vaucanson/algorithms/" + File.basename(filename, ".cc") + ".hh")
	out.print "\\\n  ", filename, "\t"
	real_files.push(filename)
      else
	File.unlink(filename)
	puts "Removing " + filename
      end
    }
    out.print "\n\n"
    out.puts("MAINTAINERCLEANFILES += $(lib" + type_ + "_la_SOURCES) " +
             "$(EXTRA_lib" + type_ + "_la_SOURCES) " +
	     type + "/lib" + type + ".mk")
    write_all_cc(type, real_files)
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
	tmp = contents[i].gsub(/^\s*\/\/\s*INTERFACE:\s*(.*)\s+\{.*/, '  \1;')
	tmp = tmp.gsub(/GenAutomaton/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::gen_automaton_t')
	tmp = tmp.gsub(/Automaton/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t')
	tmp = tmp.gsub(/HList/, 'std::set<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::hstate_t>')
	tmp = tmp.gsub(/ExpImpl/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::rat_exp_impl_t')
	tmp = tmp.gsub(/LinExp/, 'linearize_element<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::rat_exp_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::rat_exp_t::value_t>::element_t')
	tmp = tmp.gsub(/Exp/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::rat_exp_t')
	tmp = tmp.gsub(/Series/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::series_set_elt_t')
	tmp = tmp.gsub(/Letter/, 'VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::letter_t')
	tmp = tmp.gsub(/Word/, 'std::basic_string<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::letter_t>')
	tmp = tmp.gsub(/InputProjection/, 'input_projection_helper<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::value_t>::ret')
	tmp = tmp.gsub(/OutputProjection/, 'output_projection_helper<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::value_t>::ret')
	tmp = tmp.gsub(/FirstProjection/, 'projection_traits<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::value_t>::first_projection_t')
	tmp = tmp.gsub(/SecondProjection/, 'projection_traits<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::value_t>::second_projection_t')
	tmp = tmp.gsub(/LtlToPair/, 'mute_ltl_to_pair<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::value_t>::ret')
	tmp = tmp.gsub(/PairToFMP/, 'mute_pair_to_fmp<VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::set_t, VCSN_DEFAULT_GRAPH_IMPL::VCSN_CONTEXT::automaton_t::value_t>::ret')
	output.push("  template", tmp)
      end
      i = i.next
    end
    output.push("} // End of namespace vcsn", "")

    vcsn.each { |type, context|
      if create?(type, file) and ! empty
	# file has template to instantiate, write it down!
	# checking if there was any declaration kept from the current header
	write_src(type, context, File.basename(file, ".hh") + ".cc", output)
      end
    }
  }
}

# writing */lib*.mk files which are included in Makefile.am
vcsn.each { |type, context| write_makefile(type, context) }
