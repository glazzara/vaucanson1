#ifndef VCSN_ALGEBRA_CONCRETE_FREE_MONOID_TOOLS_HXX
# define VCSN_ALGEBRA_CONCRETE_FREE_MONOID_TOOLS_HXX

# include <vaucanson/algebra/concrete/free_monoid/tools.hh>

namespace vcsn
{

  template<typename A>
  const std::list<typename A::letter_t>&
  identity_value(SELECTOR(algebra::FreeMonoidBase<A>),
                 SELECTOR(std::list<typename A::letter_t>))
  {
    static const std::list<typename A::letter_t> instance;
    return instance;
  }

  template<typename A>
  std::list<typename A::letter_t>
  op_convert(SELECTOR(algebra::FreeMonoidBase<A>),
             SELECTOR(std::list<typename A::letter_t>),
             const typename A::letter_t& c)
  {
    std::list<typename A::letter_t> l;
    l.push_back(c);
    return l;
  }

  template <typename A>
  void
  op_in_mul(const algebra::FreeMonoidBase<A>& s,
            std::list<typename A::letter_t>& dst,
            const std::list<typename A::letter_t>& src)
  {
    typedef typename std::list<typename A::letter_t>::const_iterator it_t;
    for (it_t i = src.begin();
	 i != src.end();
	 i++)
      dst.push_back(*i);
  }

  template <typename A>
  std::list<typename A::letter_t>
  op_mul(const algebra::FreeMonoidBase<A>& s,
         const std::list<typename A::letter_t>& a,
         const std::list<typename A::letter_t>& b)
  {
    typedef typename std::list<typename A::letter_t>::const_iterator it_t;
    std::list<typename A::letter_t> ret(a);
    op_in_mul(s, ret, b);
    return ret;
  }

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_FREE_MONOID_TOOLS_HXX
