// ref.hh
//
// VCSN_HEADER

#ifndef UTILITY_REF_HH
#define UTILITY_REF_HH

namespace utility
{

  template<typename T>
  class ref
  {
  public:
    typedef T element_type;

    ~ref();

    ref(T* p);

    ref(const ref<T>& r);

    template<typename Y>
    ref& operator=(const ref<Y>& r);

//     ref(const ref& r);

    ref& operator=(const ref& r);

    void reset(T* p = 0);

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    
    long& ref_count() const;
    bool unique() const;

    bool bound() const;
    ref& swap(ref& other);

  protected:
    
    T*		data_;
    long*	count_;

    void dispose();
    void share(T* rdata, long *rcount);
    
  };


} // utility


#define REF_OP(Op)						\
template<typename T, typename U>				\
static inline bool operator Op(const utility::ref<T>& a, 	\
			       const utility::ref<U>& b);	


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
  void swap(utility::ref<T>& a, utility::ref<U>& b);

  template<typename T>
  void swap(utility::ref<T>& a, utility::ref<T>& b);
} // std

# include <vaucanson/misc/ref.hxx>

#endif
