/**********************
 * "core/callable.cc" *
 **********************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/callable.hh>

namespace vcsn
{
  namespace vauc
  {

    const std::string& FunctionImpl::description() const
    {
      static const std::string instance = "<no description available>";
      return instance;
    }

    FunctionImpl::~FunctionImpl()
    {}

//     const std::string& FunctionImpl::origin() const
//     {
//       static const std::string instance = "~ \"no origin for this function\"";
//       return instance;
//     }

  }
}


