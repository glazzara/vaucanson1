// functors.hh
// 
// VCSN_HEADER

#ifndef UTILITY_FUNCTORS_HH
# define UTILITY_FUNCTORS_HH

# include <vaucanson/misc/constraints.hh>
# include <vaucanson/misc/type_constraints.hh>
# include <vaucanson/misc/numerical_constraints.hh>

namespace utility
{
  namespace op
  {
    template<typename T>
    struct default_constructor
    {
      T operator() () const;
    };

    template<typename T, typename tag>
    struct from_tag_constructor
    {
      T operator() () const;
    };

    template<typename T>
    struct infinity_generator
    {
      T operator() () const;
    };

    template<typename T>
    struct minusinfinity_generator
    {
      T operator() () const;
    };

    template<typename T>
    struct maxvalue_generator
    {
      T operator() () const;
    };

    template<typename T>
    struct minvalue_generator
    {
      T operator() () const;
    };
    
  } // op
  
    // Compose when F return bool.
    // FIXME : this is not a good way of course.
    // all functor must be compliant with unary_function
    // but we don't have enough time to update all. => version 2.
  template <typename F, typename G>
  class compose1_fun_bool
  {
  public :
    compose1_fun_bool(const F&f, const G&g);

    template <class H>
    bool operator()(const H& v) const;

  private :
    F	f_;
    G g_;
  };
    
  template <class F, class G>
  compose1_fun_bool<F, G>
  compose1_f_bool(const F& f, const G& g);

} // utility

# include <vaucanson/misc/functors.hxx>

#endif
