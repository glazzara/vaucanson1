// ref.hxx
//
// VCSN_HEADER

#ifndef UTILITY_REF_HXX
#define UTILITY_REF_HXX

# include <vaucanson/misc/ref.hh>

namespace utility
{


    template<typename T>
    ref<T>::~ref() 
    { dispose(); }

    template<typename T>
    ref<T>::ref(T* p = 0) : data_(p)
    { count_ = new long(1); }

    template<typename T>
    ref<T>::ref(const ref<T>& r) 
      : data_(r.data_)
    { 
      ++*(count_ = r.count_); 
    }

//     template<typename T>
//     template<typename Y>
//     ref<T>& ref<T>::operator=(const ref<Y>& r)
//     {
//       share(r.get(), &r.ref_count());
//       return *this;
//     }
    
//     template<typename T>
//     ref<T>::ref(const ref& r)
//       : data_(r.data_)
//     { 
//       ++*(count_ = r.count_); 
//     }

    template<typename T>
     ref<T>& ref<T>::operator=(const ref& r)
     {
       share(r.data_, r.count_);
       return *this;
     }

    template<typename T>
    void ref<T>::reset(T* p) 
    {
      if (data_ == p)
	return ;
      if (! --*count_)
	delete data_;
      else
	count_ = new long;
      *count_ = 1;
      data_ = p;
    }

    template<typename T> T& ref<T>::operator*() const 
    { return *data_; }

    template<typename T> T* ref<T>::operator->() const
    { return data_; }
    
  template<typename T> T* ref<T>::get() const
  { return data_; }
    
  template<typename T> long& ref<T>::ref_count() const
  { return *count_; }
  
  template<typename T> bool ref<T>::unique() const
  { return *count_ == 1; }

  template<typename T> bool ref<T>::bound() const
  { return data_; }

  template<typename T> ref<T>& ref<T>::swap(ref& other)
  {
    std::swap(data_, other.data_);
    std::swap(count_, other.count_);
    return *this;
  }

  
  template<typename T>
  void ref<T>::dispose()
  {
    if (! --*count_)
      {
	delete data_;
	delete count_;
      }
  }
  
  template<typename T>
  void ref<T>::share(T* rdata, long *rcount) 
  {
    if (count_ != rcount)
      {
	++*rcount;
	dispose();
	data_ = rdata;
	count_ = rcount;
      }
  }
  
  
  
} // utility


#define REF_OP(Op)						\
template<typename T, typename U>				\
static inline bool operator Op(const utility::ref<T>& a, 	\
			       const utility::ref<U>& b)	\
{ return a.get() Op b.get(); }

REF_OP(==);  
REF_OP(!=);  
REF_OP(<);  
REF_OP(>);  
REF_OP(<=);  
REF_OP(>=);  

#undef REF_OP

namespace std
{
  template<typename T, typename U>
  void swap(utility::ref<T>& a, utility::ref<U>& b)
  { (void)a.swap(b); }
  template<typename T>
  void swap(utility::ref<T>& a, utility::ref<T>& b)
  { (void)a.swap(b); }
} // std

#endif
