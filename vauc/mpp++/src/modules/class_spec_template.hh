// class_spec_template.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_MODULES_CLASS_SPEC_TEMPLATE_HH
# define VCSN_VAUC_MPP___SRC_MODULES_CLASS_SPEC_TEMPLATE_HH

#include "
#PRELUDE#

    class #CLASSNAME#Type : public Type
    {
    public:
     typedef #STATIC_TYPE#       static_type_t;
     typedef #CLASSNAME#Type     dynamic_type_t;

    public:      
      virtual const std::string& name() const 
      { 
	static const std::string instance = 
	  std::string(\"#CLASSNAME#\");
	return instance; 
      }
      
      virtual const std::string& nickname() const
      {
	static const std::string instance = \"#CLASSNAME#\";
	return instance;
      }
      
      virtual bool compare_to(const Type& other) const
      { 
	return (NULL != dynamic_cast<const dynamic_type_t*>(&other)); 
      }
           
      virtual const Type& instance() const
      {
	static const dynamic_type_t instance;
	return instance;
      }
      
      virtual const std::type_info& cpp_type() const
      { 
	return typeid(static_type_t); 
      }
    };

    template <>
    struct TypeTraits<#STATIC_TYPE#>
    {
      typedef #CLASSNAME#Type	type_t;
    };

#POSTLUDE#

#endif // ! VCSN_VAUC_MPP___SRC_MODULES_CLASS_SPEC_TEMPLATE_HH
