// boost_support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_SUPPORT_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_SUPPORT_HXX

# include <vaucanson/automata/implementation/boostg/boostg_support.hh>

namespace vcsn
{
  namespace misc
  {
    /*------------------.
    | SupportIterator.  |
    `------------------*/
    //Specialization for std::vector<handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U, V> > >
    template<typename T, typename U, typename V>
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::SupportIterator (const container_t* c,
		       vector_iterator i)
      : container_(c)
    {
      if (i != c->end())
      {
	i_ = i++;
	next_ = i;
      }
      else
      {
	i_ = i;
	next_ = i;
      }
    }

    template<typename T, typename U, typename V>
    typename SupportIterator<std::vector<handler<transition_h,
			    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >::data_type
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::operator* () const
    {
      return data_type(i_->value());
    }

    template<typename T, typename U, typename V>
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >&
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::operator++ ()
    {
      std::cout << "operator++ ameliore - multi_index" << std::endl;
      if (next_ != container_->end())
	i_ = next_++;
      else
	i_ = next_;
      return *this;
    }

    template<typename T, typename U, typename V>
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >&
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::operator-- ()
    {
      --i_;
      return *this;
    }

    template<typename T, typename U, typename V>
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::operator++ (int)
    {
      SupportIterator<std::vector<handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U, V> > > > tmp = *this;
      ++(*this);
      return tmp;
    }

    template<typename T, typename U, typename V>
    bool
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::operator!= (const SupportIterator& o) const
    {
      return o.i_ != i_;
    }

    template<typename T, typename U, typename V>
    bool
    SupportIterator<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }

    //Specialization for std::vector<handler<state_h, unsigned*> >
    inline //template <>
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::SupportIterator (const container_t* c,
										  int i)
      : current_(i), container_size_(c->size()), container_(c)
    {}

    inline //template <>
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::data_type
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::operator* () const
    {
      return data_type((*container_)[current_]);
    }

    inline //template <>
    SupportIterator<std::vector<handler<state_h, unsigned*> > >&
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::operator++ ()
    {
      if (container_->size() == container_size_)
	++current_;
      else
	container_size_ = container_->size();
      return *this;
    }

    inline //template <>
    SupportIterator<std::vector<handler<state_h, unsigned*> > >&
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::operator-- ()
    {
      --current_;
      return *this;
    }

    inline //template <>
    SupportIterator<std::vector<handler<state_h, unsigned*> > >
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::operator++ (int)
    {
      SupportIterator<std::vector<handler<state_h, unsigned*> > > tmp = *this;
      ++(*this);
      return tmp;
    }

    inline //template <>
    bool
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::operator!= (const SupportIterator& o) const
    {
      return o.current_ != current_;
    }

    inline //template <>
    bool
    SupportIterator<std::vector<handler<state_h, unsigned*> > >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }


    /*------------------.
    | SupportIterator.  |
    `------------------*/

    //Specialization for InitialContainer.
    template <typename U, typename HState>
    SupportIterator<InitialContainer<U, HState> >
    ::SupportIterator (const container_t* c, container_iterator i)
      : container_ (c)
    {
      if (i != c->end())
      {
	i_ = i++;
	next_ = i;
      }
      else
      {
	i_ = i;
	next_ = i;
      }
    }

    template <typename U, typename HState>
    typename SupportIterator<InitialContainer<U, HState> >::key_type
    SupportIterator<InitialContainer<U, HState> >::operator* () const
    {
      return HState(i_->first.value());
    }

    template <typename U, typename HState>
    SupportIterator<InitialContainer<U, HState> >&
    SupportIterator<InitialContainer<U, HState> >::operator++ ()
    {
      if (next_ != container_->end())
	i_ = next_++;
      else
	i_ = next_;
      return *this;
    }

    template <typename U, typename HState>
    SupportIterator<InitialContainer<U, HState> >
    SupportIterator<InitialContainer<U, HState> >::operator++ (int)
    {
      SupportIterator<InitialContainer<U, HState> > tmp = *this;
      ++(*this);
      return tmp;
    }

    template <typename U, typename HState>
    bool
    SupportIterator<InitialContainer<U, HState> >::operator!= (const SupportIterator& o) const
    {
      return o.i_ != i_;
    }

    template <typename U, typename HState>
    bool
    SupportIterator<InitialContainer<U, HState> >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }



    /*----------.
    | Support.  |
    `----------*/

    /// support<InitialContainer<U, HState> is a const adapter of InitialContainer to container.
    template <class U, class HState>
    Support<InitialContainer<U, HState> >::Support (const Support& s)
      : m_ (s.m_)
    {
    }

    template <class U, class HState>
    Support<InitialContainer<U, HState> >::Support (const Support::container_t& m)
      : m_ (m)
    {
    }

    template <class U, class HState>
    unsigned
    Support<InitialContainer<U, HState> >::size () const
    {
      return m_.size ();
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::iterator
    Support<InitialContainer<U, HState> >::find (const HState& k) const
    {
      return m_.find (k);
    }

    template <class U, class HState>
    bool
    Support<InitialContainer<U, HState> >::empty () const
    {
      return m_.empty ();
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::iterator
    Support<InitialContainer<U, HState> >::begin () const
    {
      return iterator (&m_, m_.begin ());
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::iterator
    Support<InitialContainer<U, HState> >::end () const
    {
      return iterator (&m_, m_.end ());
    }

    template <class U, class HState>
    HState
    Support<InitialContainer<U, HState> >::back () const
    {
      return (*max_element (begin (), end ()));
    }

  }
}

namespace vcsn
{
  namespace misc
  {

  /*----------.
  | Support.  |
  `----------*/

    /// support<vector<U, T> > is a const adapter of std::vector to container.
    template <class T, class U, class V>
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::Support (const Support& s)
      : m_ (s.m_)
    {
    }

    template <class T, class U, class V>
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::Support (const std::vector<handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U, V> > >& m)
      : m_ (m)
    {
    }

    template <class T, class U, class V>
    unsigned
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::size () const
    {
      return m_.size ();
    }

    template <class T, class U, class V>
    typename Support<std::vector<handler<transition_h,
		    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >::iterator
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::find (const handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U, V> >& k) const
    {
      return m_.find (k);
    }

    template <class T, class U, class V>
    bool
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::empty () const
    {
      return m_.empty ();
    }

    template <class T, class U, class V>
    typename Support<std::vector<handler<transition_h,
		     boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >::iterator
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::begin () const
    {
      return iterator (&m_, m_.begin ());
    }

    template <class T, class U, class V>
    typename Support<std::vector<handler<transition_h,
		     boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >::iterator
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::end () const
    {
      return iterator (&m_, m_.end ());
    }

    template <class T, class U, class V>
    typename Support<std::vector<handler<transition_h,
		     boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >::handler_t
    Support<std::vector<handler<transition_h,
	    boost::multi_index::detail::hashed_index_iterator<T, U, V> > > >
    ::back () const
    {
      return m_.back();
    }


    /// support<vector<U, T> > is a const adapter of std::vector to container.
    inline
    Support<std::vector<handler<state_h, unsigned* > > >
    ::Support (const std::vector<handler<state_h, unsigned* > >& m)
      : m_ (m)
    {
    }

    inline
    unsigned
    Support<std::vector<handler<state_h, unsigned* > > >
    ::size () const
    {
      return m_.size ();
    }

    inline
    Support<std::vector<handler<state_h, unsigned* > > >::iterator
    Support<std::vector<handler<state_h, unsigned* > > >
    ::find (const handler<state_h, unsigned* >& k) const
    {
      if (k < m_.size())
	return iterator(&m_, k);
      else
	return iterator(&m_, m_.size());
    }

    inline
    bool
    Support<std::vector<handler<state_h, unsigned* > > >
    ::empty () const
    {
      return m_.empty ();
    }

    inline
    Support<std::vector<handler<state_h, unsigned* > > >::const_iterator
    Support<std::vector<handler<state_h, unsigned* > > >
    ::begin () const
    {
      return iterator (&m_, 0);
    }

    inline
    Support<std::vector<handler<state_h, unsigned* > > >::const_iterator
    Support<std::vector<handler<state_h, unsigned* > > >
    ::end () const
    {
      return iterator (&m_, m_.size());
    }

    inline
    Support<std::vector<handler<state_h, unsigned* > > >::handler_t
    Support<std::vector<handler<state_h, unsigned* > > >
    ::back () const
    {
      return m_.back();
    }

  }
}


#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_SUPPORT_HXX

