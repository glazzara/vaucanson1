// parse/libparse.hh
//
//
#ifndef PARSE_LIBPARSE_HH
# define PARSE_LIBPARSE_HH

#include "spec/class_spec.hh"
#include "spec/fun_spec.hh"
#include "spec/module_spec.hh"

spec::ClassSpec*	
class_parse(const std::string& name);

spec::FunSpec*	
fun_parse(const std::string& name);

spec::ModuleSpec*	
module_parse(const std::string& name);

#endif // PARSE_LIBPARSE_HH
