/**********************
 * <types/object.hxx> *
 **********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef TYPES_OBJECT_HXX
#define TYPES_OBJECT_HXX

#include <types/object.hh>
#include <functional>
#include <algorithm>

namespace vcsn
{
  namespace vauc
  { 

    /*-------------.
    | slot methods |
    `-------------*/

    inline slot_base::~slot_base()
    {} 

    template<typename T>
    inline slot<T>::slot(const T& init)
      : data_(init)
    {}

    template<typename T>
    inline slot_base* slot<T>::clone() const
    {
      return new slot(data_);
    }

    template<typename T>
    inline const std::type_info& slot<T>::cpp_type() const
    {
      return typeid(T);
    }

    /*-------.
    | Object |
    `-------*/

    // constructors & destructor
    inline Object::Object() 
      : slot_(NULL),
	count_(new long(1))
    {}
    
    inline Object::Object(const Object& other)
      : slot_(other.slot_)
    {
      ++*(count_ = other.count_); 
    }
    
    template<typename T>
    inline Object::Object(const T& t)
      : slot_(new slot<T>(t)),
	count_(new long(1))
    {}
    
    inline Object::~Object() 
    { 
      dispose(); 
    }
    
    // swap & assignment
    inline Object& 
    Object::swap(Object& other)
    { 
      std::swap(slot_, other.slot_);
      std::swap(count_, other.count_);
      return *this;
    }
    
    inline Object& 
    Object::operator=(const Object& other)
    {
      share(other.slot_, other.count_);
      return *this;
    }

    template<typename T>
    inline Object& 
    Object::operator=(const T& other)
    {
      if (&other == this->cast<T>())
	return *this;
      if (--*count_ == 0)
	delete slot_;
      else
	count_ = new long;
      slot_   = new slot<T>(other);
      *count_ = 1;
      return *this;
    }

    /*---------.
    | services |
    `---------*/

    // return true if the reference actually points to something
    inline bool 
    Object::bound() const
    { 
      return (NULL != slot_);
    }

    // give the c++ type of the data pointed to
    inline const std::type_info& 
    Object::cpp_type() const
    { 
      return slot_ ? slot_->cpp_type() : typeid(void); 
    }
    
    // give the reference count
    inline long 
    Object::ref_count() const 
    { 
      return *count_; 
    }
    
    // get the actual data. The real type is needed
    // to achieve the operation.
    template<typename T>
    inline T* 
    Object::cast() const
    { 
      if (!slot_ || (slot_->cpp_type() != typeid(T)))
	return NULL;
      return & static_cast<slot<T>*>(slot_)->data_;
    }

    template<typename T>
    inline T* 
    Object::cast(const T*) const
    { 
      return this->cast<T>(); 
    }

//     template<typename T>
//     inline const T*
//     Object::cast() const
//     { 
//       if (!slot_ || (slot_->cpp_type() != typeid(T)))
// 	return NULL;
//       return & static_cast<const slot<T>*>(slot_)->data;
//     }

//     template<typename T>
//     const T* 
//     Object::cast(const T*) const
//     { 
//       return this->cast<T>(); 
//     }
    

    inline Object 
    Object::clone() const 
    { 
      slot_base* p = slot_;
      
      if (p != NULL) 
	p = p->clone();
      return Object(p);
    }
      
    /*----------------.
    | Using slot_base |
    `----------------*/
    inline Object::Object(slot_base* p)
      : slot_(p),
	count_(new long(1))
    {}
    
    inline void 
    Object::share(slot_base* otherlink, long *othercount)
      {
	if (count_ != othercount)
	  {
	    ++*othercount;
	    dispose();
	    slot_ = otherlink;
	    count_ = othercount;
	  }
      }

    inline void 
    Object::dispose()
    {
      if (--*count_ == 0)
	  {
	    delete slot_;
	    delete count_;
	  }
    }


    inline bool operator==(const Object& lhs, const Object& rhs)
    { 
      return lhs.slot_ == rhs.slot_; 
    }

    inline bool operator!=(const Object& lhs, const Object& rhs)
    { 
      return lhs.slot_ != rhs.slot_; 
    }

    inline bool  operator<(const Object& lhs, const Object& rhs)
    { 
      return std::less<const slot_base*>()(lhs.slot_, rhs.slot_); 
    }

    inline bool  operator>=(const Object& lhs, const Object& rhs)
    { 
      return !(lhs < rhs); 
    }

    inline bool operator<=(const Object& lhs, const Object& rhs)
    { 
      return (lhs < rhs) || (lhs == rhs); 
    }

    inline bool operator>(const Object& lhs, const Object& rhs)
    { 
      return lhs != rhs && !(lhs < rhs); 
    }





  } // vauc
} // vcsn


namespace std
{
  template<>
  inline void swap(vcsn::vauc::Object& a, vcsn::vauc::Object& b)
  { 
    a.swap(b); 
  }

} // std

#endif
