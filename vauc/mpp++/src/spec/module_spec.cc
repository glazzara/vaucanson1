// module_spec.cc: this file is part of the Vaucanson project.
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
#include <exception>

#include "spec/module_spec.hh"
#include "internal/mangling.hh"

namespace spec 
{

  ModuleSpec::ModuleSpec(const std::string&		name, 
			 const fun_version_list_t&	fun_versions, 
			 const type_version_list_t&	type_versions,
			 const object_version_list_t&	object_versions,
			 const aliases_t&		aliases, 
			 const std::string&		prelude,
			 const std::string&		description) :
    name_(name),
    fun_versions_(fun_versions),
    type_versions_(type_versions),
    object_versions_(object_versions),
    aliases_(aliases),
    prelude_(prelude),
    description_(description)
  {}  

  const std::string&	
  ModuleSpec::name() const
  {
    return name_;
  }

  const std::string&
  ModuleSpec::prelude() const
  {
    return prelude_;
  }

  const ModuleSpec::fun_version_list_t&
  ModuleSpec::fun_versions() const
  {
    return fun_versions_;
  }

  ModuleSpec::fun_version_list_t&
  ModuleSpec::fun_versions() 
  {
    return fun_versions_;
  }

  const ModuleSpec::object_version_list_t&
  ModuleSpec::object_versions() const
  {
    return object_versions_;
  }

  ModuleSpec::aliases_t&
  ModuleSpec::aliases() 
  {
    return aliases_;
  }

  const ModuleSpec::aliases_t&
  ModuleSpec::aliases() const
  {
    return aliases_;
  }

  const std::string&
  ModuleSpec::description() const
  {
    return description_;
  }

    
  const ModuleSpec::type_version_list_t&
  ModuleSpec::type_versions() const
  {
    return type_versions_;
  }

  ModuleSpec::type_version_list_t&
  ModuleSpec::type_versions() 
  {
    return type_versions_;
  }

  void 
  ModuleDB::insert(const std::string& dynamicname, const std::string& realname)
  {
    if (map_.find(dynamicname) != map_.end())
      std::cerr << "make_modules : Warning : Two classes with the same dynamic name."
		<< std::endl;
    Tuple t;
    t.realname = realname;
    t.filename = this->mangle(realname);
    map_[dynamicname] = t;
  }

  std::string 
  ModuleDB::get_realname(const std::string& dynamic_name)
  {
    ModuleDB::db_t::iterator n = map_.find(dynamic_name);
    if (n == map_.end())
      {
	std::cerr << "make_modules : " << dynamic_name << " not found."
		  << std::endl;
	return "undefined type";
      }
    return (*n).second.realname;
  }

  std::string
  ModuleDB::get_filename(const std::string& dynamic_name)
  {
    ModuleDB::db_t::iterator n = map_.find(dynamic_name);
    if (n == map_.end())
      {
	std::cerr << "make_modules : " << dynamic_name << " not found."
		  << std::endl;
	return "undefined type";
      }
    return (*n).second.filename;
  }

  std::string 
  ModuleDB::mangle(const std::string& realname)
  {
    std::string compressed;
    Mangler m;
    m.append(realname);
    try {
//       std::cerr << m.mangled() << " " << m.zip64(m.mangled()) 
// 		<< " " << m.escape(m.zip64(m.mangled())) << std::endl;

      compressed = m.escape(m.zip64(m.mangled()));

//       std::cerr << "mangle : " << realname << " -> " << compressed << " -> "
// 		<< m.demangle(m.unzip64(m.unescape(compressed))) << std::endl;
//       std::cerr << m.unescape(compressed) << " " << m.unzip64(m.unescape(compressed)) << std::endl;
    }
    catch (const std::exception& e)
      {
	std::cerr << e.what() << std::endl;
      }
    return compressed;
  }

  std::string 
  ModuleDB::demangle(const std::string& filename)
  {
    Mangler m;
    std::string name = m.demangle(m.unzip64(m.unescape(filename)));
//     std::cerr << "demangle : " << filename << " -> " << name << std::endl;
    return name;
  }


  void ModuleDB::save(std::ostream& out)
  {
    for (ModuleDB::db_t::const_iterator i = map_.begin();
	 i != map_.end();
	 ++i)
      out << (*i).first 
	  << " " << (*i).second.realname 
	  << " " << (*i).second.filename
	  << std::endl;
  }

  void ModuleDB::load(std::istream& in)
  {
    std::string dyn_name;
    Tuple t;

    while (!in.eof())
      {
	in >> dyn_name >> t.realname >> t.filename;
// 	std::cerr << "Found : " << dyn_name << " -> " 
// 		  << t.realname << " "
// 		  << t.filename << std::endl;
	map_[dyn_name] = t;
      }
  }
  
} // spec

