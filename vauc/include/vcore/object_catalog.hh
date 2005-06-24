// object_catalog.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_VCORE_OBJECT_CATALOG_HH
# define VCSN_VAUC_INCLUDE_VCORE_OBJECT_CATALOG_HH

#include <algorithm>
#include <types/object.hh>
#include <types/symbol.hh>
#include <map>
#include <utility>
#include <list>

namespace vcsn
{
  namespace vauc
  { 
    /*----------------.
    | Object catalogs |
    `----------------*/
    class ObjectCatalog
    {
    public:
      typedef std::map<Symbol, Object> map_t;

    protected:
      map_t		map_;

    public:
      ObjectCatalog();

      ObjectCatalog(const ObjectCatalog& other);

      // returns the list of conflicting symbols
      std::list<Symbol> merge(const ObjectCatalog& other);

      Object operator[](Symbol id) const;

      bool contains(Symbol id) const;

      bool structure(Symbol id_, Object obj);

      bool erase(Symbol id);

      const map_t& contents() const;

      ObjectCatalog& swap(ObjectCatalog& other);

      void clear();

    };
  }
}


namespace std
{

  template<>
  inline void swap(vcsn::vauc::ObjectCatalog& a, vcsn::vauc::ObjectCatalog& b)
  {
    a.swap(b);
  };

}

#endif // ! VCSN_VAUC_INCLUDE_VCORE_OBJECT_CATALOG_HH
