// container_ops.hxx
//
// VCSN_HEADER

#ifndef FUNDAMENTAL_CONTAINER_OPS_HXX
# define FUNDAMENTAL_CONTAINER_OPS_HXX

# include <algorithm>

# include <vaucanson/misc/container_ops.hh>
# include <vaucanson/fundamental/predefs.hh>

namespace vcsn
{

  template<typename S, typename T>
  typename T::iterator op_begin(const Structure<S>& s, 
				T& v)
  { 
    return v.begin(); 
  }
  
  template<typename S, typename T>
  typename T::iterator op_end(const Structure<S>& s, 
			      T& v)
  { 
    return v.end(); 
  }

  template<typename S, typename T>
  typename T::const_iterator op_begin(const Structure<S>& s,
				      const T& v)
  { 
    return v.begin(); 
  }

  template<typename S, typename T>
  typename T::const_iterator op_end(const Structure<S>& s, 
				    const T& v)
  { 
    return v.end(); 
  }

  template<typename S, typename T>
  typename T::reverse_iterator op_rbegin(const Structure<S>& s, 
					 T& v)
  { 
    return v.rbegin(); 
  }

  template<typename S, typename T>
  typename T::reverse_iterator op_rend(const Structure<S>& s, 
				       T& v)
  { 
    return v.rend(); 
  }

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rbegin(const Structure<S>& s,
					       const T& v)
  { 
    return v.rbegin(); 
  }

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rend(const Structure<S>& s,
					     const T& v)
  { 
    return v.rend(); 
  }

  template<typename S, typename T>
  bool op_empty(const Structure<S>& s,
		const T& v)
  { 
    return v.empty(); 
  }
    
  template<typename S, typename T>
  size_t op_size(const Structure<S>& s, 
		 const T& v)
  { 
    return v.size(); 
  }
    
  template<typename S, typename T, typename U>
  bool op_contains_e(const Structure<S>& s, const T& v, 
		     const U& c)
  { 
    return std::find(v.begin(), v.end(), c) != v.end(); 
  }
  
  template<typename S, typename T, typename U>
  void op_insert(const Structure<S>& s, T& v,
		 const U& c)
  { 
    v.insert(c); 
  }

  template<typename S, typename T>
  bool op_is_finite(const Structure<S>& s,
		    const T& a)
  { 
    return false; 
  }
      
} // vcsn


#endif // FUNDAMENTAL_CONTAINER_OPS_HXX

