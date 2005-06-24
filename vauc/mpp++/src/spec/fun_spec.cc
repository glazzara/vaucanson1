// fun_spec.cc: this file is part of the Vaucanson project.
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
# include "spec/fun_spec.hh"

# include <list>
# include <string>
# include <vector>

# include "spec/cpp_code.hh"

namespace spec 
{
  FunSig::FunSig()
  {}

  FunSig::FunSig(const FunSig& other)
  {
    this->args = other.args;
    this->call = other.call;
  }

  const std::string
  FunSig::to_str() const
  {
    std::string str;

    for (args_t::const_iterator a = this->args.begin(); a != this->args.end();)
      {
	str += (*a).second;
	++a;
	if (a != this->args.end())
	  str += "->";
      }
    return str;
  }

  FunSpec::FunSpec(const std::string&		name, 
		   const signatures_t&	        signatures,
		   const param_set_t&		parameters,
		   const std::string&		prelude,
		   const std::string&		postlude,
		   const std::string&		description) 
  {
    description_ = description;
    param_ = parameters;
    sigs_ = signatures;
    param_value_["FUN_NAME"] = name;
    param_value_["PRELUDE"]  = prelude;
    param_value_["POSTLUDE"] = postlude;
    name_ = param_value_.find("FUN_NAME");
    postlude_ = param_value_.find("POSTLUDE");
    prelude_ = param_value_.find("PRELUDE");
  }

  const std::string
  FunSpec::name() const
  {
    return name_->second;
  }

  const FunSpec::signatures_t&
  FunSpec::signatures() const
  {
    return sigs_;
  }

  const FunSpec::param_set_t&
  FunSpec::parameters() const
  {
    return param_;
  }

  const std::string&
  FunSpec::description() const
  {
    return description_;
  }

  const std::string
  FunSpec::prelude() const
  {
    return prelude_->second;
  }

  const std::string
  FunSpec::postlude() const
  {
    return postlude_->second;
  }

  const FunSpec::param_value_t&
  FunSpec::fun_param() const
  {
    return param_value_;
  }
  
  const FunSpec::signature_t&
  FunSpec::get_signature(const args_t& args) const
  {
    std::vector<signatures_t::const_iterator> selected;

    for (signatures_t::const_iterator s = sigs_.begin(); s != sigs_.end(); ++s)
      {
	if ((*s).args.size() == args.size())
	  {
	    args_t::const_iterator as = (*s).args.begin();
	    for (args_t::const_iterator a = args.begin(); 
		 ((as != args.end()) && (a != args.end())); ++a, ++as)
	      if ((*as).second != (*a).second)
		  break;
	  }
	selected.push_back(s);
      }
    if (selected.size() > 1)
      {
	std::cerr << "fun_spec::get_signature : more than one signature found."
		  << std::endl;
	exit(EXIT_FAILURE);
      }
    else if (selected.size() == 0)
      {
	std::cerr << "fun_spec::get_signature : no signature found." << std::endl;
	exit(EXIT_FAILURE);
      }
    return *selected[0];
  }

} // spec

namespace std 
{
  
  std::ostream& 
  operator<<(std::ostream& o, const spec::FunSpec& cs)
  {
    o << "FunSpec printer" << std::endl;
    return o;
  }

} // std

