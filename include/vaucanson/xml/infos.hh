#ifndef VCSN_XML_INFOS_HH
# define VCSN_XML_INFOS_HH

# include <vaucanson/automata/concept/automata.hh>

# include <string>

namespace vcsn
{
  namespace xml
  {
    template <typename I>
    struct Optionnal
    {
      I value;
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
      I& operator()()
      {
	return value;
      }
    };

# include <vaucanson/xml/geometry.inc>

    template <typename I>
    struct ListGeometry
      : public std::map<I, Optionnal<GeometryValue> >,
        public Optionnal<GeometryValue>
    {
      ListGeometry() : std::map<I, Optionnal<GeometryValue> >(),
		       Optionnal<GeometryValue>()
      { }
    };

    struct StateList
      : public ListGeometry<hstate_t>
    {
      std::map<hstate_t, std::string> name;
      std::map<hstate_t, Optionnal<std::string> > label;

      StateList() : ListGeometry<hstate_t>(), name(), label()
      { }
    };

    struct XmlInfosTag {
      typedef Optionnal<GeometryValue> Geometry;

      Geometry structure;
      Geometry root;
      StateList states;
      ListGeometry<hedge_t> edges;
      ListGeometry<hstate_t> initials;
      ListGeometry<hstate_t> finals;

      XmlInfosTag()
	: structure(), root(), states(), edges(), initials(), finals()
      { }
    };
  }
}

#endif // VCSN_XML_INFOS_HH
