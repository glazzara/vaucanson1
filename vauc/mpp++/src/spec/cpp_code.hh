// cpp_code.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_SPEC_CPP_CODE_HH
# define VCSN_VAUC_MPP___SRC_SPEC_CPP_CODE_HH

# include <list>
# include <string>
# include <map>

namespace spec {

class CppParamCode
{
public :
  typedef std::string				code_t;
  typedef std::string				param_t;
  typedef std::string				value_t;
  typedef std::list<param_t>			param_set_t;
  typedef std::map<param_t, value_t>		param_value_t;

public :
  CppParamCode();
  CppParamCode(const std::string& param_code);

  const param_set_t& params() const
  { return parameters_; }

  const code_t
  instanciated_code(const param_value_t& values) const;
  
private :
  param_set_t		parameters_;
  code_t		param_code_;
};

} // spec

#endif // ! VCSN_VAUC_MPP___SRC_SPEC_CPP_CODE_HH
