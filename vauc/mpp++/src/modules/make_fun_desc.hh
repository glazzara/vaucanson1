// modules/make_fun_desc.hh
//
//
#ifndef MODULES_MAKE_FUN_DESC_HH
# define MODULES_MAKE_FUN_DESC_HH

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

#endif // MODULES_MAKE_FUN_DESC_HH
