// predefined_alphabets.hh: this file is part of Vaucanson.
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
#ifndef PREDEFINED_ALPHABETS_HH
# define PREDEFINED_ALPHABETS_HH

/**
 * @file predefined_alphabets.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Predefined alphabets as macros.
 */

# define ALPHABET_ASCII							\
  " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
# define ALPHABET_AZ				\
  "abcdefghijklmnopqrstuvwxyz"
# define ALPHABET_AZAZ						\
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define ALPHABET_AB "ab"

# define DEFAULT_EPSILON "1"

#endif /* !PREDEFINED_ALPHABETS_HH */
