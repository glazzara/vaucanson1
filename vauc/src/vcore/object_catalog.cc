/**************************
 * core/object_catalog.cc *
 **************************/
// $Id$

/* this file is part of the Vaucanson project */

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
	map_[Symbol(i->first.name())] = i->second;
    }

    std::list<Symbol>
    ObjectCatalog::merge(const ObjectCatalog& other)
    {
      std::list<Symbol> l;

      for (map_t::const_iterator i = other.map_.begin();
	   i != other.map_.end();
	   ++i)
	{
	  Symbol id = i->first.name();
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
      map_t::const_iterator i = map_.find(Symbol(id.name()));
      assert(i != map_.end());
      return i->second;
    }

    bool ObjectCatalog::contains(Symbol id) const
    {
      return map_.find(Symbol(id.name())) != map_.end();
    }


    bool 
    ObjectCatalog::set(Symbol id_, Object obj)
    {
      // namespace shift
      Symbol id = id_.name();

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
      map_t::iterator i = map_.find(Symbol(id.name()));
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

