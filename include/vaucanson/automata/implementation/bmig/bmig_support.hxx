// boost_support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_SUPPORT_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_SUPPORT_HXX

# include <vaucanson/automata/implementation/bmig/bmig_support.hh>

namespace vcsn
{
  namespace misc
  {
    //Specialization for std::vector<boost::shared_ptr<std::size_t> >
    inline
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::SupportIterator (const container_t* c,
										  int i)
      : current_(i), container_size_(c->size()), container_(c)
    {}

    inline
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::handler_t
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::operator* () const
    {
      return handler_t((*container_)[current_]);
    }

    inline
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >&
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::operator++ ()
    {
      if (container_->size() == container_size_)
	++current_;
      else
	container_size_ = container_->size();
      return *this;
    }

    inline
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >&
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::operator-- ()
    {
      if (container_->size() == container_size_)
	--current_;
      else
	container_size_ = container_->size();
      return *this;
    }

    inline
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::operator++ (int)
    {
      SupportIterator<std::vector<boost::shared_ptr<std::size_t> > > tmp = *this;
      ++(*this);
      return tmp;
    }

    inline
    bool
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::operator!= (const SupportIterator& o) const
    {
      return o.current_ != current_;
    }

    inline
    bool
    SupportIterator<std::vector<boost::shared_ptr<std::size_t> > >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }

    //Specialization for std::vector<boost::shared_ptr<std::size_t> >
    inline
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::SupportIterator (const container_t* c, set_iterator it)
      : current_(it), container_size_(c->size()), container_(c)
    {}

    inline
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::handler_t
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::operator* () const
    {
      return handler_t(*current_);
    }

    inline
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >&
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::operator++ ()
    {
      if (container_->size() == container_size_)
	++current_;
      else
	container_size_ = container_->size();
      return *this;
    }

    inline
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >&
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::operator-- ()
    {
      if (container_->size() == container_size_)
	--current_;
      else
	container_size_ = container_->size();
      return *this;
    }

    inline
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::operator++ (int)
    {
      SupportIterator<std::set<boost::shared_ptr<std::size_t> > > tmp = *this;
      ++(*this);
      return tmp;
    }

    inline
    bool
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::operator!= (const SupportIterator& o) const
    {
      return o.current_ != current_;
    }

    inline
    bool
    SupportIterator<std::set<boost::shared_ptr<std::size_t> > >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }

    /*------------------.
    | SupportIterator.  |
    `------------------*/

    //Specialization for vcsn::bmig::InitialContainer.
    template <typename U, typename HState>
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >
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
    typename SupportIterator<vcsn::bmig::InitialContainer<U, HState> >::handler_t
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >::operator* () const
    {
      return handler_t(i_->first);
    }

    template <typename U, typename HState>
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >&
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >::operator++ ()
    {
      if (next_ != container_->end())
	i_ = next_++;
      else
	i_ = next_;
      return *this;
    }

    template <typename U, typename HState>
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >::operator++ (int)
    {
      SupportIterator<vcsn::bmig::InitialContainer<U, HState> > tmp = *this;
      ++(*this);
      return tmp;
    }

    template <typename U, typename HState>
    bool
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >::operator!= (const SupportIterator& o) const
    {
      return o.i_ != i_;
    }

    template <typename U, typename HState>
    bool
    SupportIterator<vcsn::bmig::InitialContainer<U, HState> >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }



    /*----------.
    | Support.  |
    `----------*/

    /// support<vcsn::bmig::InitialContainer<U, HState> is a const adapter of vcsn::bmig::InitialContainer to container.
    template <class U, class HState>
    Support<vcsn::bmig::InitialContainer<U, HState> >::Support (const Support& s)
      : m_ (s.m_)
    {
    }

    template <class U, class HState>
    Support<vcsn::bmig::InitialContainer<U, HState> >::Support (const Support::container_t& m)
      : m_ (m)
    {
    }

    template <class U, class HState>
    unsigned
    Support<vcsn::bmig::InitialContainer<U, HState> >::size () const
    {
      return m_.size ();
    }

    template <class U, class HState>
    typename Support<vcsn::bmig::InitialContainer<U, HState> >::iterator
    Support<vcsn::bmig::InitialContainer<U, HState> >::find (const HState& k) const
    {
      return m_.find (k.value());
    }

    template <class U, class HState>
    bool
    Support<vcsn::bmig::InitialContainer<U, HState> >::empty () const
    {
      return m_.empty ();
    }

    template <class U, class HState>
    typename Support<vcsn::bmig::InitialContainer<U, HState> >::iterator
    Support<vcsn::bmig::InitialContainer<U, HState> >::begin () const
    {
      return iterator (&m_, m_.begin ());
    }

    template <class U, class HState>
    typename Support<vcsn::bmig::InitialContainer<U, HState> >::iterator
    Support<vcsn::bmig::InitialContainer<U, HState> >::end () const
    {
      return iterator (&m_, m_.end ());
    }

    template <class U, class HState>
    typename Support<vcsn::bmig::InitialContainer<U, HState> >::handler_t
    Support<vcsn::bmig::InitialContainer<U, HState> >::back () const
    {
      return handler_t(*max_element (begin (), end ()));
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
    inline
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::Support (const std::vector<boost::shared_ptr<std::size_t> >& m)
      : m_ (m)
    {
    }

    inline
    unsigned
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::size () const
    {
      return m_.size ();
    }

    inline
    Support<std::vector<boost::shared_ptr<std::size_t> > >::iterator
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::find (const handler<state_h, boost::shared_ptr<std::size_t>  >& k) const
    {
      if (k < m_.size())
	return iterator(&m_, k);
      else
	return iterator(&m_, m_.size());
    }

    inline
    bool
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::empty () const
    {
      return m_.empty ();
    }

    inline
    Support<std::vector<boost::shared_ptr<std::size_t> > >::const_iterator
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::begin () const
    {
      return iterator (&m_, 0);
    }

    inline
    Support<std::vector<boost::shared_ptr<std::size_t> > >::const_iterator
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::end () const
    {
      return iterator (&m_, m_.size());
    }

    inline
    Support<std::vector<boost::shared_ptr<std::size_t> > >::handler_t
    Support<std::vector<boost::shared_ptr<std::size_t> > >
    ::back () const
    {
      return handler_t(m_.back());
    }

    /// support<vector<U, T> > is a const adapter of std::set to container.
    inline
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::Support (const std::set<boost::shared_ptr<std::size_t> >& m)
      : m_ (m)
    {
    }

    inline
    unsigned
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::size () const
    {
      return m_.size ();
    }

    inline
    Support<std::set<boost::shared_ptr<std::size_t> > >::iterator
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::find (const handler<state_h, boost::shared_ptr<std::size_t>  >& k) const
    {
	return iterator(&m_, m_.find(k.value()));
    }

    inline
    bool
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::empty () const
    {
      return m_.empty ();
    }

    inline
    Support<std::set<boost::shared_ptr<std::size_t> > >::const_iterator
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::begin () const
    {
      return iterator (&m_, m_.begin());
    }

    inline
    Support<std::set<boost::shared_ptr<std::size_t> > >::const_iterator
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::end () const
    {
      return iterator (&m_, m_.end());
    }

    inline
    Support<std::set<boost::shared_ptr<std::size_t> > >::handler_t
    Support<std::set<boost::shared_ptr<std::size_t> > >
    ::back () const
    {
      //FIXME Maybe wrong! Compare pointers instead of id.
      return handler_t(*max_element (begin (), end ()));
    }


  }
}


#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_SUPPORT_HXX

