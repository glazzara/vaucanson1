/***************************
 * "core/module_loader.hh" *
 ***************************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/module_loader.hh>
#include <vcore/exception.hh>

#include <cstdlib>
#include <iostream>
#include <cassert>

class Instance 
  : public vcsn::vauc::ModuleLoader
{
public:
  Instance() {};
  ~Instance() {};
};

static Instance *_loader_instance = 0;


namespace vcsn
{
  namespace vauc
  {

    Module::Module() {};
    Module::~Module() {};
    Module::Module(const Module& other) {};


    const ModuleBase& Module::entry() const
    {
      typedef ModuleBase *(*fptr)();
      
      fptr f = (fptr)(entry_);

      ModuleBase *p = f();
      return *p;
    }

    Module* ModuleLoader::load(const std::string& name) const
    {
      lt_dlhandle h = lt_dlopenext(name.c_str());
      if (h == NULL)
	RAISE("dynamic loading", lt_dlerror());

      lt_ptr p = lt_dlsym(h, "_module_entry");
      if (p == NULL)
	{
	  lt_dlclose(h);
	  RAISE("dynamic loading", lt_dlerror());
	}
      Module *m = new Module;
      m->h_ = h;
      m->entry_ = p;
      return m;
    }

    void ModuleLoader::unload(Module* p) const
    {
//       for (std::vector<std::pair<std::string, Callable> >::const_iterator i = p->entry().functions().begin();
// 	   i != p->entry().functions().end();
// 	   ++i)
// 	if (! i->unique())
// 	  RAISE("dynamic loading", "function busy: " + i->canonical_name());
//       for (std::vector<std::pair<std::string, Object> >::const_iterator i 
// 	     = p->entry().constants().begin();
// 	   i != p->entry().constants().end();
// 	   ++i)
// 	if (i->second.ref_count() > 1)
// 	  RAISE("dynamic loading", "constant busy: " + i->first);

      // FIXME: check this
      RAISE("dynamic loading", "unload not supported");

//       int r = lt_dlclose(p->h_);
//       if (r)
// 	RAISE("dynamic loading", lt_dlerror());

//       delete p;
    }

    ModuleLoader::ModuleLoader()
    {
      std::cerr << "Initializing dynamic loader..." << std::endl;

      int r = lt_dlinit();
      if (r)
	{
	  std::cerr << ">>> " << lt_dlerror() << std::endl;
	  exit(1);
	}      
    }

    ModuleLoader::~ModuleLoader()
    {
      std::cerr << "Shutting down dynamic loader..." << std::endl;
      
      int r = lt_dlexit();
      if (r)
	{
	  std::cerr << ">>> " << lt_dlerror() << std::endl;
	  exit(1);
	}
    }




    const ModuleLoader& loader_instance()
    {
      if (! ::_loader_instance)
	::_loader_instance = new Instance;
      return *::_loader_instance;
    }

    void loader_destroy()
    {
      delete ::_loader_instance;
      ::_loader_instance = 0;
    }

    ModuleLoader::ModuleLoader(const ModuleLoader& other)
    {
      assert(! "possible");
    }


  }
}

