// alphabets_base.hh
//
// VCSN_HEADER

#ifndef ALGEBRA_ALPHABETS_BASE_HH
# define ALGEBRA_ALPHABETS_BASE_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/internal/traits.hh>
# include <vaucanson/misc/container_ops.hh>

namespace vcsn {

  namespace algebra {

    /*--------------------.
    | AlphabetsBase<Self> |
    `--------------------*/

    template<class Self>
    struct AlphabetsBase 
      : Structure<Self>
    {
    protected:
      AlphabetsBase();
      AlphabetsBase(const AlphabetsBase& other);
    };

    /*----------------.
    | alphabet_traits |
    `----------------*/
    template<typename S, typename T>
    struct alphabet_traits 
    {
      typedef traits::undefined_type	letter_t;
    };

  } // algebra

  using namespace algebra;
  
  /*------------------------------------.
  | MetaElement<AlphabetsBase<Self>, T> |
  `------------------------------------*/
    template<class Self, typename T>
    struct MetaElement<AlphabetsBase<Self>, T>
      : MetaElement<Structure<Self>, T>
    {
      typedef typename alphabet_traits<Self, T>::letter_t	letter_t;
      typedef typename op_begin_traits<Self, T>::const_ret_t	const_iterator;
      typedef typename op_begin_traits<Self, T>::ret_t		iterator;

      size_t		size() const;
      bool		contains(const letter_t& l) const;
      bool		is_finite() const;
      iterator		begin();
      const_iterator	begin() const;
      iterator		end();
      const_iterator	end() const;
      /* sugar */
      void		insert(const letter_t& l);

    protected:
      MetaElement();
      MetaElement(const MetaElement& other);
    };

    template<typename Self, typename St, typename T>
    St& op_rout(const AlphabetsBase<Self>& s, St& st, const T& a);

    // FIXME : add equality between two alphabets !

} // vcsn

# include <vaucanson/algebra/concept/alphabets_base.hxx>

#endif // ALGEBRA_ALPHABETS_BASE_HH
