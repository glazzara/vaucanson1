/**********************
 * <vcore/callable.hh> *
 **********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_CALLABLE_HH
# define CORE_CALLABLE_HH

#include <string>
#include <vector>

#include <types/object.hh>

#include <vaucanson/misc/ref.hh>

namespace vcsn
{
  namespace vauc
  {
    class Env;

    class FunctionImpl
    {
    public:
      typedef std::vector<std::string> sig_t;

      // return the signature for the function
      virtual const sig_t& signature() const = 0;

      // attempt a call, should raise an exception if the call
      // is invalid.
      virtual Object call(Env& context,
			  const std::vector<Object>& args) const = 0;

      // return the return type expected for a given set
      // of arguments. While most function will either
      //   1) always return the same name, independent of the argument list
      // or
      //   2) always return "", the "any" type
      // there are cases where the return type is linked to the
      // argument types.
      virtual std::string return_type(const sig_t& sig) const = 0;

      // a description for what the function does.
      virtual const std::string& description() const;

      // an interpreter script that evaluates to a callable for this
      // functionimpl.
      virtual const std::string& origin() const = 0;

      virtual ~FunctionImpl();

    };

    class Callable 
      : public utility::ref<FunctionImpl>
    {
    public:
      Callable(FunctionImpl* p = 0)
	: utility::ref<FunctionImpl>(p)
      {}

      Callable(const Callable& other)
	: utility::ref<FunctionImpl>(other)
      {}

      Callable& operator=(const Callable& other)
      {
	share(other.data_,other.count_);
	//	utility::ref<FunctionImpl>::operator=(other);
	return *this;
      }

      Callable& swap(utility::ref<FunctionImpl>& other)
      {
	utility::ref<FunctionImpl>::swap(other);
	return *this;
      }

      typedef std::vector<std::string> sig_t;
      const sig_t& signature() const
      {
	return get()->signature();
      }
      
      Object call(Env& context,
		  const std::vector<Object>& args) const
      { 
	return get()->call(context, args); 
      }

      std::string return_type(const sig_t& sig) const
      {
	return get()->return_type(sig);
      }

      const std::string& description() const
      {
	return get()->description();
      }

      const std::string& origin() const
      {
	return get()->origin();
      }

      bool operator==(const Callable& other) const
      {
	return signature() == other.signature();
      }

    protected:
      void reset(FunctionImpl *p) 
      {}

    };
		      


  }
}


// #include <functional>

// namespace std
// {



//   template <>
//   struct less<vcsn::vauc::Callable>
//   {
//     bool  
//     operator()(const vcsn::vauc::Callable& lhs, 
// 	       const vcsn::vauc::Callable& rhs)
//     {
//       return lhs.signature() < rhs.signature();
//     }
//   };


// } // std


#endif
