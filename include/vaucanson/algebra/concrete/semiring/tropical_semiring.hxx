// tropical_semiring.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SEMIRING_TROPICAL_SEMIRING_HXX
# define VCSN_ALGEBRA_CONCRETE_SEMIRING_TROPICAL_SEMIRING_HXX
# include <vaucanson/config/system.hh>
# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>

namespace vcsn {

    /*---------------.
    | Identity value |
    `---------------*/
    template<class TropicalKind, typename T> 
    inline
    T identity_value(SELECTOR(algebra::TropicalSemiring<TropicalKind>), SELECTOR(T))
    { 
      return T(0); 
    }
        
    template<typename T>
    inline
    T zero_value(SELECTOR(algebra::TropicalSemiring<algebra::TropicalMax>), SELECTOR(T))
    { 
      return utility::limits<T>::min(); 
    }

    template<typename T>
    inline
    T zero_value(SELECTOR(algebra::TropicalSemiring<algebra::TropicalMin>), SELECTOR(T))
    { 
      return utility::limits<T>::max(); 
    }

    /*------------.
    | op_contains |
    `------------*/
    template<class TropicalKind, typename T>
    inline
    bool op_contains(const algebra::TropicalSemiring<TropicalKind>& s, T c)
    { 
      return true; 
    }

    /*--------------------.
    | Multiplication is + |
    `--------------------*/
    template<class TropicalKind, typename T, typename U>
    inline
    void op_in_mul(const algebra::TropicalSemiring<TropicalKind>& s1,
		   T& dst, U arg)
    { 
      if ((dst == zero_value(SELECT(algebra::TropicalSemiring<TropicalKind>), 
			     SELECT(T))) ||
	  (arg == zero_value(SELECT(algebra::TropicalSemiring<TropicalKind>), 
			     SELECT(U))))
	dst = zero_value(SELECT(algebra::TropicalSemiring<TropicalKind>), SELECT(T));
      else
	dst += arg; 
    }

    template<class TropicalKind, typename T, typename U>
    inline
    T op_mul(const algebra::TropicalSemiring<TropicalKind>&, T a, U b)
    { 
      if ((a == zero_value(SELECT(algebra::TropicalSemiring<TropicalKind>), 
			   SELECT(T))) ||
	  (b == zero_value(SELECT(algebra::TropicalSemiring<TropicalKind>), 
			   SELECT(U))))
	return zero_value(SELECT(algebra::TropicalSemiring<TropicalKind>), SELECT(T));
      return a + b; 
    }

    /*---------.
    | Addition |
    `---------*/
    template<typename T, typename U>
    inline
    void op_in_add(const algebra::TropicalSemiring<algebra::TropicalMax>& s1,
		   T& dst, U arg)
    { 
      dst = std::max(dst, arg); 
    }

    template<typename T, typename U>
    void op_in_add(const algebra::TropicalSemiring<algebra::TropicalMin>& s1,
		   T& dst, U arg)
    { 
      dst = std::min(dst, arg); 
    }

    template<typename T, typename U>
    T op_add(const algebra::TropicalSemiring<algebra::TropicalMax>&, T a, U b)
    { 
      return std::max(a, b); 
    }

    template<typename T, typename U>
    T op_add(const algebra::TropicalSemiring<algebra::TropicalMin>&, T a, U b)
    { 
      return std::min(a, b); 
    }

    /*-----.
    | Star |
    `-----*/
    template <typename T>
    static inline bool 
    op_starable(const algebra::TropicalSemiring<algebra::TropicalMin>&, T b)
    { 
      if (b < 0) 
	return false;
      return true;
    }

    template <class T>
    static inline void 
    op_in_star(const algebra::TropicalSemiring<algebra::TropicalMin>&, T& b)
    { 
      if (b >= 0)
	{
	  b = 0;
	  return;
	}
      assertion(! "star not defined.");
    }

    template <typename T>
    static inline bool 
    op_starable(const algebra::TropicalSemiring<algebra::TropicalMax>&, T b)
    { 
      if (b > 0) 
	return false;
      return true;
    }

    template <class T>
    static inline void 
    op_in_star(const algebra::TropicalSemiring<algebra::TropicalMax>&, T& b)
    { 
      if (b <= 0)
	{
	  b = 0;
	  return;
	}
      assertion(! "star not defined.");
    }

    template <class TropicalKind, class T>
    inline
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose(const algebra::TropicalSemiring<TropicalKind>& set, SELECTOR(T))
    {
      return Element<algebra::TropicalSemiring<TropicalKind>, T>
	(set, utility::random::generate<T>());
    }

    template <class TropicalKind, typename T>
    inline
    bool
    op_can_choose_non_starable(const algebra::TropicalSemiring<TropicalKind>& set,
				SELECTOR(T))
    {
      return true;
    }

    template <class TropicalKind, class T>
    inline
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose_starable(const algebra::TropicalSemiring<TropicalKind>& set,
			SELECTOR(T))
    {
      const T min = TropicalKind::template NonStareableInterval<T>::inf();
      const T max = TropicalKind::template NonStareableInterval<T>::sup();
      
      T r;
      do
	r = op_choose(set, SELECT(T));
      while ( (min < r) && (r < max) );
      return r;
    }

    template <class TropicalKind, class T>
    inline
    Element<algebra::TropicalSemiring<TropicalKind>, T>
    op_choose_non_starable(const algebra::TropicalSemiring<TropicalKind>& set,
			    SELECTOR(T))
    {
      const T min = TropicalKind::template NonStareableInterval<T>::inf();
      const T max = TropicalKind::template NonStareableInterval<T>::sup();
      
      T r;
      do
	r = op_choose(set, SELECT(T));
      while ( (max <= r) || (r <= min) );
      return r;
    }

    /*---------------.
    | Pretty printer |
    `---------------*/
    template<typename St, typename T>
    St& op_rout(const algebra::TropicalSemiring<algebra::TropicalMax>&, St& st, const T& v)
    { 
      if (v == zero_value(SELECT(algebra::TropicalSemiring<algebra::TropicalMax>), SELECT(T)))
	st << "-oo";
      else
	st << v;
      return st;
    }    

    template<typename St, typename T>
    St& op_rout(const algebra::TropicalSemiring<algebra::TropicalMin>& s, St& st, const T& v)
    { 
      if (v == zero_value(SELECT(algebra::TropicalSemiring<algebra::TropicalMin>), SELECT(T)))
	st << "+oo";
      else
	st << v;
      return st;
    }    

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SEMIRING_TROPICAL_SEMIRING_HXX
