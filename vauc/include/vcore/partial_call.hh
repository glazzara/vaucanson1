// partial_call.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_VAUC_INCLUDE_VCORE_PARTIAL_CALL_HH
# define VCSN_VAUC_INCLUDE_VCORE_PARTIAL_CALL_HH


#include <vcore/callable.hh>

#include <utility>
#include <functional>

namespace vcsn
{
  namespace vauc
  {
    class PartialCall
      : public FunctionImpl
    {
    public:
      PartialCall(Callable c);
      PartialCall(const PartialCall& other);
      PartialCall();

      void append_arg(Object arg);
      void append_args(const std::vector<Object>& args);

      virtual const sig_t& signature() const;

      virtual Object call(Env& context,
			  const std::vector<Object>& args) const;

      virtual std::string return_type(const sig_t& sig) const;

      virtual const std::string& description() const;

      virtual const std::string& origin() const;

      PartialCall& operator=(const PartialCall& other);

      virtual ~PartialCall();

    protected:
      Callable c_;
      std::vector<Object> partial_args_;
      std::vector<std::string> partial_sig_;
      std::string description_;
      std::string origin_;
    };

    //    bool operator<(const Callable& lhs, const Callable& rhs);

    struct PartialCallCompare
    {
      bool operator()(const PartialCall& lhs,
		      const PartialCall& rhs) const;
    };

  }
}

#endif // ! VCSN_VAUC_INCLUDE_VCORE_PARTIAL_CALL_HH
