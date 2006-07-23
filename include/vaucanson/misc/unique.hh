// unique.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_MISC_UNIQUE_HH
# define VCSN_MISC_UNIQUE_HH

/**
 * @file unique.hh
 * Declarations for the type canonicalization tools.
 */

# include <list>
# include <algorithm>
# include <typeinfo>
# include <map>

namespace vcsn
{
  namespace misc
  {
    /** The namespace for the instance collection tools */
    namespace unique
    {
      /// Base class for @c uniquelist
      template <class T>
      struct UniqueListBase
      {
	  virtual ~UniqueListBase ();
      };

      typedef UniqueListBase<int> uniquelist_base;

      /** Simple unique list structure
       *
       * @arg @c T the type of stored values
       *
       * This structure implements a simple list structure
       * for use by the @c unique_map structure.
       */
      template <typename T>
      struct uniquelist : public std::list<T>, public uniquelist_base
      {
	  ~uniquelist ();
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
	  template <class U>
	  struct TiSlot
	  {
	      TiSlot (const std::type_info& );
	      const std::type_info &id;
	      bool operator== (const TiSlot& other) const;
	      bool operator< (const TiSlot& other) const;
	  };

	  typedef TiSlot<int> ti_slot;

	  /** The map type used */
	  typedef std::map<ti_slot, uniquelist_base*> map_t;

	  /** Access to the unique instance of this structure */
	  static map_t& instance ();
	protected:
	  map_t map_;
	  /** Constructor for the class.
	   *  It is protected so that no secondary instances may be created.
	   */
	  UniqueMap ();
	  /** Destructor for the class.
	   *
	   * This destructor actually destroys all stored canonical
	   * instances. Any further reference to the canonical values is
	   * invalid.
	   */
	  ~UniqueMap ();
      };

      typedef UniqueMap<int> unique_map;

      struct unifiable
      {
	  inline unifiable ();
	  inline unifiable (const unifiable&);
	private:
	  template <typename T>
	  friend const T& get (const T&);
	  bool unique_;
      };

      /** @addtogroup misc *//** @{ */
      /** @brief The canonicalization operator
       *
       * This operator uses the @c unique_map structure to retrieve the
       * unique instance equal to the given value.
       *
       * @see @c unique_map
       */
      template <typename T>
      const T& get (const T&);

      /// Version of the canonicalization operator for pointers
      template <typename T>
      const T* get (const T*);

      /** @} */
    }

  } // misc
} // vcsn

# ifndef INTERFACE_ONLY
#  include <vaucanson/misc/unique.hxx>
# endif // INTERFACE_ONLY

#endif // ! VCSN_MISC_UNIQUE_HH
