// bitset.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_BITSET_HXX
# define VCSN_MISC_BITSET_HXX

/**
 * @file   bitset.hxx
 * @brief  This file contains a Bitset class implementaion.
 * 
 * @author Thomas Claveirole <thomas@lrde.epita.fr>
 */

# include <vaucanson/misc/bitset.hh>
# include <vaucanson/misc/contract.hh>

# include <cstdlib>

namespace utility
{
  /*-------.
  | Bitset |
  `-------*/

  // Default contructors.
  inline
  Bitset::Bitset(size_type max) : data_size_	(get_data_size(max)),
				  data_		(new data_type[data_size_]),
				  max_size_	(max),
				  size_		(0),
				  end_	(bit_iterator(get_index(max_size_),
						      get_bitnum(max_size_)))
  {
    bzero(data_, data_size_ * sizeof (data_type));
  }

  inline
  Bitset::Bitset(size_type max, const data_type* data)
    : data_size_	(get_data_size(max)),
      data_		(new data_type[data_size_]),
      max_size_		(max),
      size_		(invalid_size),
      end_		(bit_iterator(get_index(max_size_),
				      get_bitnum(max_size_)))
  {
    memcpy(data_, data, data_size_ * sizeof (data_type));
  }
  
  // Copy constructor.
  inline
  Bitset::Bitset(const Bitset& bs) : data_size_	(bs.data_size_),
				     data_	(new data_type[data_size_]),
				     max_size_	(bs.max_size_),
				     size_	(bs.size_),
				     end_	(bs.end_)
  {
    memcpy(data_, bs.data_, data_size_ * sizeof (data_type));
  }

  // Constructor from iterators.
  template <class InputIterator>
  Bitset::Bitset(InputIterator first, InputIterator last)
  {
    value_type	max = 0;

    for (InputIterator i = first; i != last; ++i)
      {
	assertion(*i >= 0);
	if (*i > max)
	  max = *i;
      }
    data_size_ = get_data_size(max + 1);
    data_ = new data_type[data_size_];
    bzero(data_, data_size_ * sizeof (data_type));
    max_size_ = max + 1;
    size_ = 0;
    end_ = bit_iterator(get_index(max_size_), get_bitnum(max_size_));
    insert(first, last);
  }

  // Destructor.
  inline
  Bitset::~Bitset()
  {
    delete[] data_;
  }

  // Assignment.
  inline
  Bitset&
  Bitset::operator = (const Bitset& rhs)
  {
    if (this != &rhs)
      {
	data_size_ = rhs.data_size_;
	delete[] data_;
	data_ = new data_type[data_size_];
	memcpy(data_, rhs.data_, data_size_ * sizeof (data_type));
	max_size_ = rhs.max_size_;
	size_ = rhs.size_;
	end_ = rhs.end_;
      }
    postcondition(*this == rhs);
    return *this;
  }

  /*------------.
  | Iterators.  |
  `------------*/

  // begin
  inline
  Bitset::iterator
  Bitset::begin()
  {
    return iterator (this);
  }

  inline
  Bitset::const_iterator
  Bitset::begin() const
  {
    return const_iterator (this);
  }

  // end
  inline
  Bitset::iterator
  Bitset::end()
  {
    return iterator (this, end_);
  }

  inline
  Bitset::const_iterator
  Bitset::end() const
  {
    return const_iterator (this, end_);
  }

  /*--------------------.
  | Reverse Iterators.  |
  `--------------------*/

  // rbegin
  inline
  Bitset::reverse_iterator
  Bitset::rbegin()
  {
    return reverse_iterator (end());
  }

  inline
  Bitset::const_reverse_iterator
  Bitset::rbegin() const
  {
    return const_reverse_iterator (end());
  }

  // rend
  inline
  Bitset::reverse_iterator
  Bitset::rend()
  {
    return reverse_iterator (begin());
  }

  inline
  Bitset::const_reverse_iterator
  Bitset::rend() const
  {
    return const_reverse_iterator (begin());
  }

  /*------------------.
  | Misc. functions.  |
  `------------------*/

  // empty
  inline
  bool
  Bitset::empty() const
  {
    return size_ == 0;
  }

  // size
  inline
  Bitset::size_type
  Bitset::size() const
  {
    return size_ == invalid_size ? compute_size() : size_;
  }

  // max_size
  inline
  Bitset::size_type
  Bitset::max_size() const
  {
    return max_size_;
  }

  /*-------------.
  | Insertions.  |
  `-------------*/

  inline
  std::pair<Bitset::iterator, bool>
  Bitset::insert(const value_type& x)
  {
    precondition(static_cast<size_type> (x) < max_size_);

    size_type	idx = get_index(x);
    size_type	bnm = get_bitnum(x);

    if (get_bit(idx, bnm))
      return std::make_pair(end(), false);
    else
      {
	data_[idx] |= (1 << bnm);
	if (size_ != invalid_size)
	  size_++;
	return std::make_pair(iterator (this, bit_iterator (idx, bnm)), true);
      }
  }

  inline
  Bitset::iterator
  Bitset::insert(iterator, const value_type& x)
  {
    return insert(x).first;
  }

  template <class InputIterator>
  void
  Bitset::insert(InputIterator first, InputIterator last)
  {
    while (first != last)
      {
	insert(*first);
	++first;
      }
  }

  /*------.
  | Erase |
  `------*/

  inline
  void
  Bitset::erase(iterator position)
  {
    precondition(static_cast<size_type> (*position) < max_size_);

    erase(*position);
  }

  inline
  Bitset::size_type
  Bitset::erase(const key_type& x)
  {
    precondition(static_cast<size_type> (x) < max_size_);

    size_type	idx = get_index(x);
    size_type	bnm = get_bitnum(x);

    if (get_bit(idx, bnm))
      {
	data_[idx] &= ~(1 << bnm);
	if (size_ != invalid_size)
	  --size_;
	return 1;
      }
    else
      return 0;
  }

  inline
  void
  Bitset::erase(iterator first, iterator last)
  {
    while (first != last)
      {
	erase(*first);
	++first;
      }
  }
  
  /*------------------.
  | Misc. functions.  |
  `------------------*/

  // swap
  inline
  void
  Bitset::swap(Bitset& other)
  {
    std::swap(data_size_, other.data_size_);
    std::swap(data_, other.data_);
    std::swap(max_size_, other.max_size_);
    std::swap(size_, other.size_);
    std::swap(end_, other.end_);
  }

  // clear
  inline
  void
  Bitset::clear()
  {
    bzero(data_, data_size_ * sizeof (data_type));
    size_ = 0;
  }

  // key_compare
  inline
  Bitset::key_compare
  Bitset::key_comp() const
  {
    return key_compare ();
  }

  // value_compare
  inline
  Bitset::value_compare
  Bitset::value_comp() const
  {
    return value_compare ();
  }

  // find
  inline
  Bitset::iterator
  Bitset::find(const key_type& x) const
  {
    precondition(static_cast<size_type> (x) < max_size_);

    bit_iterator	it(get_index(x), get_bitnum(x));
    if (get_bit(it))
      return iterator (this, it);
    else
      return iterator (this, end_);
  }

  // count
  inline
  Bitset::size_type
  Bitset::count(const key_type& x) const
  {
    precondition(static_cast<size_type> (x) < max_size_);

    return get_bit(get_index(x), get_bitnum(x)) ? 1 : 0;
  }

  // lower_bound
  inline
  Bitset::iterator
  Bitset::lower_bound(const key_type& x) const
  {
    precondition(static_cast<size_type> (x) < max_size_);

    bit_iterator	it(get_index(x), get_bitnum(x));

    while ((it != bit_end()) && !get_bit(it))
      ++it;
    return iterator (this, it);
  }

  // upper_bound
  inline
  Bitset::iterator
  Bitset::upper_bound(const key_type& x) const
  {
    precondition(static_cast<size_type> (x) < max_size_);

    bit_iterator	it(get_index(x), get_bitnum(x));

    if (it == bit_begin())
      return iterator (this, end_);
    else
      {
	do
	  {
	    --it;
	  }
	while ((it != bit_begin()) && !get_bit(it));
	return iterator (this, get_bit(it) ? it : end_);
      }
  }

  // equal_range
  inline
  std::pair<Bitset::iterator, Bitset::iterator>
  Bitset::equal_range(const key_type& x) const
  {
    // FIXME: Could be optimized.
    return std::make_pair(lower_bound(x), upper_bound(x));
  }

  /*------------.
  | Operators.  |
  `------------*/

  inline
  bool
  Bitset::operator == (const Bitset& rhs) const
  {
    if (rhs.data_size_ < data_size_)
      return rhs.operator == (*this);
    else
      {
	for (size_type i = 0; i < data_size_; ++i)
	  if (data_[i] != rhs.data_[i])
	    return false;
	for (size_type i = data_size_; i < rhs.data_size_; ++i)
	  if (rhs.data_[i])
	    return false;
	return true;
      }
  }

  inline
  bool
  Bitset::operator < (const Bitset& rhs) const
  {
    // Case 1: rhs is longer than *this.
    for (size_type i = rhs.data_size_ - 1; i >= data_size_; ++i)
      if (rhs.data_[i])
	return true;
    // Case 2: *this is longer than rhs.
    for (size_type i = data_size_ - 1; i >= rhs.data_size_; ++i)
      if (data_[i])
	return false;
    // Common case: compare the bits rhs and *this have in common.
    for (int i = std::min(data_size_, rhs.data_size_) - 1; i >= 0; ++i)
      if (rhs.data_[i] != data_[i])
	return rhs.data_[i] > data_[i];
    // If we get out from the previous loop, then the bitsets are equals.
    return false;
  }

  inline
  bool
  Bitset::operator != (const Bitset& rhs) const
  {
    return !(*this == rhs);
  }

  inline
  bool
  Bitset::operator > (const Bitset& rhs) const
  {
    return rhs < *this;
  }

  inline
  bool
  Bitset::operator <= (const Bitset& rhs) const
  {
    return !(*this > rhs);
  }

  inline
  bool
  Bitset::operator >= (const Bitset& rhs) const
  {
    return !(*this < rhs);
  }

  inline
  Bitset
  Bitset::operator & (const Bitset& rhs) const
  {
    const size_type	r_data_size = std::min(data_size_, rhs.data_size_);
    const size_type	r_max_size = std::min(max_size_, rhs.max_size_);
    Bitset		result (r_max_size);
    
    for (size_type i = 0; i < r_data_size; ++i)
      {
	result.data_[i] = data_[i] & rhs.data_[i];
	if (result.data_[i])
	  result.size_ = invalid_size;
      }
    return result;
  }

  inline
  Bitset
  Bitset::operator | (const Bitset& rhs) const
  {
    if (rhs.data_size_ < data_size_)
      return rhs.operator | (*this);
    else
      {
	Bitset	result (rhs.max_size_);
	
	for (size_type i = 0; i < data_size_; ++i)
	  {
	    result.data_[i] = data_[i] | rhs.data_[i];
	    if (result.data_[i])
	      result.size_ = invalid_size;
	  }
	for (size_type i = data_size_; i < rhs.data_size_; ++i)
	  {
	    result.data_[i] = rhs.data_[i];
	    if (result.data_[i])
	      result.size_ = invalid_size;
	  }
	return result;
      }
  }    
  
  inline
  bool
  Bitset::operator [] (const key_type& x) const
  {
    return count(x);
  }

  /*------------------------------.
  | Projection and Unprojection.  |
  `------------------------------*/

  inline
  Bitset
  Bitset::project(const Bitset& b) const
  {
    BitActionCount<int, -1, 1> bit_counter;
    Bitset result(b.size());

    for (bit_iterator it = bit_begin();
	 (it != bit_end()) && (it != b.bit_end());
	 ++it)
      {
	if (b.do_on_bit(bit_counter, it) && get_bit(it))
	  result.insert(bit_counter.value);
      }
    return result;
  }

  inline
  Bitset
  Bitset::unproject(const Bitset& b) const
  {
    BitActionCount<int, 0, 1> bit_counter;
    Bitset result(b.max_size());
    bit_iterator b_it = b.bit_begin();

    while ((b_it != b.bit_end()) && !b.get_bit(b_it))
      ++b_it;
    for (bit_iterator it = bit_begin(); it != bit_end(); ++it)
      if (get_bit(it))
	{
	  while ((b_it != b.bit_end()) && (bit_counter.value < *it))
	    b.do_on_bit(bit_counter, ++b_it);
	  assertion(bit_counter.value == *it);
	  result.insert(*b_it);
	}
    return result;
  }

  /*--------.
  | Casts.  |
  `--------*/
  
  inline
  unsigned
  Bitset::to_unsigned() const
  {
    return cast<unsigned>();
  }
  
  template <class Type>
  const Type
  Bitset::cast() const
  {
    const Type* ptr = reinterpret_cast<const Type*> (data_);
    return *ptr;
  }
  
  /*--------.
  | Print.  |
  `--------*/

  inline
  std::ostream&
  Bitset::print(std::ostream& ostr) const
  {
    ostr << "{ ";
    for (Bitset::bit_iterator it = bit_begin(); it != bit_end(); ++it)
      if (get_bit(it))
	ostr << *it << ' ';
    return ostr << "}";
  }

  /*------------------.
  | Protected stuff.  |
  `------------------*/

  // get_data_size
  Bitset::size_type
  Bitset::get_data_size(size_type max)
  {
    precondition(max > 0);
    
    const size_type data_bits = sizeof (data_type) * 8;
    return max / data_bits + (max % data_bits ? 1 : 0);
  }

  // get_index
  inline
  Bitset::size_type
  Bitset::get_index(const key_type& x)
  {
    return x / (sizeof (data_type) * 8);
  }

  // get_bitnum
  inline
  Bitset::size_type
  Bitset::get_bitnum(const key_type& x)
  {
    return x % (sizeof (data_type) * 8);
  }

  // get_bit
  inline
  bool
  Bitset::get_bit(size_type index, size_type bit) const
  {
    return (data_[index] & (1 << bit)) != 0;
  }
  
  inline
  bool
  Bitset::get_bit(const bit_iterator& it) const
  {
    return get_bit(it.get_index(), it.get_bitnum());
  }

  // compute_size
  inline
  Bitset::size_type
  Bitset::compute_size() const
  {
    BitActionCount<int, 0, 1> bc;
    for (bit_iterator it = bit_begin(); it != bit_end(); ++it)
      do_on_bit(bc, it);
    return size_ = bc.value;
  }
  
  /*---------------.
  | Bit iterator.  |
  `---------------*/

  // constructors.
  inline
  Bitset::
  bit_iterator::bit_iterator(size_type index, size_type bitnum) :
    index_	(index),
    bitnum_	(bitnum),
    value_	(index_ * sizeof (data_type) * 8 + bitnum_)
  {
  }

  // operators.
  inline
  const Bitset::bit_iterator&
  Bitset::bit_iterator::operator -- ()
  {
    --value_;
    if (bitnum_)
      --bitnum_;
    else
      {
	bitnum_ = sizeof (data_type) * 8 - 1;
	--index_;
      }
    return (*this);
  }

  inline
  const Bitset::bit_iterator&
  Bitset::bit_iterator::operator ++ ()
  {
    ++value_;
    if (++bitnum_ >= sizeof (data_type) * 8)
      {
	bitnum_ = 0;
	++index_;
      }
    return *this;
  }

  inline
  Bitset::value_type
  Bitset::bit_iterator::operator * () const
  {
    return value_;
  }

  inline
  bool
  Bitset::bit_iterator::operator == (const bit_iterator& rhs) const
  {
    return rhs.value_ == value_;
  }

  inline
  bool
  Bitset::bit_iterator::operator != (const bit_iterator& rhs) const
  {
    return !(*this == rhs);
  }

  // get_index
  inline
  Bitset::size_type
  Bitset::bit_iterator::get_index() const
  {
    return index_;
  }

  // get_bitnum
  inline
  Bitset::size_type
  Bitset::bit_iterator::get_bitnum() const
  {
    return bitnum_;
  }
  
  // bit_begin
  inline
  Bitset::bit_iterator
  Bitset::bit_begin() const
  {
    return bit_iterator ();
  }

  // bit_end
  inline
  const Bitset::bit_iterator&
  Bitset::bit_end() const
  {
    return end_;
  }

  /*--------------.
  | Bit actions.  |
  `--------------*/

  // Count
  template <typename CountType, CountType Start, CountType Step>
  inline
  Bitset::
  BitActionCount<CountType, Start, Step>::BitActionCount() : value(Start)
  {
  }

  template <typename CountType, CountType Start, CountType Step>
  inline
  bool
  Bitset::
  BitActionCount<CountType, Start, Step>::operator () (const Bitset&,
						       size_type,
						       size_type,
						       bool val)
  {
    if (val)
      value += Step;
    return val;
  }

  /*------------.
  | do_on_bit.  |
  `------------*/

  // non-const
  template <class BitAction>
  inline
  bool
  Bitset::do_on_bit(BitAction& action, const key_type& x)
  {
    precondition(x < max_size_);

    const size_type index	= get_index(x);
    const size_type bit		= get_bitnum(x);
    const bool value		= get_bit(index, bit);
    return action(*this, index, bit, value);
  }

  template <class BitAction>
  inline
  bool
  Bitset::do_on_bit(BitAction& action, const bit_iterator& it)
  {
    return action(*this, it.get_index(), it.get_bitnum(), get_bit(it));
  }

  // const
  template <class ConstBitAction>
  inline
  bool
  Bitset::do_on_bit(ConstBitAction& action, const key_type& x) const
  {
    precondition(x < max_size_);

    const size_type index	= get_index(x);
    const size_type bit		= get_bitnum(x);
    const bool value		= get_bit(index, bit);
    return action(*this, index, bit, value);
  }

  template <class ConstBitAction>
  inline
  bool
  Bitset::do_on_bit(ConstBitAction& action, const bit_iterator& it) const
  {
    return action(*this, it.get_index(), it.get_bitnum(), get_bit(it));
  }

  /*---------------.
  | const_iterator |
  `---------------*/

  // Default constructors.
  inline
  Bitset::const_iterator::const_iterator() : bs_ (0), cbit_ ()
  {
    warning("The constructor Bitset::const_iterator::const_iterator() "
	    "is dangerous and therefore should not be used.");
  }

  inline
  Bitset::const_iterator::const_iterator(const Bitset* bs) : bs_(bs),
							     cbit_()
  {
    skip_zeros_forward();
  }
  
  inline
  Bitset::const_iterator::const_iterator(const Bitset* bs,
					 const bit_iterator& cbit)
    : bs_(bs),
      cbit_(cbit)
  {
    skip_zeros_forward();
  }
  
  // Copy constructors.
  inline
  Bitset::const_iterator::const_iterator(const const_iterator& it)
    : bs_(it.bs_), cbit_(it.cbit_)
  {
  }

  inline
  Bitset::const_iterator::const_iterator(const iterator& it)
    : bs_(it.bs_), cbit_(it.cbit_)
  {
  }

  // Operators.
  inline
  const Bitset::const_iterator&
  Bitset::const_iterator::operator ++ ()
  {
    ++cbit_;
    skip_zeros_forward();
    return *this;
  }

  inline
  Bitset::const_iterator
  Bitset::const_iterator::operator ++ (int)
  {
    const_iterator ret(*this);

    operator ++ ();
    return ret;
  }

  inline
  const Bitset::const_iterator&
  Bitset::const_iterator::operator -- ()
  {
    --cbit_;
    skip_zeros_backward();
    return *this;
  }

  inline
  Bitset::const_iterator
  Bitset::const_iterator::operator -- (int)
  {
    const_iterator ret (*this);

    operator -- ();
    return ret;
  }

  inline
  bool
  Bitset::const_iterator::operator == (const const_iterator& rhs) const
  {
    return *(*this) == *rhs;
  }

  inline
  bool
  Bitset::const_iterator::operator == (const iterator& rhs) const
  {
    return *(*this) == *rhs;
  }
  
  inline
  bool
  Bitset::const_iterator::operator != (const const_iterator& rhs) const
  {
    return !(*this == rhs);
  }

  inline
  bool
  Bitset::const_iterator::operator != (const iterator& rhs) const
  {
    return !(*this == rhs);
  }

  inline
  Bitset::value_type
  Bitset::const_iterator::operator * () const
  {
    return *cbit_;
  }
  
  inline
  void
  Bitset::const_iterator::skip_zeros_forward()
  {
    precondition(bs_ != 0);

    while ((cbit_ != bs_->bit_end()) && !bs_->get_bit(cbit_))
      ++cbit_;
  }

  inline
  void
  Bitset::const_iterator::skip_zeros_backward()
  {
    precondition(bs_ != 0);

    while ((cbit_ != bs_->bit_begin()) && !bs_->get_bit(cbit_))
      --cbit_;
  }

  /*---------.
  | iterator |
  `---------*/

  // Default constructors.
  inline
  Bitset::iterator::iterator() : bs_ (0), cbit_ ()
  {
    warning("The constructor Bitset::iterator::iterator() is dangerous "
	    "and therefore should not be used.");
  }

  inline
  Bitset::iterator::iterator(const Bitset* bs)
    : bs_(bs),
      cbit_()
  {
    skip_zeros_forward();
  }

  inline
  Bitset::iterator::iterator(const Bitset* bs, const bit_iterator& cbit)
    : bs_(bs),
      cbit_(cbit)
  {
    skip_zeros_forward();
  }

  // Copy constructor.
  inline
  Bitset::iterator::iterator(const iterator& it) : bs_(it.bs_), cbit_(it.cbit_)
  {
  }

  // Operators
  inline
  const Bitset::iterator&
  Bitset::iterator::operator ++ ()
  {
    ++cbit_;
    skip_zeros_forward();
    return *this;
  }

  inline
  Bitset::iterator
  Bitset::iterator::operator ++ (int)
  {
    iterator res(*this);

    operator ++ ();
    return res;
  }

  inline
  const Bitset::iterator&
  Bitset::iterator::operator -- ()
  {
    --cbit_;
    skip_zeros_backward();
    return *this;
  }

  inline
  Bitset::iterator
  Bitset::iterator::operator -- (int)
  {
    iterator res (*this);

    operator -- ();
    return res;
  }

  inline
  bool
  Bitset::iterator::operator == (const iterator& rhs) const
  {
    return *(*this) == *rhs;
  }
  
  inline
  bool
  Bitset::iterator::operator == (const const_iterator& rhs) const
  {
    return *(*this) == *rhs;
  }
  
  inline
  bool
  Bitset::iterator::operator != (const iterator& rhs) const
  {
    return !(*this == rhs);
  }

  inline
  bool
  Bitset::iterator::operator != (const const_iterator& rhs) const
  {
    return !(*this == rhs);
  }

  inline
  Bitset::value_type
  Bitset::iterator::operator * () const
  {
    return *cbit_;
  }

  inline
  void
  Bitset::iterator::skip_zeros_forward()
  {
    precondition(bs_ != 0);

    while ((cbit_ != bs_->bit_end()) && !bs_->get_bit(cbit_))
      ++cbit_;
  }

  inline
  void
  Bitset::iterator::skip_zeros_backward()
  {
    precondition(bs_ != 0);

    while ((cbit_ != bs_->bit_begin()) && !bs_->get_bit(cbit_))
      --cbit_;
  }

  inline
  std::ostream&
  operator << (std::ostream& ostr, const Bitset& set)
  {
    return set.print(ostr);
  }

} // namespace bts
  
namespace std
{
  template <>
  void swap(utility::Bitset& lhs, utility::Bitset& rhs)
  {
    lhs.swap(rhs);
  }

  insert_iterator<utility::Bitset>::insert_iterator(utility::Bitset& x,
						    utility::Bitset::iterator)
  {
    container = &x;
  }

  insert_iterator<utility::Bitset>&
  insert_iterator<utility::Bitset>::operator = (utility::Bitset::
						const_reference value)
  {
    container->insert(value);
    return *this;
  }

  insert_iterator<utility::Bitset>&
  insert_iterator<utility::Bitset>::operator * ()
  {
    return *this;
  }

  insert_iterator<utility::Bitset>&
  insert_iterator<utility::Bitset>::operator ++ ()
  {
    return *this;
  }

  insert_iterator<utility::Bitset>&
  insert_iterator<utility::Bitset>::operator ++ (int)
  {
    return *this;
  }
}

#endif // BITSET_HXX
