// parse/libparse.cc
//
//

#include <string>

#include "parse/libparse.hh"
#include "spec/class_spec.hh"
#include "parse/class_spec_parse.hh"

/*------------------.
| Scanner functions |
`------------------*/
void class_spec_scan_open(const std::string &filename);
void class_spec_scan_close();
void fun_spec_scan_open(const std::string &filename);
void fun_spec_scan_close();
void module_spec_scan_open(const std::string &filename);
void module_spec_scan_close();

/*-----------------.
| Parser functions |
`-----------------*/
void class_spec_parse();
void fun_spec_parse();
void module_spec_parse();

/*----------------------------.
| Global variables definition |
`----------------------------*/
spec::ClassSpec*	the_class_spec = 0;
spec::ModuleSpec*	the_module_spec = 0;
spec::FunSpec*		the_fun_spec = 0;
int			errors = 0;

extern int yydebug;

/*------------.
| class_parse |
`------------*/
spec::ClassSpec*
class_parse(const std::string &name)
{
  yydebug = 0;
  class_spec_scan_open(name);
  class_spec_parse();
  class_spec_scan_close();
  return the_class_spec;
}


/*------------.
| fun_parse |
`------------*/
spec::FunSpec*
fun_parse(const std::string &name)
{
  yydebug = 0;
  fun_spec_scan_open(name);
  fun_spec_parse();
  fun_spec_scan_close();
  return the_fun_spec;
}

/*-------------.
| module_parse |
`-------------*/
spec::ModuleSpec*
module_parse(const std::string &name)
{
  yydebug = 0;
  module_spec_scan_open(name);
  module_spec_parse();
  module_spec_scan_close();
  return the_module_spec;
}
