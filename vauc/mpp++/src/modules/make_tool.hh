// modules/make_tool.hh
//
//
#ifndef MODULES_MAKE_TOOL_HH
# define MODULES_MAKE_TOOL_HH

# include <string>

# include "spec/cpp_code.hh"

namespace modules
{

  spec::CppParamCode
  load_template(const std::string& filename);  

  std::string
  get_include_name(const std::string & module_name, const std::string& param);

  std::string
  get_class_name(const std::string & module_name, const std::string& param);

  std::string
  get_class_zcppname(const std::string& current_module_name, const std::string& param);

} // modules

#endif // MODULES_MAKE_TOOL_HH
