
/*******************************************************************
 * <vaucanson/misc/triplet.hh>: utility tools similar to std::pair *
 * and std::triplet                                                *
 *******************************************************************/
// $Id$

/* this file is part of the Vaucanson project. */
#ifndef UTILITY_TRIPLET_HH
# define UTILITY_TRIPLET_HH

namespace utility
{

  /*! A simple class like std::pair, for triplets.
   * 
   * This class provides the same services as std::pair, except
   * that a \a third attribute and third_type are involved.
   */
  template <class _T1, class _T2, class _T3>
  struct triplet {
    typedef _T1 first_type;
    typedef _T2 second_type;
    typedef _T3 third_type;

    _T1 first;
    _T2 second;
    _T3 third;

    triplet() : first(), second(), third() {}
    triplet(const _T1& __a, const _T2& __b, const _T3& __c) 
      : first(__a), second(__b), third(__c) {}

    template <class _U1, class _U2, class _U3>
    triplet(const triplet<_U1, _U2, _U3>& __t) 
      : first(__t.first), second(__t.second), third(__t.third) {}
  };
}

template <class _T1, class _T2, class _T3>
inline bool operator==(const utility::triplet<_T1, _T2, _T3>& __x,
		       const utility::triplet<_T1, _T2, _T3>& __y)
{ 
  return __x.first == __y.first 
    && __x.second == __y.second
    && __x.third == __y.third; 
}

template <class _T1, class _T2, class _T3>
inline bool operator<(const utility::triplet<_T1, _T2, _T3>& __x, 
		      const utility::triplet<_T1, _T2, _T3>& __y)
{ 
  return __x.first < __y.first || 
    (!(__y.first < __x.first) 
     && __x.second < __y.second) ||
    (!(__y.first < __x.first) 
     && !(__x.second < __y.second) 
     && __x.third < __y.third) ; 
}

template <class _T1, class _T2, class _T3>
inline bool operator!=(const utility::triplet<_T1, _T2, _T3>& __x,
		       const utility::triplet<_T1, _T2, _T3>& __y) 
{
  return !(__x == __y);
}

template <class _T1, class _T2, class _T3>
inline bool operator>(const utility::triplet<_T1, _T2, _T3>& __x, 
		      const utility::triplet<_T1, _T2, _T3>& __y) 
{
  return __y < __x;
}

template <class _T1, class _T2, class _T3>
inline bool operator<=(const utility::triplet<_T1, _T2, _T3>& __x, 
		       const utility::triplet<_T1, _T2, _T3>& __y) 
{
  return !(__y < __x);
}

template <class _T1, class _T2, class _T3>
inline bool operator>=(const utility::triplet<_T1, _T2, _T3>& __x, 
		       const utility::triplet<_T1, _T2, _T3>& __y) 
{
  return !(__x < __y);
}

namespace utility
{
  /*! \brief Make a triplet from three values
   *
   * This function behaves as std::make_pair, except that
   * it takes three arguments and return a \a triplet.
   */
  template<class _T1, class _T2, class _T3>
  inline triplet<_T1, _T2, _T3> 
  make_triplet(const _T1& __x, const _T2& __y, const _T3& __z)
  {
    return triplet<_T1, _T2, _T3>(__x, __y, __z);
  }

}
#endif 
