//
// k_monoid_base.hh
// 
// Made by (Maxime Rey)
// Login   <max@nirgal>
// 
// Started on  Mon Mar 31 21:17:20 2003 Maxime Rey
// Last update Tue Apr  1 17:09:09 2003 Maxime Rey
//

#ifndef   K_MONOID_BASE_HH_
# define   K_MONOID_BASE_HH_

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
# include <misc/traits.hh>
# include <string>

namespace vcsn {

  namespace algebra {

    template<class Self>
    struct KMonoidBase 
      : MonoidBase<Self>
    {
      typedef typename traits::virtual_types<Self>::alphabet_t  alphabet_t;
      typedef typename alphabet_t::letter_t                        letter_t;

      alphabet_t&	alphabet();

      const alphabet_t& alphabet() const;

    protected:
      KMonoidBase();

      KMonoidBase(const KMonoidBase& m);
    };

  } // algebra

  using namespace algebra;

  template<class Self, typename T>
  struct MetaElement<KMonoidBase<Self>, T>
    : MetaElement<MonoidBase<Self>, T>
  {
    typedef typename op_begin_traits<Self, T>::ret_t	iterator;

    typedef typename 
    op_begin_traits<Self, T>::const_ret_t		const_iterator;

    typedef typename op_rbegin_traits<Self, T>::ret_t	reverse_iterator;

    typedef typename 
    op_rbegin_traits<Self, T>::const_ret_t		const_reverse_iterator;


    size_t		      length() const;


    iterator			begin();
    const_iterator		begin() const;
    reverse_iterator		rbegin();
    const_reverse_iterator	rbegin() const;

    iterator			end();
    const_iterator		end() const;
    reverse_iterator		rend();
    const_reverse_iterator	rend() const;

    void insert(typename KMonoidBase<Self>::letter_t l);
    void insert(Element<FreeMonoid<typename KMonoidBase<Self>::alphabet_t>, T> str);

    void clear();

    void set_k(unsigned k)
    {
      k_ = k;
    }

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);

    unsigned k_;
  };


  template<typename Self, typename T>
  bool op_contains(const KMonoidBase<Self>& s, const T& v);

  
} // vcsn

# include <algebra/concept/k_monoid_base.hxx>

#endif /* !K_MONOID_BASE_HH_ */
