// element.hxx: this file is part of the Vaucanson project.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_DESIGN_PATTERN_ELEMENT_HXX
# define VCSN_DESIGN_PATTERN_ELEMENT_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/design_pattern/element.hh>

namespace vcsn {

  /*-------------.
  | Constructors |
  `-------------*/

  template <class S, class T>
  Element<S,T>::Element() :
    MetaElement<S, T>(),
    structure_(),
    value_(op_default(SELECT(S), SELECT(T)))
  {
//FIXME: Find another way to have empty elements.
#ifndef VCSN_XML_EMPTY_ELEMENTS
    static_assertion_(not dynamic_traits<S>::ret, need_dynamic_structural_element);
#endif //VCSN_XML_EMPTY_ELEMENTS
  }

  /*--------------------------.
  | Constructors from Element |
  `--------------------------*/

  template <class S, class T>
  Element<S,T>::Element(const Element& other) :
    MetaElement<S, T>(other),
    structure_(other.structure_),
    value_(other.value_)
  {}

  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const Element<S, U>& other) :
    structure_(other.structure()),
    value_(op_convert(other.structure(), SELECT(T), other.value()))
  {}

  template <bool Cond, typename S, typename T>
  struct convert_dynamic
  {
     static S convert(const SetSlot<S>& structure_, const T& t)
     {
	if (!structure_.bound())
          return op_convert(SELECT(S), t);
	else
          return structure_.get();
     }
  };

  template <typename S, typename T>
  struct convert_dynamic<false, S, T>
  {
     static S convert(const SetSlot<S>&, const T&)
     {
       return S();
     }
  };
  
  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>::Element(const Element<OtherS, U>& other)
    : value_(op_convert(SELECT(S), SELECT(T), 
			other.structure(), other.value()))
  {
    structure_.assign(convert_dynamic<dynamic_traits<S>::ret, S, OtherS>
		    ::convert(structure_, other.structure()));
    //static_assertion_(not dynamic_traits<S>::ret, need_dynamic_structural_element);
  }

  /*-------------------------.
  | Constructors from values |
  `-------------------------*/

  template <class S, class T>
  Element<S,T>::Element(const T& other)
    : structure_(),
      value_(op_convert(SELECT(S), SELECT(T), other))
  {
    static_assertion_(not dynamic_traits<S>::ret, need_dynamic_structural_element);
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const U& other)
    : structure_(),
      value_(op_convert(SELECT(S), SELECT(T), other))
  {
    static_assertion_(not dynamic_traits<S>::ret, need_dynamic_structural_element);
  }

  /*--------------------------------------.
  | Constructors from structural elements |
  `--------------------------------------*/

  template <class S, class T>
  Element<S,T>::Element(const S& structure)
    : structure_(structure),
      value_(op_default(structure_.get(), SELECT(T)))
  {}

  template <class S, class T>
  Element<S,T>::Element(const S& structure, const T& other)
    : structure_(structure),
      value_(op_convert(structure_.get(), SELECT(T), other))
  {}
  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const S& structure, const U& other)
    : structure_(structure),
      value_(op_convert(structure_.get(), SELECT(T), other))
  {}

  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>::Element(const S& structure, const Element<OtherS, U>& other)
    : structure_(structure),
      value_(op_convert(structure_.get(), SELECT(T),
		        other.structure(), other.value()))
  {}

  /*-----------.
  | Assignment |
  `-----------*/

  template <class S, class T>
  Element<S,T>&
  Element<S,T>::operator=(const Element& other)
  {
    if (!structure_.bound())
      structure_.assign(other.structure());
    op_assign(structure(), other.structure(), value_, other.value());
    return *this;
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>&
  Element<S,T>::operator=(const Element<S, U>& other)
  {
    if (!structure_.bound())
      structure_.assign(other.structure());
    op_assign(structure(), other.structure(), value_, other.value());
    return *this;
  }

  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>& Element<S,T>::operator=(const Element<OtherS, U>& other)
  {
    structure_.assign(convert_dynamic<dynamic_traits<S>::ret, S, OtherS>
	    	::convert(structure_, other.structure()));
    op_assign(structure(), other.structure(), value_, other.value());
    return *this;
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>& Element<S,T>::operator=(const U& other)
  {
    op_assign(structure(), value(), other);
    return *this;
  }

  /*------.
  | Sugar |
  `------*/

  template <class S, class T>
  void
  Element<S,T>::attach(const S& structure)
  {
    structure_.attach(structure);
  }

  template <class S, class T>
  const S&
  Element<S,T>::structure() const
  {
    return structure_.get();
  }

  template <class S, class T>
  T&	Element<S,T>::value()
  {
    return value_;
  }

  template <class S, class T>
  const T&	Element<S,T>::value() const
  {
    return value_;
  }

} // vcsn


#endif // ! VCSN_DESIGN_PATTERN_ELEMENT_HXX
