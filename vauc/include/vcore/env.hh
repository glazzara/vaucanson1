/*****************
 * <vcore/env.hh> *
 *****************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_ENV_HH
#define CORE_ENV_HH

#include <types/object.hh>
#include <types/symbol.hh>
#include <types/type.hh>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <vcore/callable.hh>
#include <vcore/object_catalog.hh>
#include <stack>

namespace vcsn
{
  namespace vauc
  {

    class ModuleLoader;
    class Module;

    class Env
    {
    public:
      Env(const ModuleLoader& loader);

      unsigned type_distance(Symbol from, Symbol to);
      Object obj_convert(Object what, Symbol final_type);

      void set_converter(Callable fun, Symbol to, unsigned cost);
      typedef std::map<std::pair<Symbol, Symbol>, std::pair<unsigned, Callable> >
      converters_map_t;

      const converters_map_t& converters() const;
      void remove_converter(Symbol from, Symbol to);
			 

      // exports the current scope
      const ObjectCatalog& get_scope() const;

      void open_scope();
      void close_scope();

      Object load_module(Symbol name);
      Object load_module(Symbol name, Symbol file);

      Object module_catalog(Symbol name) const;
      void import_module(Symbol name);
      void import_object(Symbol module, Symbol name);

//       Object front() const;
//       void set_front(Object& other);
//       void clear_front();

      std::list<Object>& history();
      const std::list<Object>& history() const;

      bool contains(Symbol mod, Symbol id) const;
      bool contains(Symbol id) const;

      Object at(Symbol mod, Symbol id) const;
      Object at(Symbol id) const;

      typeinfo_t type_of(Object obj) const;
      typeinfo_t describe_type(Symbol id) const;
      typeinfo_t reverse_type_lookup(Symbol id) const;

      void assign(Symbol id, Object obj);
      void kill(Symbol id);
      void clear_scope();

      std::list<Symbol> modules() const;


      typedef std::map<Symbol, std::pair<Symbol, std::string> > type_map_t;
      const type_map_t& type_map() const { return _types; }
      

    protected:
      const ModuleLoader& _loader;
      typedef std::map<Symbol, std::pair<Module*, ObjectCatalog> > module_map_t;
      module_map_t _loaded_modules;

      type_map_t _types;

      converters_map_t _converters;
      converters_map_t _cached_paths;

      std::stack<ObjectCatalog> _scopes;
//       Object _front;
      std::list<Object> _history;

      std::pair<unsigned, Callable> find_path(Symbol from, Symbol to) const;
    };

  }
}


#endif
