// modules/make_class_desc.hh
//
//
#ifndef MODULES_MAKE_CLASS_DESC_HH
# define MODULES_MAKE_CLASS_DESC_HH

# include <string>

# include "spec/class_spec.hh"

namespace modules {

/*----------------.
| make_class_desc |
`----------------*/
  std::string
  make_class_desc(const std::string&			module_name,
		  const spec::ClassSpec&	       	class_desc, 
		  const spec::ClassSpec::param_value_t& param_value);

} // modules

#endif // MODULES_MAKE_CLASS_DESC_HH
