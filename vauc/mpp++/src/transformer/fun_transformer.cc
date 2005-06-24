// fun_transformer.cc: this file is part of the Vaucanson project.
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
#include "transformer/fun_transformer.hh"
#include "funs.hh"

namespace spec
{
  void fun_transformer(std::ostream& o, const FunSpec& spec)
  {
    std::string uname = upper(norm(spec.name()));
    std::string name = lower(norm(spec.name()));
    const FunSig& sig = *spec.signatures().begin();

    o << "#ifndef TEMPL_" << uname << "_HXX\n"
      << "#define TEMPL_" << uname << "_HXX\n\n"
      << spec.prelude() << std::endl
      << "\n#include <templates/fun_macros.hxx>\n\n";

    for (FunSig::args_t::const_iterator i = sig.args.begin();
	 i != sig.args.end();
	 ++i)
      if (i->second != "any")
	{
	  std::string rt = transform2(i->second);
	  if (rt != "")
	    o << "#include <" << rt << ".hh>\n\n";
	}

    std::ostringstream MANGLEDs;
    MANGLEDs << uname << "_NAME(";
    for (std::list<std::string>::const_iterator i = spec.parameters().begin();
	 i != spec.parameters().end();
	 ++i)
      {
	if (i != spec.parameters().begin())
	  MANGLEDs << ", ";
	MANGLEDs << *i;
      }
    MANGLEDs << ")";

    std::string MANGLED = MANGLEDs.str();

    o << "#define MAKE_" << MANGLED << " " << uname;
    for (std::list<std::string>::const_iterator i = spec.parameters().begin();
	 i != spec.parameters().end();
	 ++i)
      o << " ## __ ## " << *i;

    o << "\n#define " << MANGLED << " MAKE_" << MANGLED
      << "\n\n#define T_" << uname << "_DEF(_ModName, _Name";
    for (std::list<std::string>::const_iterator i = spec.parameters().begin();
	 i != spec.parameters().end();
	 ++i)
      o << ", " << *i;
    o << ", _Desc, _CName) \\\n" 
      << "FUN_BEGIN(_ModName, _Name, " << MANGLED;
    o << ", _Desc, " << (sig.args.size() - 1) 
      << ", _CName) \\\n";
    for (FunSig::args_t::const_iterator i = sig.args.begin();
	 i != sig.args.end();
	 ++i)
      if (i->first != "ret")
	o << "\tFUN_DECL_ARG(" << transform(i->second) << ") \\\n";
    o << "FUN_TEXT(_ModName, " << MANGLED << ") \\\n";
     
    int count = 0;
    for (FunSig::args_t::const_iterator i = sig.args.begin();
	 i != sig.args.end();
	 ++i, ++count)
      if (i->first != "ret")
	o << "\tFUN_GET_ARG(" << count << ", " 
	  << i->first << ", "
	  << transform(i->second) << ") \\\n";
    o << "{ FUN_PROTECT_EXN \\\n";

    CppParamCode::param_value_t vmap;
    
    for (std::list<std::string>::const_iterator i = sig.call.params().begin();
	 i != sig.call.params().end();
	 ++i)
      vmap[*i] = transform(*i);
      
    o << escape(sig.call.instanciated_code(vmap)) << "\\\n FUN_CATCH_EXN } \\\n";

    o << "FUN_RET(_ModName, " << MANGLED << ") \\\n";
    for (FunSig::args_t::const_iterator i = sig.args.begin();
	 i != sig.args.end();
	 ++i)
      if (i->first == "ret")
	{
	  o << "\treturn ";
	  if (i->second == "any")
	    o << "\"\"";
	  else
	    o << "typeid(" << transform(i->second) << ").name()";
	  o << ";\\\n";
	}
    o << "FUN_END(_ModName, " << MANGLED << ") \n\n#endif\n";

  }
}

