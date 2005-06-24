// make_fun_desc.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_MODULES_MAKE_FUN_DESC_HH
# define VCSN_VAUC_MPP___SRC_MODULES_MAKE_FUN_DESC_HH

# include "spec/fun_spec.hh"

namespace modules {

/*--------------.
| make_fun_desc |
`--------------*/
  void
  make_fun_desc(const std::string&			module_name,
		const std::string&			nick_name,
		const spec::FunSpec&			fun_desc, 
		const spec::FunSpec::param_value_t&	param_value);
  
  std::string
  make_fun_version(const std::string&			module_name,
		   const std::string&			nick_name,
		   const spec::FunSpec&			fun_desc, 
		   const spec::FunSpec::param_value_t&  param_value,
		   const spec::FunSpec::signature_t&	sig);
  
  
} // modules

#endif // ! VCSN_VAUC_MPP___SRC_MODULES_MAKE_FUN_DESC_HH
