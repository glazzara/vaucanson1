// alphabets_base.hh
//
// $Id$
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
    //! Structural element of alphabet.
    /*!
     * Empty class. Its role is essentially in static typing.
     */
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
    //! Traits defined by Element<AlphabetsBase, T>.
    /*! Each specialization of Element<AlphabetsBase, T> must
     * specialize this traits too. 
     * letter_t defines the type of letters the set contains.
     */
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
  //! Services of every alphabet.
  /*! MetaElement<AlphabetsBase<Self>, T> defines the services of
   *  alphabet.
   */
    template<class Self, typename T>
    struct MetaElement<AlphabetsBase<Self>, T>
      : MetaElement<Structure<Self>, T>
    {
      typedef typename alphabet_traits<Self, T>::letter_t	letter_t;
      typedef typename op_begin_traits<Self, T>::const_ret_t	const_iterator;
      typedef typename op_begin_traits<Self, T>::ret_t		iterator;

      /*! Insert a letter in the alphabet. */
      void		insert(const letter_t& l);
      /*! Select a random letter in the alphabet. */
      letter_t          choose();
      /*! Cardinal of the alphabet. */
      size_t		size()                      const;
      /*! Return true if l is in the alphabet. */
      bool		contains(const letter_t& l) const;
      /*! Return true if the alphabet is finite. */
      bool		is_finite()                 const;
      /*! Iterator that is the beginning of the alphabet. */
      iterator		begin();
      /*! Iterator that is the beginning of the alphabet. (const version) */
      const_iterator	begin()                     const;
      /*! Iterator that is the end of the alphabet. */
      iterator		end();
      /*! Iterator that is the end of the alphabet. (const version) */
      const_iterator	end()                       const;

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
