// tropical_semiring.hxx
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef ALGEBRA_TROPICAL_SEMIRING_HXX
# define ALGEBRA_TROPICAL_SEMIRING_HXX
# include <vaucanson/config/system.hh>
# ifdef HAVE_LIMITS
#  include <limits>
# else
#  include <vaucanson/misc/limits.hh>
# endif // HAVE_LIMITS
# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hh>

namespace vcsn {

  namespace algebra {

    /*---------------.
    | Identity value |
    `---------------*/
    template<class TropicalKind, typename T> 
    inline
    T identity_value(SELECTOR(TropicalSemiring<TropicalKind>), SELECTOR(T))
    { 
      return T(0); 
    }
        
    template<typename T>
    inline
    T zero_value(SELECTOR(TropicalSemiring<TropicalMax>), SELECTOR(T))
    { 
      return std::numeric_limits<T>::min(); 
    }

    template<typename T>
    inline
    T zero_value(SELECTOR(TropicalSemiring<TropicalMin>), SELECTOR(T))
    { 
      return std::numeric_limits<T>::max(); 
    }

    /*------------.
    | op_contains |
    `------------*/
    template<class TropicalKind, typename T>
    inline
    bool op_contains(const TropicalSemiring<TropicalKind>& s, T c)
    { 
      using namespace utility::concepts;

      function_requires<HasLimits<T> >();
      return true; 
    }

    /*--------------------.
    | Multiplication is + |
    `--------------------*/
    template<class TropicalKind, typename T, typename U>
    inline
    void op_in_mul(const TropicalSemiring<TropicalKind>& s1,
		   T& dst, U arg)
    { 
      if ((dst == zero_value(SELECT(TropicalSemiring<TropicalKind>), 
			     SELECT(T))) ||
	  (arg == zero_value(SELECT(TropicalSemiring<TropicalKind>), 
			     SELECT(U))))
	dst = zero_value(SELECT(TropicalSemiring<TropicalKind>), SELECT(T));
      else
	dst += arg; 
    }

    template<class TropicalKind, typename T, typename U>
    inline
    T op_mul(const TropicalSemiring<TropicalKind>& s, T a, U b)
    { 
      if ((a == zero_value(SELECT(TropicalSemiring<TropicalKind>), 
			   SELECT(T))) ||
	  (b == zero_value(SELECT(TropicalSemiring<TropicalKind>), 
			   SELECT(U))))
	return zero_value(SELECT(TropicalSemiring<TropicalKind>), SELECT(T));
      return a + b; 
    }

    /*---------.
    | Addition |
    `---------*/
    template<typename T, typename U>
    inline
    void op_in_add(const TropicalSemiring<TropicalMax>& s1,
		   T& dst, U arg)
    { 
      dst = std::max(dst, arg); 
    }

    template<typename T, typename U>
    void op_in_add(const TropicalSemiring<TropicalMin>& s1,
		   T& dst, U arg)
    { 
      dst = std::min(dst, arg); 
    }

    template<typename T, typename U>
    T op_add(const TropicalSemiring<TropicalMax>& s, T a, U b)
    { 
      return std::max(a, b); 
    }

    template<typename T, typename U>
    T op_add(const TropicalSemiring<TropicalMin>& s, T a, U b)
    { 
      return std::min(a, b); 
    }

    /*-----.
    | Star |
    `-----*/
    template <typename T>
    static inline bool 
    op_stareable(const TropicalSemiring<TropicalMin>& s, T b)
    { 
      if (b < 0) 
	return false;
      return true;
    }

    template <class T>
    static inline void 
    op_in_star(const TropicalSemiring<TropicalMin>& s, T& b)
    { 
      if (b >= 0)
	b = 0;
      assert(! "star not defined.");
    }

    template <typename T>
    static inline bool 
    op_stareable(const TropicalSemiring<TropicalMax>& s, T b)
    { 
      if (b > 0) 
	return false;
      return true;
    }

    template <class T>
    static inline void 
    op_in_star(const TropicalSemiring<TropicalMax>& s, T& b)
    { 
      if (b <= 0)
	b = 0;
      assert(! "star not defined.");
    }


    /*---------------.
    | Pretty printer |
    `---------------*/
    template<typename St, typename T>
    St& op_rout(const TropicalSemiring<TropicalMax>& s, St& st, const T& v)
    { 
      if (v == zero_value(SELECT(TropicalSemiring<TropicalMax>), SELECT(T)))
	st << "-oo";
      else
	st << v;
      return st;
    }    

    template<typename St, typename T>
    St& op_rout(const TropicalSemiring<TropicalMin>& s, St& st, const T& v)
    { 
      if (v == zero_value(SELECT(TropicalSemiring<TropicalMin>), SELECT(T)))
	st << "+oo";
      else
	st << v;
      return st;
    }    

  } // algebra

} // vcsn

#endif // ALGEBRA_TROPICAL_SEMIRING_HXX
