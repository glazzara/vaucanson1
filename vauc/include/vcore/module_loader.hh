/*************************************
 * <vaucanson/core/module_loader.hh> *
 *************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_MODULE_LOADER_HH
#define CORE_MODULE_LOADER_HH

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

#endif

