// unique.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_MISC_UNIQUE_HXX
# define VCSN_MISC_UNIQUE_HXX

#include <vaucanson/misc/unique.hh>

namespace utility {

  namespace unique {

    inline
    unique_map::ti_slot::TiSlot(const std::type_info& _id)
      : id(_id) {}

    inline
    bool unique_map::ti_slot::
    operator==(const unique_map::ti_slot& other) const
    {
      return id == other.id;
    }

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
    {}

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
