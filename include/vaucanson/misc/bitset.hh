// bitset.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_MISC_BITSET_HH
# define VCSN_MISC_BITSET_HH

/**
 * @file   bitset.hh
 * @brief  Bitset class declaration.
 *
 * @author Thomas Claveirole <thomas@lrde.epita.fr>
 * @see Bitset
 */

# include <iterator>
# include <iostream>
# include <functional>

namespace utility
{

  /**
   * @brief Dynamic bitset class.
   *
   * This is a dynamic bitset implementation which behave almost like
   * a std::set<int>.
   *
   * @author Thomas Claveirole <thomas@lrde.epita.fr>
   */
  struct Bitset
  {
    typedef int						key_type;
    typedef int						value_type;
    typedef std::less<key_type>				key_compare;
    typedef key_compare					value_compare;
    // FIXME: Missing to be std::set compliant: allocator_type.
    // FIXME: reference and const_reference are not real references, because
    // it would prevents a code using a reverse_iterator to compile.
    typedef value_type					reference;
    typedef const value_type				const_reference;
    struct						iterator;
    struct						const_iterator;
    typedef unsigned int				size_type;
    typedef int						difference_type;
    typedef value_type*					pointer;
    typedef const value_type*				const_pointer;
    typedef std::reverse_iterator<iterator>		reverse_iterator;
    typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

    // data_type is the type used for the bit field.
    typedef unsigned int				data_type;

    // FIXME: Constructors have almost nothing common to std::set.

    /**
     * @brief Default constructor.
     *
     * @param max The highest integer which could be inserted into the set.
     */
    Bitset(size_type max);

    /// Constructor with user-provided bit field.
    Bitset(size_type max, const data_type* data);

    /// Copy constructor.
    Bitset(const Bitset& bs);

    /// Constructor from Input Iterators.
    template <class InputIterator>
    Bitset(InputIterator first, InputIterator last);

    /// Standard destructor.
    ~Bitset();

    /// Affectation.
    Bitset&	operator = (const Bitset& rhs);

    /// Iterators.
    /** @{ */
    iterator		begin();
    const_iterator	begin() const;
    iterator		end();
    const_iterator	end() const;
    /** @} */

    /// Reverse iterators.
    /** @{ */
    reverse_iterator		rbegin();
    const_reverse_iterator	rbegin() const;
    reverse_iterator		rend();
    const_reverse_iterator	rend() const;
    /** @} */

    bool	empty() const;
    size_type	size() const;
    size_type	max_size() const;

    /// Insert an element into the set.
    /** @{ */
    std::pair<iterator, bool>	insert(const value_type& x);
    iterator			insert(iterator position, const value_type& x);
    template <class InputIterator>
    void			insert(InputIterator first,
				       InputIterator last);
    /** @} */

    /// Erase an element from the set.
    /** @{ */
    void	erase(iterator position);
    size_type	erase(const key_type& x);
    void	erase(iterator first, iterator last);
    /** @} */

    /// Swap with another Bitset.
    void	swap(Bitset& other);

    /// Clear the set.
    void	clear();

    key_compare		key_comp() const;
    value_compare	value_comp() const;

    /// Find an element in the set.
    iterator	find(const key_type& x) const;

    /// Used for compatibility with std::set. Returns 0 or 1.
    size_type	count(const key_type& x) const;

    iterator				lower_bound(const key_type& x) const;
    iterator				upper_bound(const key_type& x) const;
    std::pair<iterator, iterator>	equal_range(const key_type& x) const;

    bool	operator == (const Bitset& rhs) const;
    bool	operator < (const Bitset& rhs) const;
    bool	operator != (const Bitset& rhs) const;
    bool	operator > (const Bitset& rhs) const;
    bool	operator >= (const Bitset& rhs) const;
    bool	operator <= (const Bitset& rhs) const;

    Bitset	operator & (const Bitset& rhs) const;
    Bitset	operator | (const Bitset& rhs) const;

    /// Returns the xth bit.
    bool	operator [] (const key_type& x) const;

    /// Project the set onto another bitset. The result is space-optimized.
    Bitset	project(const Bitset& b) const;

    /**
     * @brief Inverse function of project.
     *
     * S.project(T).unproject(T) == S cap T
     *
     * @see project()
     */
    Bitset	unproject(const Bitset& b) const;

    /// Reinterpret bits as unsigned int.
    unsigned	to_unsigned() const;

    /// Reinterpret bits as another type.
    template <typename Type>
    const Type	cast() const;

    /// Print the set.
    std::ostream&	print(std::ostream& ostr) const;

  protected:
    /// Calculates the number of data_type needed for the set.
    static
    size_type	get_data_size(size_type max);

    /// Get the index of x in the data_ attribute.
    static
    size_type	get_index(const key_type& x);

    /// Get the bit number of x inside the data_[i] attribute.
    static
    size_type	get_bitnum(const key_type& x);

    /// Get a bit inside data_.
    bool	get_bit(size_type index, size_type bit) const;

    /// Recalculate the set's size when invalid.
    size_type	compute_size() const;

    /*-------------------.
    | Iterator on bits.  |
    `-------------------*/
    struct bit_iterator
    {
      bit_iterator(size_type index = 0, size_type bitnum = 0);
      const bit_iterator&	operator -- ();
      const bit_iterator&	operator ++ ();
      value_type		operator * () const;
      bool			operator == (const bit_iterator& rhs) const;
      bool			operator != (const bit_iterator& rhs) const;
      size_type			get_index() const;
      size_type			get_bitnum() const;
    protected:
      size_type		index_;
      size_type		bitnum_;
      value_type	value_;
    };

    bit_iterator	bit_begin() const;
    const bit_iterator&	bit_end() const;

    /// Get a bit inside data_ given an iterator.
    bool	get_bit(const bit_iterator& it) const;

    /*------------------.
    | Actions on bits.  |
    `------------------*/

    template <typename CountType, CountType Start, CountType Step>
    struct BitActionCount
    {
      BitActionCount();

      CountType	value;

      bool	operator () (const Bitset& bitset,
			     size_type index,
			     size_type bit,
			     bool value);
    };

    /*--------------------------------.
    | do_on_bit(BitAction, element_t) |
    `--------------------------------*/

    /// Perform an action onto the bit corresponding to an element.
    /** @{ */
    template <class BitAction>
    bool	do_on_bit(BitAction& action, const key_type& x);
    template <class BitAction>
    bool	do_on_bit(BitAction& action, const bit_iterator& it);
    /** @} */

    /// Perform an action onto the bit corresponding to an element, const.
    /** @{ */
    template <class ConstBitAction>
    bool	do_on_bit(ConstBitAction& action, const key_type& x) const;
    template <class ConstBitAction>
    bool	do_on_bit(ConstBitAction& action,
			  const bit_iterator& it) const;
    /** @} */

    /*-------------------.
    | Attributes, misc.  |
    `-------------------*/

    enum { invalid_size = static_cast <unsigned int> (-1) };

    size_type		data_size_;
    data_type*		data_;

    size_type		max_size_;
    mutable size_type	size_;
    bit_iterator	end_;

  public:

    /*-----------------.
    | const_iterator.  |
    `-----------------*/

    struct const_iterator
    {
      typedef std::bidirectional_iterator_tag	iterator_category;
      typedef Bitset::value_type		value_type;
      typedef Bitset::difference_type		difference_type;
      typedef Bitset::reference			reference;
      typedef Bitset::pointer			pointer;

      const_iterator();
      const_iterator(const Bitset* bs);
      const_iterator(const Bitset* bs, const bit_iterator& cbit);
      const_iterator(const const_iterator& it);
      const_iterator(const iterator& it);

      const const_iterator&	operator ++ ();
      const_iterator		operator ++ (int);
      const const_iterator&	operator -- ();
      const_iterator		operator -- (int);
      bool			operator == (const const_iterator& rhs) const;
      bool			operator == (const iterator& rhs) const;
      bool			operator != (const const_iterator& rhs) const;
      bool			operator != (const iterator& rhs) const;
      value_type		operator * () const;

    protected:
      void			skip_zeros_forward();
      void			skip_zeros_backward();

      const Bitset* bs_;
      bit_iterator cbit_;
    };

    /*-----------.
    | iterator.  |
    `-----------*/

    struct iterator
    {
      typedef std::bidirectional_iterator_tag	iterator_category;
      typedef Bitset::value_type		value_type;
      typedef Bitset::difference_type		difference_type;
      typedef Bitset::reference			reference;
      typedef Bitset::pointer			pointer;

      iterator();
      iterator(const Bitset* bs);
      iterator(const Bitset* bs, const bit_iterator& cbit);
      iterator(const iterator& it);

      // Friend functions for const_iterator
      friend const_iterator::const_iterator(const iterator& it);

      const iterator&	operator ++ ();
      iterator		operator ++ (int);
      const iterator&	operator -- ();
      iterator		operator -- (int);
      bool		operator == (const iterator& rhs) const;
      bool		operator == (const const_iterator& rhs) const;
      bool		operator != (const iterator& rhs) const;
      bool		operator != (const const_iterator& rhs) const;
      value_type	operator * () const;

    protected:
      void		skip_zeros_forward();
      void		skip_zeros_backward();

      const Bitset* bs_;
      bit_iterator cbit_;
    };
  };


  /// Print a bitset onto an output stream.
  std::ostream&
  operator << (std::ostream& ostr, const Bitset& set);

} // end of namespace utility

namespace std
{
  /// Specialized swap.
  template <>
  void swap(utility::Bitset& lhs, utility::Bitset& rhs);

  /// Specialized insert_iterator.
  template <>
  class insert_iterator<utility::Bitset> :
    public iterator<output_iterator_tag, void, void, void, void>
  {
  public:
    typedef utility::Bitset		container_type;

    insert_iterator(utility::Bitset& x, utility::Bitset::iterator);

    insert_iterator<utility::Bitset>&
    operator = (utility::Bitset::const_reference value);

    insert_iterator<utility::Bitset>&
    operator * ();

    insert_iterator<utility::Bitset>&
    operator ++ ();

    insert_iterator<utility::Bitset>&
    operator ++ (int);
  protected:
    utility::Bitset*		container;
  };
}


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/misc/bitset.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_BITSET_HH
