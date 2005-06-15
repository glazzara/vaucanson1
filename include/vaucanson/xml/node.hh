// node.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_XML_NODE_HH
# define VCSN_XML_NODE_HH

/**
 * @file node.hh
 *
 * Node class for Factory Method, used in xml::xml_converter::save()
 *
 *
 * @see xml::xml_converter, vcsn::Factory
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */
# include <string>
# include <map>
# include <xercesc/dom/DOM.hpp>
# include <vaucanson/design_pattern/factory.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/xml/xml_chooser.hh>
# include <vaucanson/xml/tools.hh>


namespace vcsn
{
  namespace xml
  {

    /**
     * Node class interface.
     *
     * @param T	Type of the automaton.
     *
     */
    template <class T>
    struct Node
    {
      typedef Factory<Node<T>, std::string> factory_t;
      typedef std::map<std::string, hstate_t> map_t;
      virtual void process(xercesc::DOMElement*, T&, map_t&, factory_t&) = 0;
    };


# define CREATE_CLASSNODE(name)					\
    template <class T>						\
    struct name ## Node : Node<T>				\
    {								\
      void process(xercesc::DOMElement*, T&,			\
		   typename Node<T>::map_t&,			\
		   typename Node<T>::factory_t&);		\
      static Node<T>* create() { return new name ## Node; }	\
    };

# define CREATE_PARAM_CLASSNODE(name)				\
    template <class T>						\
    struct name ## Node : Node<T>				\
    {								\
      void process(xercesc::DOMElement*, T&,			\
		   typename Node<T>::map_t&,			\
		   typename Node<T>::factory_t&) {};		\
								\
      template <class U>					\
      void process(xercesc::DOMElement*, T&, U &,		\
		   typename Node<T>::map_t&,			\
		   typename Node<T>::factory_t&);		\
      static Node<T>* create() { return new name ## Node; }	\
    };


CREATE_CLASSNODE(automaton)
CREATE_CLASSNODE(transducer)
CREATE_CLASSNODE(type)
CREATE_CLASSNODE(content)
CREATE_CLASSNODE(states)
CREATE_CLASSNODE(transitions)
CREATE_CLASSNODE(state)
CREATE_CLASSNODE(transition)
CREATE_CLASSNODE(initial)
CREATE_CLASSNODE(final)
CREATE_PARAM_CLASSNODE(semiring)
CREATE_PARAM_CLASSNODE(monoid)
CREATE_PARAM_CLASSNODE(freemonoid)
CREATE_PARAM_CLASSNODE(generator)


# define TParm					\
    template <class S, class T>
# define TParmFMP					\
      template <class S, class T, class M1, class M2>
# define AUTtype				\
    Element<Automata<S>, T>
# define TRANStype				\
    Element<Transducer<S>, T>

# define FMPtype      							  \
    Element<								  \
      Automata<								  \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
      >, T								  \
    >

# define CREATE_SPEC_TYPE_NODE(TempParam, Type)			\
    TempParam							\
    struct typeNode<Type> : Node<Type>				\
    {								\
      void process(xercesc::DOMElement*, Type&,			\
		   typename Node<Type>::map_t&,			\
		   typename Node<Type>::factory_t&);		\
      static Node<Type>* create() { return new typeNode; }	\
    };


# define CREATE_SPEC_PARAM_NODE(name, TempParam, Type)		\
    TempParam							\
    struct name ## Node<Type> : Node<Type>			\
    {								\
      void process(xercesc::DOMElement*, Type&,			\
		   typename Node<Type>::map_t&,			\
		   typename Node<Type>::factory_t&) {};		\
      template <class U>					\
      void process(xercesc::DOMElement*, Type&, U &,		\
		   typename Node<Type>::map_t&,			\
		   typename Node<Type>::factory_t&);		\
      static Node<Type>* create() { return new name ## Node; }	\
    };


CREATE_SPEC_TYPE_NODE(TParm, AUTtype)
CREATE_SPEC_TYPE_NODE(TParm, TRANStype)
CREATE_SPEC_TYPE_NODE(TParmFMP, FMPtype)
CREATE_SPEC_PARAM_NODE(semiring, TParm, TRANStype)
CREATE_SPEC_PARAM_NODE(monoid, TParmFMP, FMPtype)

	} // ! xml

} // !vcsn


// Macros used to declare the factory. It cannot be done using a
// static attribute since the class is templated.
# define register_in_factory(f, T, name)				\
    factory_reg(f, std::string(#name), name ## Node<T>::create);

# define register_all_factory(f, T)			\
    register_in_factory(f, T, automaton)		\
    register_in_factory(f, T, transducer)		\
    register_in_factory(f, T, type)			\
    register_in_factory(f, T, semiring)			\
    register_in_factory(f, T, monoid)			\
    register_in_factory(f, T, freemonoid)		\
    register_in_factory(f, T, generator)		\
    register_in_factory(f, T, content)			\
    register_in_factory(f, T, states)			\
    register_in_factory(f, T, transitions)		\
    register_in_factory(f, T, state)			\
    register_in_factory(f, T, transition)		\
    register_in_factory(f, T, initial)			\
    register_in_factory(f, T, final)


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/node.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_XML_NODE_HH
