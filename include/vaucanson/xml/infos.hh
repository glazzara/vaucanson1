// infos.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_XML_INFOS_HH
# define VCSN_XML_INFOS_HH

/** @addtogroup xml *//** @{ */
/**
 * @file infos.hh
 *
 * Attached XML data for Graphs.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */
/** @} */

# include <string>

# include <vaucanson/automata/concept/automata.hh>

namespace vcsn
{

  namespace xml
  {

    /** @addtogroup xml *//** @{ */

    /// Optionnal fields.
    template <typename I>
    struct Optionnal
    {
    public:
      Optionnal<I>() : set(false) {}

      Optionnal<I>(const I& i) : set(true)
      {
	value = i;
      }

      Optionnal<I>(const Optionnal<I>& o)
      {
	value = o.value;
	set = o.set;
      }

      /// Return reference to the value and tell it is set.
      I& operator()()
      {
	set = true;
	return value;
      }

      const I& operator()() const
      {
	return value;
      }

      bool& is_set() { return set; }
      const bool& is_set() const { return set; }

    private:
      /// Value
      I value;
      /// Is set ?
      bool set;
    };

# include <vaucanson/xml/geometry.inc>

    /// Contains a geometry and a map of geometry.
    template <typename I>
    struct ListGeometry
      : public std::map<I, Optionnal<GeometryValue> >,
        public Optionnal<GeometryValue>
    {
      ListGeometry() : std::map<I, Optionnal<GeometryValue> >(),
		       Optionnal<GeometryValue>()
      { }
    };

    /// Contains a geometry, a map of geometry and a list of name.
    struct StateList
      : public ListGeometry<hstate_t>
    {
    public:
      std::map<hstate_t,
	       std::string>&			get_name()
						{ return name; }
      const std::map<hstate_t,
		     std::string>&		get_name() const
						{ return name; }
      std::map<hstate_t,
	       Optionnal<std::string> >&	get_label()
						{ return label; }
      const std::map<hstate_t,
		     Optionnal<std::string> >&	get_label() const
						{ return label; }

      StateList() : ListGeometry<hstate_t>(), name(), label()
      { }
    private:
      std::map<hstate_t, std::string> name;
      std::map<hstate_t, Optionnal<std::string> > label;
    };

    /// XML Infos for graph's tag.
    struct XmlInfosTag {
      typedef Optionnal<GeometryValue> Geometry;
    public:
      Geometry&				get_structure()
					{ return structure; }
      const Geometry&			get_structure() const
					{ return structure; }
      Geometry&				get_root()
					{ return root; }
      const Geometry&			get_root() const
					{ return root; }
      StateList&			get_states()
					{ return states; }
      const StateList&			get_states() const
					{ return states; }
      ListGeometry<hedge_t>&		get_edges()
					{ return edges; }
      const ListGeometry<hedge_t>&	get_edges() const
					{ return edges; }
      ListGeometry<hstate_t>&		get_initials()
					{ return initials; }
      const ListGeometry<hstate_t>&	get_initials() const
					{ return initials; }
      ListGeometry<hstate_t>&		get_finals()
					{ return finals; }
      const ListGeometry<hstate_t>&	get_finals() const
					{ return finals; }

      XmlInfosTag()
	: structure(), root(), states(), edges(), initials(), finals()
      { }

    private:
      /// Geometry of content.
      Geometry structure;
      /// Geometry of the whole automaton.
      Geometry root;
      /// States geometry.
      StateList states;
      /// Transitions geometry.
      ListGeometry<hedge_t> edges;
      /// Initial states geometry.
      ListGeometry<hstate_t> initials;
      /// Final states geometry.
      ListGeometry<hstate_t> finals;

    };

    /** @} */

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_INFOS_HH
