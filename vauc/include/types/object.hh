/**********************
 * <types/object.hh> *
 **********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef TYPES_OBJECT_HH
# define TYPES_OBJECT_HH

# include <typeinfo>

namespace vcsn
{
  namespace vauc
  { 

    // maintenance stuff below...
    struct slot_base
    {
      virtual				~slot_base();
      virtual slot_base*		clone() const    = 0;
      virtual const std::type_info&	cpp_type() const = 0;
    };
    
    template<typename T>
    struct slot : public slot_base
    {
      slot(const T& init);

      virtual const std::type_info&	cpp_type() const;
      virtual slot_base*		clone() const;

      T data_;
    };
    
    /*--------.
    | Objects |
    `--------*/
    // these actually are *references* to objects. But they are smart.

    class Object
    {
    public:

      // constructors & destructor
      Object();
      Object(const Object& other);

      template<typename T>
      Object(const T& t);

      ~Object();

      // swap & assignment
      Object& swap(Object& other);

      template<typename T>
      Object& operator=(const T& other);

      Object& operator=(const Object& other);

      /*---------.
      | services |
      `---------*/

      // return true if the reference actually points to something
      bool bound() const;

      // give the c++ type of the data pointed to
      const std::type_info& cpp_type() const;

      // get the actual data. The real type is needed
      // to achieve the operation.
      template<typename T>
      T* cast() const;
      
      template<typename T>
      T* cast(const T*) const;

//       // same as before, but on const Objects.
//       template<typename T>
//       const T* cast() const;
    
//       template<typename T>
//       const T* cast(const T* nullptr) const;


      // reference count of the object
      long ref_count() const;

      // data cloning
      Object clone() const;

    protected :

      Object(slot_base* p);

      void share(slot_base* otherlink, long *othercount);
      void dispose();


      friend bool operator==(const Object& lhs, const Object& rhs);
      friend bool operator!=(const Object& lhs, const Object& rhs);
      friend bool operator<(const Object& lhs, const Object& rhs);

    protected :
      slot_base*	slot_;
      long*		count_;
    };

  } // vauc
} // vcsn

#include <types/object.hxx>

#endif
