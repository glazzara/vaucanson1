// unique.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_MISC_UNIQUE_HXX
# define VCSN_MISC_UNIQUE_HXX

#include <vaucanson/misc/unique.hh>

namespace utility {

  namespace unique {

    template class UniqueMap<int>;
    
    template <>
    template <>
    inline
    unique_map::ti_slot::TiSlot(const std::type_info& _id) : id(_id)
    {
    }

    template <>
    template <>
    inline
    bool
    unique_map::ti_slot::
    operator==(const unique_map::ti_slot& other) const
    {
      return id == other.id;
    }

    template <>
    template <>
    inline
    bool unique_map::ti_slot::
    operator<(const unique_map::ti_slot& other) const
    {
      return id.before(other.id);
    }

    template<typename T>
    uniquelist<T>::~uniquelist()
    {}

    inline
    unifiable::unifiable() : unique_(false)
    {}

    inline
    unifiable::unifiable(const unifiable& ) : unique_(false)
    {}

    template<typename T>
    const T& get(const T& v)
    {
      if (static_cast<const unifiable&>(v).unique_)
	return v;

      unique_map::map_t& m = unique_map::instance();

      unique_map::map_t::iterator i = m.find(typeid(T));
      if (i == m.end())
	{
	  uniquelist<T> *l =
	    static_cast<uniquelist<T>* >(m[typeid(T)] = new uniquelist<T>);
	  l->push_front(v);
	  static_cast<unifiable&>(l->front()).unique_ = true;
	  return l->front();
	}
      uniquelist<T> *l =
	static_cast<uniquelist<T>*>(i->second);
      typename uniquelist<T>::const_iterator j;
      if ((j = std::find(l->begin(), l->end(), v)) == l->end())
	{
	  l->push_front(v);
	  static_cast<unifiable&>(l->front()).unique_ = true;
	  return l->front();
	}
      return *j;
    }

    template<typename T>
    const T* get(const T* v)
    {
      return & get(*v);
    }

    template <>
    inline
    uniquelist_base::~UniqueListBase() {}

    template <class T>
    typename UniqueMap<T>::map_t&
    UniqueMap<T>::instance()
    {
      static unique_map instance_;
      return instance_.map_;
    }

    template <class T>
    UniqueMap<T>::UniqueMap()
    {
    }

    template <class T>
    UniqueMap<T>::~UniqueMap()
    {
      for (typename map_t::iterator i = map_.begin();
	   i != map_.end();
	   ++i)
	delete i->second;
    }

  } // unique

} // utility

#endif // ! VCSN_MISC_UNIQUE_HXX
