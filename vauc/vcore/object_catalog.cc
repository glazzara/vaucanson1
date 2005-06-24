// object_catalog.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

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
# include <vcore/object_catalog.hh>
# include <cassert>

namespace vcsn
{
  namespace vauc
  { 
    /*----------------.
    | Object catalogs |
    `----------------*/
    ObjectCatalog::ObjectCatalog() 
    {}

    ObjectCatalog::ObjectCatalog(const ObjectCatalog& other)
    {
      for (map_t::const_iterator i = other.map_.begin();
	   i != other.map_.end();
	   ++i)
	map_[Symbol(i->first.value())] = i->second;
    }

    std::list<Symbol>
    ObjectCatalog::merge(const ObjectCatalog& other)
    {
      std::list<Symbol> l;

      for (map_t::const_iterator i = other.map_.begin();
	   i != other.map_.end();
	   ++i)
	{
	  Symbol id = i->first.value();
	  if (map_.find(id) != map_.end())
	    l.push_back(id);
	  else
	    map_[id] = i->second;
	}
	
      return l;
    }

    Object 
    ObjectCatalog::operator[](Symbol id) const
    {
      map_t::const_iterator i = map_.find(Symbol(id.value()));
      assert(i != map_.end());
      return i->second;
    }

    bool ObjectCatalog::contains(Symbol id) const
    {
      return map_.find(Symbol(id.value())) != map_.end();
    }


    bool 
    ObjectCatalog::set(Symbol id_, Object obj)
    {
      // namespace shift
      Symbol id = id_.value();

      map_t::iterator i = map_.find(id);

      bool b = false;
      if (i != map_.end())
	b = true;

      map_[id] = obj;
      return b;
    }

    bool 
    ObjectCatalog::erase(Symbol id)
    {
      map_t::iterator i = map_.find(Symbol(id.value()));
      if (i == map_.end())
	return false;
	
      map_.erase(i);
      return true;
    }

    const ObjectCatalog::map_t& 
    ObjectCatalog::contents() const
    { return map_; }

    ObjectCatalog& 
    ObjectCatalog::swap(ObjectCatalog& other)
    { 
      map_.swap(other.map_); 
      return *this;
    }

    void ObjectCatalog::clear()
    {
      map_.clear();
    }

  }
}

