// predefined_alphabets.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009 The Vaucanson Group.
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

#ifndef PREDEFINED_ALPHABETS_HH
# define PREDEFINED_ALPHABETS_HH

/**
 * @file predefined_alphabets.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *         Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * Predefined alphabets as macros.
 */

# include "parser_options.hh"

// FIXME: " and \0 (\\0)
# define ALPHABET_ASCII							\
  "\\ \"!#$%&'\\(\\)*+\\,-./0123456789\\:;<\\=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
# define ALPHABET_AZ				\
  "abcdefghijklmnopqrstuvwxyz"
# define ALPHABET_AZAZ						\
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define ALPHABET_DIGITS "0123456789"

void build_predefined_string(char* buffer);

# include "predefined_alphabets.hxx"

#endif /* !PREDEFINED_ALPHABETS_HH */
