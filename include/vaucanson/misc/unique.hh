// unique.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_UNIQUE_HH
# define VCSN_MISC_UNIQUE_HH

#include <list>
#include <algorithm>
#include <typeinfo>
#include <map>

namespace utility
{
  /** The namespace for the instance collection tools */
  namespace unique
  {
    /// Base class for @c uniquelist
    struct uniquelist_base
    {
      virtual ~uniquelist_base();
    };
    
    /** Simple unique list structure
     *
     * @arg @c T the type of stored values
     *
     * This structure implements a simple list structure
     * for use by the @c unique_map structure.
     */
    template<typename T>
    struct uniquelist : public std::list<T>, public uniquelist_base
    {
      ~uniquelist();
    };

    /** Canonical type map
     *
     * This structure is a helper for the @c get operator, that
     * retains associations between static types (represented by the
     * @c std::type_info structure) and a hash map of dynamic values.
     *
     * This structure is used for dynamic type instances
     * canonicalization, i.e. storage and retrieval of unique
     * instances of structural elements in Vaucanson.
     *
     * @see @c vcsn::Structure
     */
    template <class T>
    struct UniqueMap
    {
      /** Helper to make @c std::type_info into a valid key type for
	  @c std::map */
      struct ti_slot
      {
	inline ti_slot(const std::type_info& );
	const std::type_info &id;
	inline bool operator==(const ti_slot& other) const;
	inline bool operator<(const ti_slot& other) const;
      };

      /** The map type used */
      typedef std::map<ti_slot, uniquelist_base*> map_t;

      /** Access to the unique instance of this structure */
      static map_t& instance();
    protected:
      map_t map_;
      /** Constructor for the class. 
       *  It is protected so that no secondary instances may be created. 
       */
      UniqueMap(); 
      /** Destructor for the class.
       *
       * This destructor actually destroys all stored canonical
       * instances. Any further reference to the canonical values is
       * invalid.
       */
      ~UniqueMap();
    };

#define unique_map UniqueMap<int>

    struct unifiable
    {
      inline unifiable();
      inline unifiable(const unifiable&);
    private:
      template<typename T>
      friend const T& get(const T&);
      bool unique_;
    };

    /** @addtogroup utility *//** @{ */
    /** @brief The canonicalization operator
     *
     * This operator uses the @c unique_map structure to retrieve the
     * unique instance equal to the given value.
     *
     * @see @c unique_map
     */
    template<typename T>
    const T& get(const T&);

    /// Version of the canonicalization operator for pointers
    template<typename T>
    const T* get(const T*);

    /** @} */
  }

}

#include <vaucanson/misc/unique.hxx>

#endif // VCSN_MISC_UNIQUE_HH
