// common.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007 The Vaucanson Group.
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

// Use a global timer.
# define GLOBAL_TIMER timer
# include <vaucanson/misc/timer.hh>
extern vcsn::misc::Timer timer;
# include <vaucanson/misc/usual_macros.hh>

struct arguments_t
{
    arguments_t (std::string name)
      : progname (name),
	n_args (0),
	alphabet (0),
	epsilon (0),
# ifdef WITH_TWO_ALPHABETS
	alphabet2 (0),
	epsilon2 (0),
# endif /* ! WITH_TWO_ALPHABETS */
	verbose (false),
	report_time (false),
	bench (false)
    {}

    std::string	progname;
    char*	args[3];
    int		n_args;
    char*	alphabet;
    char	epsilon;
# ifdef WITH_TWO_ALPHABETS
    char*	alphabet2;
    char	epsilon2;
# endif /* ! WITH_TWO_ALPHABETS */
    bool	verbose;
    bool	report_time;
    bool	bench;
    unsigned	nb_iteration;
    std::string plot_output_filename;
};

#endif /* !COMMON_HH */
