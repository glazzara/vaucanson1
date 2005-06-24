// module_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_VCORE_MODULE_BASE_HH
# define VCSN_VAUC_INCLUDE_VCORE_MODULE_BASE_HH

#include <triplet.hh>
#include <types/type.hh>
#include <string>
#include <vector>
#include <lazy/exp.hh>
#include <vcore/callable.hh>

namespace vcsn
{
  namespace vauc
  {

    class ModuleBase
    {
    public:


      virtual const std::string& name() const = 0;
      virtual const std::string& description() const = 0;


      // the modules that should be loaded when this one is loaded.
      // no dependency should be strict, only suggested.
      typedef std::vector<std::string> deps_t;

      virtual const deps_t& suggested_deps() const = 0;

      // the types defined by the module.
      typedef std::vector<typeinfo_t> types_t;

      virtual const types_t& types() const = 0;

      // the functions defined by the module.
      typedef utility::triplet<
	std::string /* callable name */,
	std::string /* closure name */,
	Callable > fun_descr_t;
      typedef std::vector<fun_descr_t> functions_t;
      

      virtual const functions_t& functions() const = 0;

      // a number of pre-defined constants.
      // the special object "_init", if it is defined and is a LazyExp, is
      // automatically evaluated once the module is loaded.

      typedef std::pair<std::string, Object> constant_descr_t;
      typedef std::vector<constant_descr_t> constants_t;
      virtual const constants_t& constants() const = 0;


      virtual ~ModuleBase() {};
    };


  }
}

#endif // ! VCSN_VAUC_INCLUDE_VCORE_MODULE_BASE_HH
