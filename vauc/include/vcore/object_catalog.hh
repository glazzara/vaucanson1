/****************************
 * <vcore/object_catalog.hh> *
 ****************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef OBJECT_CATALOG_HH
# define OBJECT_CATALOG_HH

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

      bool set(Symbol id_, Object obj);

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

#endif
