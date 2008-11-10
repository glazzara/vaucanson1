// common.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

#ifndef COMMON_HH
# define COMMON_HH

/**
 * @file common.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *         Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * This file contains common declarations for all files.
 */

# ifdef HAVE_CONFIG_H
#  include <config.h>
# endif

# include <vaucanson/config/system.hh>

# include <iostream>

# define echo(S) std::cout << S << std::endl
# define echo_(S) std::cout << S
# define warn(S) std::cerr << S << std::endl
# define warn_(S) std::cerr << S

# ifndef CONTEXT
#  error "CONTEXT has to be declared."
# endif

# define CONTEXT_HEADER    <vaucanson/CONTEXT.hh>
# define CONTEXT_NAMESPACE vcsn::CONTEXT

# if 0 /* @bug Should use this with dynamic libraries. */
#  define VCSN_USE_INTERFACE_ONLY 1
# endif /* 0 */

/* Turn VCSN traps into exception. */
# define EXCEPTION_TRAPS 1

# include <string>

// Use a global timer and bencher.
# define GLOBAL_TIMER global_timer
# define GLOBAL_BENCHER bencher
# include <vaucanson/misc/usual_macros.hh>
extern vcsn::misc::Timer global_timer;
extern vcsn::misc::Bencher bencher;

// Use a global command result.
# include "pipe.hh"
# define GLOBAL_RESULT last_command_output
extern command_output last_command_output;

struct arguments_t
{
    arguments_t (const std::string& name)
      : progname (name),
	n_args (0),
	alphabet (0),
# ifdef WITH_TWO_ALPHABETS
	alphabet2 (0),
# endif // ! WITH_TWO_ALPHABETS
	verbose (false),
	bench (false),
	nb_iterations (1),
	report_time (false),
	export_time_dot (false),
	export_time_xml (false),
	input_type (INPUT_TYPE_XML),
	output_aut_type (OUTPUT_TYPE_XML),
	output_exp_type (OUTPUT_TYPE_EXP)
    {}

    std::string	progname;
    const char*	args[3];
    int		n_args;

    // String to parse to retrieve representations informations.
    std::string parser;

    // Alphabet.
    std::vector<std::string> alphabet;

    // Representation of Monoid<Alphabet>.
    monoid_rep_t mrep;
    // Representation of Series<Semiring, Monoid>.
    series_rep_t srep;

# ifdef WITH_TWO_ALPHABETS
    // Representation of Series<Semiring, FirstMonoid>
    IOAUT_CONTEXT::series_rep_t srep1;
    // Representation of Series<Semiring, SecondMonoid>
    IOAUT_CONTEXT::series_rep_t srep2;
    // Representation of FirstMonoid.
    first_monoid_rep_t mrep1;
    // Representation of SecondMonoid.
    second_monoid_rep_t mrep2;

    std::vector<std::string> alphabet2;
    std::string parser2;
# endif // ! WITH_TWO_ALPHABETS

    bool	verbose;
    bool	bench;
    unsigned	nb_iterations;
    std::string plot_output_filename;
    bool        report_time;
    int         report_degree;

    bool        export_time_dot;
    int         export_dot_degree;

    bool        export_time_xml;

    input_format_t	input_type;
    output_format_t	output_aut_type;
    output_format_t	output_exp_type;

# define ADD_OPTION(x) \
      if (x != "") \
        x += " "; \
      if (type) \
        x += std::string(type) + "="; \
      x += str;

    void add_parser_option(const char* type, const char* str)
    {
      ADD_OPTION(parser)
    }
# ifdef WITH_TWO_ALPHABETS
    void add_parser2_option(const char* type, const char* str)
    {
      ADD_OPTION(parser2)
    }
# endif // ! WITH_TWO_ALPHABETS

# undef ADD_OPTION
};

# define IMPORT_DEFAULT(name) \
extern const std::string default_##name ();

IMPORT_DEFAULT(open_par)
IMPORT_DEFAULT(close_par)
IMPORT_DEFAULT(plus)
IMPORT_DEFAULT(times)
IMPORT_DEFAULT(star)
IMPORT_DEFAULT(epsilon)
IMPORT_DEFAULT(zero)
IMPORT_DEFAULT(open_weight)
IMPORT_DEFAULT(close_weight)
IMPORT_DEFAULT(space)

# undef IMPORT_DEFAULT

#endif // ! COMMON_HH
