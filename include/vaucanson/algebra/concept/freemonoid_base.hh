// freemonoid_base.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGEBRA_FREEMONOID_BASE_HH
# define ALGEBRA_FREEMONOID_BASE_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/
    //! Structural element for free monoid.
    /*! */

    template<class Self>
    struct FreeMonoidBase 
      : MonoidBase<Self>
    {
      typedef typename traits::virtual_types<Self>::alphabet_t  alphabet_t;
      typedef typename alphabet_t::letter_t			letter_t;

      alphabet_t&	alphabet();
      const alphabet_t& alphabet() const;

    protected:
      FreeMonoidBase();
      FreeMonoidBase(const FreeMonoidBase& m);
    };

  } // algebra


  /*-------------------------------------.
  | MetaElement<FreeMonoidBase<Self>, T> |
  `-------------------------------------*/

  template<class Self, typename T>
  struct MetaElement<FreeMonoidBase<Self>, T>
    : MetaElement<MonoidBase<Self>, T>
  {
    size_t		      length() const;
    void		      mirror();
    
    typedef typename op_begin_traits<Self, T>::ret_t	iterator;
    typedef typename 
    op_begin_traits<Self, T>::const_ret_t		const_iterator;
    typedef typename op_rbegin_traits<Self, T>::ret_t	reverse_iterator;
    typedef typename 
    op_rbegin_traits<Self, T>::const_ret_t		const_reverse_iterator;

    iterator			begin();
    const_iterator		begin() const;
    reverse_iterator		rbegin();
    const_reverse_iterator	rbegin() const;
    iterator			end();
    const_iterator		end() const;
    reverse_iterator		rend();
    const_reverse_iterator	rend() const;

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };

  template<typename S, typename T>
  Element<S, T>
  mirror(const Element<S, T>& e);
    
  template<typename Self, typename T>
  void op_in_mirror(const FreeMonoidBase<Self>& s, T& v);

  template<typename Self, typename T>
  bool op_contains(const FreeMonoidBase<Self>& s, const T& v);

  template<typename Self, typename St, typename T>
  St& op_rout(const FreeMonoidBase<Self>& s, St& st, const T& v);

} // vcsn

# include <vaucanson/algebra/concept/freemonoid_base.hxx>

#endif // ALGEBRA_FREEMONOID_BASE_HH
