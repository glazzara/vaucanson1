/***************************
 * <vaucanson/misc/ref.hh> *
 ***************************/
// $Id$

/* this file is par of the Vaucanson project */
#ifndef UTILITY_REF_HH
#define UTILITY_REF_HH

namespace utility
{

  template<typename T>
  class ref
  {
  public:
    typedef T element_type;

    ~ref() { dispose(); }

    ref(T* p = 0) : data_(p)
    { count_ = new long(1); }

    //    template<typename Y>
    ref(const ref<T>& r) 
      : data_(r.data_)
    { 
      ++*(count_ = r.count_); 
    }

    template<typename Y>
    ref& operator=(const ref<Y>& r)
    {
      share(r.data_, r.count_);
      return *this;
    }

//     ref(const ref& r)
//       : data_(r.data_)
//     { 
//       ++*(count_ = r.count_); 
//     }

     ref& operator=(const ref& r)
     {
       share(r.data_, r.count_);
       return *this;
     }

    void reset(T* p = 0) 
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

    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    T* get() const { return data_; }
    
    long ref_count() const { return *count_; }
    bool unique() const { return *count_ == 1; }

    bool bound() const { return data_; }

    ref& swap(ref& other)
    {
      std::swap(data_, other.data_);
      std::swap(count_, other.count_);
      return *this;
    }

  protected:
    
    T*		data_;
    long*	count_;

    void dispose()
    {
      if (! --*count_)
	{
	  delete data_;
	  delete count_;
	}
    }

    void share(T* rdata, long *rcount) 
    {
      if (count_ != rcount)
	{
	  ++*rcount;
	  dispose();
	  data_ = rdata;
	  count_ = rcount;
	}
    }
    
  };


}


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
}

#endif
