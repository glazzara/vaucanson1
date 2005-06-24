// module_loader.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_VCORE_MODULE_LOADER_HH
# define VCSN_VAUC_INCLUDE_VCORE_MODULE_LOADER_HH

#include <vcore/module_base.hh>
#include <string>
#include <ltdl.h>

namespace vcsn
{
  namespace vauc
  {

    class ModuleLoader;

    class Module
    {
    public:      
      const ModuleBase& entry() const;

    protected:
      ~Module();
      Module();
      Module(const Module& other);
      lt_dlhandle h_;
      lt_ptr entry_;
      friend class ModuleLoader;
    };


    class ModuleLoader
    {
    public:
      Module* load(const std::string& name) const;

      // although there is provision for unloading a module at this
      // stage, it is yet unused.
      void unload(Module *p) const;


    protected:
      ~ModuleLoader();
      ModuleLoader();
      ModuleLoader(const ModuleLoader& other);
    };

    const ModuleLoader& loader_instance();
    void loader_destroy();

  }
}

#endif // ! VCSN_VAUC_INCLUDE_VCORE_MODULE_LOADER_HH
