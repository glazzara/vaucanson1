#include "transformer/ty_transformer.hh"
#include "funs.hh"

namespace spec
{
  void ty_transformer(std::ostream& o, const ClassSpec& spec)
  {
    std::string uname = upper(norm(spec.name()));
    std::string name = lower(norm(spec.name()));

    o << "#ifndef TTEMPL_" << uname << "_HXX\n"
      << "#define TTEMPL_" << uname << "_HXX\n\n"
      << spec.prelude() << std::endl
      << "\n#include <templates/type_macros.hxx>\n\n"
      << "\n\n#define TT_" << uname << "_DEF(_ModName, _Name";
    for (std::list<std::string>::const_iterator i = spec.parameters().begin();
	 i != spec.parameters().end();
	 ++i)
      o << ", " << *i;
    o << ") \\\n" 
      << "TYPE_BEGIN \\\n";

    CppParamCode::param_value_t vmap;
    
    for (std::list<std::string>::const_iterator i = spec.cpp_desc().params().begin();
	 i != spec.cpp_desc().params().end();
	 ++i)
      vmap[*i] = transform(*i);
      
    o << escape(spec.cpp_desc().instanciated_code(vmap)) << "\\\n";

    o << "TYPE_END(_ModName, _Name)\n\n#endif\n";

  }
}
