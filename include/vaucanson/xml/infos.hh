#ifndef VCSN_XML_INFOS_HH
# define VCSN_XML_INFOS_HH

# include <vaucanson/automata/concept/automata.hh>

# include <string>

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file infos.hh
 * @brief Attached XML data for Graphs.
 * @author Valentin David <valentin@lrde.epita.fr>
 */

namespace vcsn
{
  namespace xml
  {
    /// Optionnal fields.
    template <typename I>
    struct Optionnal
    {
      /// Value
      I value;
      /// Is set ?
      bool set;
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
      std::map<hstate_t, std::string> name;
      std::map<hstate_t, Optionnal<std::string> > label;

      StateList() : ListGeometry<hstate_t>(), name(), label()
      { }
    };

    /// XML Infos for graph's tag.
    struct XmlInfosTag {
      typedef Optionnal<GeometryValue> Geometry;

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

      XmlInfosTag()
	: structure(), root(), states(), edges(), initials(), finals()
      { }
    };
  }
}

/** @} */

#endif // VCSN_XML_INFOS_HH
