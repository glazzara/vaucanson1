// functors.hxx
// 
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef UTILITY_FUNCTORS_HXX
# define UTILITY_FUNCTORS_HXX

# include <vaucanson/misc/functors.hh>
# include <vaucanson/misc/constraints.hh>
# include <vaucanson/misc/type_constraints.hh>
# include <vaucanson/misc/numerical_constraints.hh>

namespace utility
{
  namespace op
  {
    template<typename T>
    T default_constructor<T>::operator() () const { return T(); }
    

    template<typename T, typename tag>
    T from_tag_constructor<T, tag>::operator() () const 
    { 
      return T(tag()); 
    }
    
    template<typename T>
    T infinity_generator<T>::operator() () const  
    { 
      UTILITY_REQUIRE_CONCEPT(T, concepts, HasInfinity);
      return std::numeric_limits<T>::infinity();
    }
    
    template<typename T>
    T minusinfinity_generator<T>::operator() () const  
    { 
      UTILITY_REQUIRE_CONCEPT(T, concepts, HasInfinity);
      UTILITY_REQUIRE_CONCEPT(T, concepts, IsSigned);
      return - (std::numeric_limits<T>::infinity());
    }
    
    template<typename T>
    T maxvalue_generator<T>::operator() () const  
    { 
      UTILITY_REQUIRE_CONCEPT(T, concepts, BoundedType);
      return std::numeric_limits<T>::max();
    }
    
    template<typename T>
    T minvalue_generator<T>::operator() () const  
    { 
      UTILITY_REQUIRE_CONCEPT(T, concepts, BoundedType);
      return std::numeric_limits<T>::min();
    }
        
  } // op
  
    // Compose when F return bool.
    // FIXME : this is not a good way of course.
    // all functor must be compliant with unary_function
    // but we don't have enough time to update all. => version 2.

  template <typename F, typename G>
  compose1_fun_bool<F, G>::compose1_fun_bool(const F&f, const G&g) :
    f_(f), g_(g)
  {}
  
  template <typename F, typename G>
  template <class H>
  bool compose1_fun_bool<F, G>::operator()(const H& v) const
  {
    return f_(g_(v));
  }

    
  template <class F, class G>
  compose1_fun_bool<F, G>
  compose1_f_bool(const F& f, const G& g)
  {
    return compose1_fun_bool<F, G>(f, g);
  }

} // utility



#endif
