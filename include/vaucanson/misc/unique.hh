#ifndef UTILITY_UNIQUE_HH
# define UTILITY_UNIQUE_HH

#include <list>
#include <typeinfo>
#include <map>

/* @file unique.hh
 * Declarations for the type canonicalization tools.
 */

/** @addtogroup Utility *//** @{ */

/**
 * @brief The namespace for utility constructs.
 *
 * This namespace holds all constructs that are not
 * Vaucanson-specific.
 */
namespace utility
{

  /** The namespace for the instance collection tools. */
  namespace unique
  {
    /** Generic hash operator.
     *
     * This trait must be specialized for any type that has dynamic
     * information in addition to its static type information
     */
    template<typename T>
    struct hash
    {
      unsigned operator()(const T&) const;
    };

    /** Base class for @c hashmap */
    struct hashmap_base
    {
      virtual ~hashmap_base();
    };
    
    /** Simple hash map structure
     *
     * @arg @c T the type of stored values
     * @arg @c hash_size the size of the hash table
     *
     * This structure implements a simple hash map structure
     * for use by the @c unique_map structure.
     */
    template<typename T, unsigned hash_size>
    struct hashmap : public hashmap_base
    {
      /** The main access operator.
       *
       * This operator retrieves the canonical instance of a value,
       * creating one if necessary.
       *
       * It uses the @c hash trait and the standard equality operator
       * (==) for the value type.
       */
      const T& get_or_insert(const T&);

      ~hashmap();
    protected:
      std::list<T> vec_[hash_size];
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
      typedef std::map<ti_slot, hashmap_base*> map_t;

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
    
    /** The canonicalization operator
     *
     * This operator uses the @c unique_map structure to retrieve the
     * unique instance equal to the given value.
     *
     * @see @c unique_map
     */
    template<typename T>
    const T& get(const T&);
    

  }




}

/** @} */

#include <vaucanson/misc/unique.hxx>

#endif
