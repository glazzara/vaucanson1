// automata_kind.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_KIND_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_KIND_HH

# include <utility>

namespace vcsn {

  struct labels_are_letters {};
  struct labels_are_words   {};
  struct labels_are_series  {};
  struct labels_are_couples {};

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
  struct LabelOf<labels_are_series, WordValue, WeightValue, 
		 SeriesValue, Letter>
  {
    typedef SeriesValue	ret;
  };

  template <class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter>
  struct LabelOf<labels_are_couples, WordValue, WeightValue, 
		 SeriesValue, Letter>
  {
    typedef std::pair<WeightValue, WordValue>	ret;
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
