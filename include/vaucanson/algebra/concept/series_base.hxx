// series_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_SERIES_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_SERIES_BASE_HXX

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
    | SeriesBase<Self> |
    `-----------------*/

    template<class Self>
    const typename SeriesBase<Self>::monoid_t&
    SeriesBase<Self>::monoid() const
    {
      return this->self().monoid();
    }

    template<class Self>
    const typename SeriesBase<Self>::semiring_t&
    SeriesBase<Self>::semiring() const
    {
      return this->self().semiring();
    }

    template<class Self>
    typename SeriesBase<Self>::monoid_t&
    SeriesBase<Self>::monoid()
    {
      return this->self().monoid();
    }

    template<class Self>
    typename SeriesBase<Self>::semiring_t&
    SeriesBase<Self>::semiring()
    {
      return this->self().semiring();
    }

    template<class Self>
    SeriesBase<Self>::SeriesBase()
    {}

    template<class Self>
    SeriesBase<Self>::SeriesBase(const SeriesBase& other) :
      SemiringBase<Self>(other)
    {}

  } // algebra


    /*---------------------------------.
    | MetaElement<SeriesBase<Self>, T> |
    `---------------------------------*/

  template<typename S, typename T>
  typename MetaElement<algebra::SeriesBase<S>, T>::semiring_elt_value_t
  MetaElement<algebra::SeriesBase<S>, T>::get(const monoid_value_t& m) const
  {
    // assertion(set().monoid().contains(m));
    return op_series_get(this->set(), this->value(), m);
  }

  template<typename S, typename T>
  typename MetaElement<algebra::SeriesBase<S>, T>::semiring_elt_t
  MetaElement<algebra::SeriesBase<S>, T>::get(const monoid_elt_t& m) const
  {
    return semiring_elt_t(this->set().semiring(), get(m.value()));
  }

  template<typename S, typename T>
  void
  MetaElement<algebra::SeriesBase<S>, T>::assoc(const monoid_value_t& m,
						const semiring_elt_value_t& w)
  {
    // assertion(set().monoid().contains(m));
    // assertion(set().semiring().contains(w));
    return op_series_set(this->set(), this->value(), m, w);
  }

  template<typename S, typename T>
  void
  MetaElement<algebra::SeriesBase<S>, T>::assoc(const monoid_elt_t& m,
						const semiring_elt_t& w)
  {
    assoc(m.value(), w.value());
  }

  template<typename S, typename T>
  bool
  MetaElement<algebra::SeriesBase<S>, T>::is_finite_app() const
  {
    return op_is_finite_app(this->set(), this->value());
  }

  template <typename S, typename T>
  typename MetaElement<algebra::SeriesBase<S>, T>::monoid_elt_t
  MetaElement<algebra::SeriesBase<S>, T>::choose_from_supp() const
  {
    return
      typename MetaElement<algebra::SeriesBase<S>, T>::monoid_elt_t
      (this->set().monoid(), op_choose_from_supp(this->set(), this->value()));
  }

  template <typename S, typename T>
  void
  MetaElement<algebra::SeriesBase<S>, T>::transpose()
  {
    op_in_transpose(this->set(), this->value());
  }

  template <typename S, typename T>
  typename MetaElement<algebra::SeriesBase<S>, T>::support_t
  MetaElement<algebra::SeriesBase<S>, T>::supp() const
  {
    return op_support(this->set(), this->value());
  }

  template<typename S, typename T>
  MetaElement<algebra::SeriesBase<S>, T>::MetaElement()
  {}

  template<typename S, typename T>
  MetaElement<algebra::SeriesBase<S>, T>::MetaElement(const MetaElement& other) :
    MetaElement<algebra::SemiringBase<S>, T>(other)
  {}

  template<typename S, typename T>
  bool op_is_finite_app(const algebra::SeriesBase<S>& s, const T& t)
  {
    return false;
  }

  template<typename S, typename T, typename M, typename W>
  void op_series_set(const algebra::SeriesBase<S>& s, const T& t, const W& w)
  {
    assertion(! "defined.");
  }

  template <class S, class T>
  Element<S, T> op_series_choose(const algebra::SeriesBase<S>& s, SELECTOR(T))
  {
    assertion(! "defined.");
    return Element<S, T>();
  }

  template <class S, class T>
  typename algebra::series_traits<T>::support_t
  op_support(const algebra::SeriesBase<S>&, const T& v)
  {
    return v;
  }

  template <class S, class T>
  Element<S, T>
  transpose(const algebra::SeriesBase<S>& s, const T& t)
  {
    T	new_t(t);
    new_t.transpose();
    return new_t;
  }

  template <class S, class T>
  bool
  is_letter_support(const Element<S, T>& s)
  {
    typedef typename algebra::series_traits<T>::support_t support_t;
    support_t supp = s.supp();
    for_each_const_(support_t, e, supp)
      if (op_size(s.set().monoid(), *e) != 1)
	return false;
    return true;
  }

  template <typename S1, typename S2, typename T1, typename T2>
  void
  extract_support(Element<S1, T1>& s1, Element<S2, T2>& s2)
  {
    typedef typename algebra::series_traits<T2>::support_t support_t;
    typedef typename algebra::series_traits<T1>::semiring_elt_value_t semiring_elt_value_t;
    for_each_const_(support_t, e, s2.supp())
      s1.assoc(*e, algebra::identity_as<semiring_elt_value_t>::of(s1.set().semiring()));
  }

  template <class S, class T>
  Element<S, T> hadamard(const Element<S, T>& lhs,
			 const Element<S, T>& rhs)
  {
    typedef Element<S, T> series_elt_t;
    typedef typename Element<S, T>::monoid_elt_t monoid_elt_t;
    typedef typename Element<S, T>::semiring_elt_t semiring_elt_t;
    typedef typename Element<S, T>::support_t support_t;
    Element<S, T> output;
    support_t support = lhs.supp();
    for (typename support_t::iterator supp = support.begin();
	 supp != support.end();
	 ++supp)
      {
 	output +=  lhs.get(*supp) *
 	  rhs.get(*supp) * series_elt_t(lhs.set(), monoid_elt_t(*supp));
      }
    return output;
  }

  template <class S, class M>
  S
  op_convert(const algebra::SeriesBase<S>&,
	     const algebra::FreeMonoidBase<M>& monoid)
  {
    // Ensures the monoid is compatible with the series.
    enum { compatible = utility::static_eq<typename S::monoid_t, M>::value };
    static_assertion_(compatible, invalid_conversion_from_monoid_to_series);

    typename S::semiring_t semiring;
    return S (semiring, monoid.self());
  }

  template <class S, class T>
  T op_convert(const algebra::SeriesBase<S>&, SELECTOR(T), const T& src_)
  {
    return src_;
  }

  template <class S, class T, class U>
  T op_convert(const algebra::SeriesBase<S>& s, SELECTOR(T), const U& src_)
  {
    typedef typename algebra::series_traits<U>::support_t	support_t;
    typedef typename Element<S, T>::monoid_elt_t		monoid_elt_t;
    S ts = s.self();
    Element<S, U> src(ts, src_);
    Element<S, T> dst(ts);
    support_t support = src.supp();
    for_each_const_(support_t, ss, support)
      dst += src.get(monoid_elt_t(s.monoid(), *ss)) *
      Element<S, T>(s.self(), monoid_elt_t(s.monoid(), *ss));
    return dst.value();
  }

} // vcsn

#endif // VCSN_ALGEBRA_CONCEPT_SERIES_BASE_HXX
