// fun_spec.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_SPEC_FUN_SPEC_HH
# define VCSN_VAUC_MPP___SRC_SPEC_FUN_SPEC_HH

# include <map>
# include <utility>
# include <list>
# include <string>
# include <iostream>

# include "spec/cpp_code.hh"

namespace spec 
{
  
  struct FunSig
  {
    FunSig();
    FunSig(const FunSig&);

    typedef std::list<std::pair<std::string, std::string> >	args_t;

    const std::string
    to_str() const;

    CppParamCode       	call;
    args_t		args;
  };
  
  class FunSpec
  {
  public:
    typedef FunSig				signature_t;
    typedef FunSig::args_t		        args_t;
    typedef CppParamCode			cpp_param_t;
    typedef cpp_param_t::param_set_t		param_set_t;
    typedef cpp_param_t::param_value_t		param_value_t;
    typedef std::list<signature_t>		signatures_t;

    FunSpec(const std::string& name, 
	    const signatures_t& signatures,
	    const param_set_t& parameters,
	    const std::string& prelude,
	    const std::string& postlude,
	    const std::string& description);

    const std::string	
    name() const;

    const signatures_t&
    signatures() const;

    const signature_t&
    get_signature(const args_t&) const;

    const std::string
    prelude() const;

    const std::string
    postlude() const;

    const param_value_t&
    fun_param(const param_value_t&);

    const param_value_t&
    fun_param() const;

    const param_set_t&
    parameters() const;

    const std::string&
    description() const;

  private:
    signatures_t			sigs_;
    param_set_t				param_;
    param_value_t			param_value_;
    param_value_t::const_iterator	prelude_;
    param_value_t::const_iterator	postlude_;
    param_value_t::const_iterator	name_;
    std::string				description_;
  };

} // spec

namespace std 
{
  
  std::ostream& 
  operator<<(std::ostream& o, const spec::FunSpec& cs);

} // std

#endif // ! VCSN_VAUC_MPP___SRC_SPEC_FUN_SPEC_HH
