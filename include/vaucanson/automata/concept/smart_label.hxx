// smart_label.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_CONCEPT_SMART_LABEL_HXX_
# define VCSN_AUTOMATA_CONCEPT_SMART_LABEL_HXX_

namespace vcsn
{

  template <typename T>
  struct SmartLabel_ref_inc
  {
    SmartLabel_ref_inc (const SmartLabel<T>&)
    { }

    int operator() (SmartLabel<T>& sl)
    {
      return sl.ref_inc ();
    }
  };

  /*-----------`
  | SmartLabel |
  \-----------*/

  template <typename T>
  inline
  SmartLabel<T>::SmartLabel(const T& l)
    : value_(l),
      ref_(1)
  { }

  template <typename T>
  inline
  const T&
  SmartLabel<T>::value() const
  {
    return value_;
  }

  template <typename T>
  inline
  int
  SmartLabel<T>::ref() const
  {
    return ref_;
  }

  template <typename T>
  inline
  int
  SmartLabel<T>::ref_dec()
  {
    return --ref_;
  }

  template <typename T>
  inline
  int
  SmartLabel<T>::ref_inc()
  {
    return ++ref_;
  }


 /*---------------------`
  | SmartLabelContainer |
  \--------------------*/

  template <typename T>
  typename SmartLabelContainer<T>::hlabel_t
  SmartLabelContainer<T>::insert (const T& l)
  {
    typename label_container_t::iterator i = data_.find (l);

    if (i != data_.end ())
    {
      data_.modify (i, SmartLabel_ref_inc<T> (*i));
      return hlabel_t (&*i);
    }
    else
      return hlabel_t (&*data_.insert (SmartLabel<T> (l)).first);
  }

} // End of namespace vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_SMART_LABEL_HXX_ //
