// automata_kind.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_KIND_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_KIND_HH

# include <utility>

namespace vcsn {

  // These names are approximate; the comments below give the details.
  struct labels_are_letters {};  // really generators of the monoid
  struct labels_are_atoms   {};  // "letter" or monoid unit
  struct labels_are_words   {};  // really element of the monoid
  struct labels_are_series  {};  // really!

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter>
  struct LabelOf;

  template <class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter>
  struct LabelOf<labels_are_letters, WordValue, WeightValue,
		 SeriesValue, Letter>
  {
    typedef Letter	ret;
  };

  template <class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter>
  struct LabelOf<labels_are_atoms, WordValue, WeightValue,
		 SeriesValue, Letter>
  {
    typedef std::pair<WeightValue, WordValue>	ret;
  };

  template <class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter>
  struct LabelOf<labels_are_series, WordValue, WeightValue,
		 SeriesValue, Letter>
  {
    typedef SeriesValue	ret;
  };

  template <class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter>
  struct LabelOf<labels_are_words, WordValue, WeightValue,
		 SeriesValue, Letter>
  {
    typedef WordValue	ret;
  };

} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_KIND_HH
