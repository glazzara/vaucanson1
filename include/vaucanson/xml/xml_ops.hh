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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_XML_XML_OPS_HH
# define VCSN_XML_XML_OPS_HH

# include <vaucanson/xml/xml_automaton.hh>
# include <vaucanson/xml/xml_set.hh>

namespace vcsn
{
  xml::XmlAutomaton
  op_default(SELECTOR(xml::XmlStructure), SELECTOR(xml::XmlAutomaton));

  template <class S>
  void op_assign(const AutomataBase<S>&,
		 const xml::XmlStructure&,
		 xml::XmlAutomaton&,
		 const xml::XmlAutomaton&);

  void op_assign(const xml::XmlStructure&,
  		 const xml::XmlStructure&,
		 xml::XmlAutomaton&,
		 const xml::XmlAutomaton&);

  xml::XmlAutomaton
  op_convert(const xml::XmlStructure&,
	     const xml::XmlAutomaton&,
	     const xml::XmlAutomaton&);

  namespace xml {
    xercesc::DOMDocument* loaddocument(xercesc::DOMBuilder*, std::istream&);
  }

  template<typename S, typename St>
  St& op_rout(const AutomataBase<S>&, St&, const xml::XmlAutomaton&);
  template<typename St>

  St& op_rin(xml::XmlStructure&, St&, xml::XmlAutomaton&);
  template<typename S, typename St>
  St& op_rin(const AutomataBase<S>&, St&, xml::XmlAutomaton&);

  template <typename Tm, typename Tw, typename S>
  algebra::polynom<Tm,Tw> op_convert(const algebra::SeriesBase<S>&,
				     SELECTOR2(algebra::polynom<Tm, Tw>),
				     const xml::XmlValue&);

  template <typename Tm, typename Tw, typename S>
  rat::exp<Tw,Tm> op_convert(const algebra::SeriesBase<S>&,
			     SELECTOR2(rat::exp<Tw, Tm>),
			     const xml::XmlValue&);

  template <typename Tm, typename Tw, typename S>
  xml::XmlValue op_convert(const algebra::SeriesBase<S>&,
			   SELECTOR(xml::XmlValue),
			   const algebra::polynom<Tm, Tw>&);

  template <typename Tm, typename Tw, typename S>
  xml::XmlValue op_convert(const algebra::SeriesBase<S>&,
			   SELECTOR(xml::XmlValue),
			   const rat::exp<Tm, Tw>&);


  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  xml::XmlAutomaton op_convert(SELECTOR2(Automata<algebra::Series<W, M> >),
			       SELECTOR(xml::XmlAutomaton),
			       const Graph<Kind,
			       WordValue,
			       WeightValue,
			       SerieValue,
			       Letter,
			       Tag>&);

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  Graph<Kind, WordValue, WeightValue, SerieValue, Letter, Tag>
  op_convert(SELECTOR2(Automata<algebra::Series<W, M> >),
	     const Graph<Kind,
	     WordValue,
	     WeightValue,
	     SerieValue,
	     Letter,
	     Tag>&,
	     const xml::XmlAutomaton&);

  template <typename Tm, typename Tw, typename W, typename M>
  void op_assign(SELECTOR2(algebra::Series<W, M>),
		 algebra::polynom<Tm, Tw>&,
		 const xml::XmlValue&);

  template <typename Tm, typename Tw, typename W, typename M>
  void op_assign(SELECTOR2(algebra::Series<W, M>),
		 rat::exp<Tm, Tw>&,
		 const xml::XmlValue&);

  template <typename Tm, typename Tw, typename W, typename M>
  void op_assign(const algebra::Series<W, M>& s,
		 xml::XmlValue&,
		 const rat::exp<Tm, Tw>&);

  template <typename Tm, typename Tw, typename W, typename M>
  void op_assign(const algebra::Series<W, M>& s,
		 xml::XmlValue&,
		 const algebra::polynom<Tm, Tw>&);

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  void
  op_assign(SELECTOR2(Automata<algebra::Series<W, M> >),
	    Graph<Kind,
	    WordValue,
	    WeightValue,
	    SerieValue,
	    Letter,
	    Tag>& dst,
	    const xml::XmlAutomaton&);

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  void
  op_assign(SELECTOR2(Automata<algebra::Series<W, M> >),
	    xml::XmlAutomaton&,
	    const Graph<Kind,
	    WordValue,
	    WeightValue,
	    SerieValue,
	    Letter,
	    Tag>&);

}

# include <vaucanson/xml/xml_ops.hxx>

#endif // VCSN_XML_XML_OPS_HH
