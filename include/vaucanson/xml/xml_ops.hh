// xml_ops.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_OPS_HH
# define VCSN_XML_XML_OPS_HH

# include <vaucanson/xml/xml_set.hh>
# include <vaucanson/xml/xml_automaton.hh>

namespace vcsn
{

  namespace xml
  {
    /*--------------.
    | I/O Functions |
    `--------------*/

    template <class Ostream>
    Ostream&
    op_rout(const XmlStructure& xs, Ostream& os, const XmlAutomaton& xv);

    template <class Istream>
    Istream&
    op_rin(XmlStructure& s, Istream& is, XmlAutomaton& v);

    /*----------------------.
    | Structure conversions |
    `----------------------*/

    template <class Auto>
    XmlStructure
    op_convert(const XmlStructure&, const AutomataBase<Auto>& s);

    template <class Auto>
    Auto
    op_convert(const AutomataBase<Auto>&, const XmlStructure& s);

    /*------------------.
    | Value conversions |
    `------------------*/

    template <class S, class T>
    XmlAutomaton
    op_convert(const XmlStructure&	xs,	const XmlAutomaton&	,
	       const AutomataBase<S>&	s,	const T&		v);

    template <class S, class T>
    T
    op_convert(const AutomataBase<S>&	s,	const T&		,
	       const XmlStructure&	xs,	const XmlAutomaton&	xv);
    /*-----------.
    | Assignment |
    `-----------*/

    template <typename S>
    void
    op_assign(AutomataBase<S>&		lhs,
	      const XmlStructure&	rhs);

    template <typename S, typename T>
    void
    op_assign(const AutomataBase<S>&	lhs_s,
	      const XmlStructure&	rhs_s,
	      T&			lhs_v,
	      const XmlAutomaton&	rhs_v);

    /*---------------------.
    | Conversion of series |
    `---------------------*/

    template <typename S, typename T>
    T
    op_convert(const algebra::SeriesBase<S>& s,
	       const T&,
	       const xml_value_t& v);

    // FIXME: Since op_convert with three arguments should take the structure
    // FIXME: and the value of a series as the two first arguments, that
    // FIXME: prototype does not follow the usual semantic: xml_value_t is
    // FIXME: never considered as an implementation of series.
    template<typename S, typename T>
    xml_value_t
    op_convert(const algebra::SeriesBase<S>& s,
	       SELECTOR(xml_value_t),
	       const T& p);


  } // End of namespace xml.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_ops.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_OPS_HH
