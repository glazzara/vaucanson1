#ifndef UTILITY_UNIQUE_HH
# define UTILITY_UNIQUE_HH

#include <list>
#include <algorithm>
#include <typeinfo>
#include <map>

namespace utility
{
  /** The namespace for the instance collection tools */
  namespace unique
  {
    /** Base class for @c uniquelist */
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
    struct unique_map
    {
      /** Helper to make @c std::type_info into a valid key type for @c std::map */
      struct ti_slot
      {
	ti_slot(const std::type_info& );
	const std::type_info &id;
	bool operator==(const ti_slot& other) const;
	bool operator<(const ti_slot& other) const;
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
      unique_map(); 
      /** Destructor for the class.
       *
       * This destructor actually destroys all stored canonical
       * instances. Any further reference to the canonical values is
       * invalid.
       */
      ~unique_map();
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

    template<typename T>
    struct uniquified
    { 
      uniquified(const T&);
      uniquified(const uniquified&);
      operator const T& () const;
    protected:
      const T& r_;
    };

    template<typename T>
    uniquified<S> avoid_uniquify(const T&);
    template<typename T>
    uniquified<S> avoid_uniquify(const T*);

    /** @} */
  }

}

#include <vaucanson/misc/unique.hxx>

#endif
