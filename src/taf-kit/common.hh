// common.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

# include <iostream>

# define echo(S) std::cout << S << std::endl
# define echo_(S) std::cout << S
# define warn(S) std::cerr << S << std::endl
# define warn_(S) std::cerr << S

# if ! (defined (CONTEXT_HEADER) && defined (CONTEXT_NAMESPACE))
#  error "CONTEXT_HEADER and CONTEXT_NAMESPACE has to be declared."
# endif /* defined (CONTEXT_HEADER) && defined (CONTEXT_NAMESPACE) */

# if 0 /* @bug Should use this with dynamic libraries. */
#  define VCSN_USE_INTERFACE_ONLY 1
# endif /* 0 */

/* Turn VCSN traps into exception. */
# define EXCEPTION_TRAPS 1

# include <string>

struct arguments_t
{
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
};

#endif /* !COMMON_HH */
