/*****************
 * "core/env.cc" *
 *****************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/env.hh>
#include <vcore/exception.hh>
#include <vcore/module_loader.hh>
#include <vcore/closure.hh>

#include "unwind_init.hh"

#include <limits>
#include <cassert>

namespace vcsn
{
  namespace vauc
  {

    Env::Env(const ModuleLoader& loader)
      : _loader(loader) /* ,
			   _front(ObjectCatalog()) */
    {
      _scopes.push(ObjectCatalog());
    }

    unsigned Env::type_distance(Symbol from,
				Symbol to) 
    {
      // FIXME: fix this
      if (from == to || to == "")
	return 0;

      for (converters_map_t::const_iterator i = _cached_paths.begin();
	   i != _cached_paths.end();
	   ++i)
	{
	  if (i->first.first == from &&
	      i->first.second == to)
	    return i->second.first;
	}
      const std::pair<unsigned, Callable> &p = find_path(from, to);

      _cached_paths.insert(converters_map_t::value_type
			   (std::make_pair(from, to), p));
    }

    void Env::set_converter(Callable fun, Symbol to, unsigned cost)
    {
      if (to == "")
	RAISE("converters", "destination type cannot be the \"any\" type");

      if (fun.signature().size() != 1)
	RAISE("converters", "new converter must take exactly one argument");

      Symbol from = *fun.signature().begin();

      if (from == "")
	RAISE("converters", "new converter cannot take \"any\" as argument type");

      typeinfo_t t = reverse_type_lookup(to);
      Symbol tto = "";
      if (t.first == "?")
	tto = to;
      else
	tto = t.first;

      if (from == tto)
	RAISE("converters", "cannot set a conversion from " + to.value() + " to itself");

      const std::pair<Symbol,Symbol>& p = std::make_pair(from, tto);

      _converters[p] = std::make_pair(cost, fun);
      _cached_paths.clear();
	    
    }

    const Env::converters_map_t& Env::converters() const
    {
      return _converters;
    }

    void Env::remove_converter(Symbol from, Symbol to)
    {
      typeinfo_t f = reverse_type_lookup(from);
      Symbol tfrom = "";
      if (f.first == "?")
	tfrom = from;
      else
	tfrom = f.first;

      typeinfo_t t = reverse_type_lookup(to);
      Symbol tto = "";
      if (t.first == "?")
	tto = to;
      else
	tto = t.first;

      _converters.erase(std::make_pair(tfrom, tto));
      _cached_paths.clear();
    }

    Object Env::obj_convert(Object what, Symbol to) 
    {
      Symbol from = what.cpp_type().name();
      if (from == to || to == "")
	return what;
      
      for (converters_map_t::const_iterator i = _cached_paths.begin();
	   i != _cached_paths.end();
	   ++i)
	if (i->first.first == from && i->first.second == to)
	  {
	    if (i->second.first != std::numeric_limits<unsigned>::max())
	      {
		std::vector<Object> args;
		args.push_back(what);
		return i->second.second.call(*this, args);
	      }
	    else
	      break;
	  }
      RAISE("converting", "no converters found");
    }

    void Env::open_scope()
    {
      _scopes.push(_scopes.top());
    }

    void Env::close_scope()
    {
      ObjectCatalog c(_scopes.top());
      _scopes.pop();

      bool b = false;
      if (_scopes.empty())
	{
	  b = true;
	  _scopes.push(c);
	}

      if (b)
	RAISE("popping scope", "toplevel reached");
    }

    void Env::clear_scope()
    {
      ObjectCatalog& c = _scopes.top();
      for (ObjectCatalog::map_t::const_iterator i = c.contents().begin();
	   i != c.contents().end();
	   )
	if (i->first.value().size() > 0 && i->first.value()[0] != '_')
	  ++i;
	else
	  {
	    Symbol id = (i++)->first;
	    c.erase(id);
	  }
    }
	  

    Object Env::load_module(Symbol name)
    {
      return load_module(name, "libv" + name.value());
    }

    Object Env::load_module(Symbol name, Symbol file)
    {
      if (_loaded_modules.find(name) != _loaded_modules.end())
	RAISE("loading module", "module already loaded: " + name.value());
      
      Module *m = _loader.load(file.value());
      const ModuleBase& b = m->entry();

      // FIXME: check module dependencies

      _loaded_modules[b.name()] = std::make_pair(m, ObjectCatalog());
      ObjectCatalog& c = _loaded_modules[b.name()].second;
      
      // first, merge the type definitions
      for (std::vector<typeinfo_t>::const_iterator i = b.types().begin();
	   i != b.types().end();
	   ++i)
	_types.insert(std::make_pair(Symbol(i->first),
				     std::make_pair(Symbol(i->second), i->third)));


      // now, merge the constants
      for (ModuleBase::constants_t::const_iterator i = b.constants().begin();
	   i != b.constants().end();
	   ++i)
	c.structure(i->first, i->second);

      // now, merge the functions
      for (ModuleBase::functions_t::const_iterator i = b.functions().begin();
	   i != b.functions().end();
	   ++i)
	{
	  PartialCall pc(i->third);

	  // insert the function as object
	  if (i->first.size() > 0)
	    c.structure(i->first, Object(Callable(new PartialCall(pc))));

	  // and as closure...
	  // FIXME: there is room for optimization here...

	  if (i->second.size() > 0)
	    {
	      const std::string& f_name = i->second;
	      
	      if (c.contains(f_name) && OBJECT_IS_A(c[f_name], Closure))
		{
		  Object oc = c[f_name];
		  OBJECT_CAST(oc, Closure)->merge_fun(pc);
		}
	      else
		{
		  Object cl = Closure();
		  OBJECT_CAST(cl, Closure)->merge_fun(pc);
		  c.structure(f_name, cl);
		}

	      if (f_name[0] == '_')
		{
		  if (_scopes.top().contains(f_name))
		    {
		      Object oc = _scopes.top()[f_name];
		      if (OBJECT_IS_A(oc, Closure))
			OBJECT_CAST(oc, Closure)->merge_fun(pc);
		    }
		  else
		    {
		      Object cl = Closure();
		      OBJECT_CAST(cl, Closure)->merge_fun(pc);
		      _scopes.top().structure(f_name, cl);
		    }
		}
	    }
	}
      if (c.contains("_init") && OBJECT_IS_A(c["_init"], std::string))
	unwind_init(*this, *OBJECT_CAST(c["_init"], std::string));
      return ObjectCatalog(c);
    }

    Object Env::module_catalog(Symbol name) const
    {
      module_map_t::const_iterator i;
      if ((i = _loaded_modules.find(name)) == _loaded_modules.end())
	RAISE("extracting module objects", "module not loaded: " + name.value());
      
      return i->second.second;
    }

    void Env::import_module(Symbol name)
    {
      if (_loaded_modules.find(name) == _loaded_modules.end())
	RAISE("importing module", "module not loaded: " + name.value());

      ObjectCatalog& src = _loaded_modules[name].second;
      ObjectCatalog& dst = _scopes.top();

      for (ObjectCatalog::map_t::const_iterator l = src.contents().begin();
	   l != src.contents().end();
	   ++l)
	{
	  Object what = l->second;
	  if (!OBJECT_IS_A(what, Callable))
	    // import_module does not import callables
	    {
	      if (dst.contains(l->first))
		{
		  Object ow = dst[l->first];
		  if (OBJECT_IS_A(ow, Closure))
		    {
		      Closure& c = *OBJECT_CAST(ow, Closure);
		      if (OBJECT_IS_A(what, Closure))
			{
			  Closure& from = *OBJECT_CAST(what, Closure);
			  if (&from != &c)
			    for (Closure::funs_t::const_iterator f = from.funs().begin();
				 f != from.funs().end();
				 ++f)
			      c.merge_fun(*f);
			}
		      else
			{ 
			  if (OBJECT_IS_A(what, Callable))
			    {
			      Callable& from = *OBJECT_CAST(what, Callable);
			      c.merge_fun(PartialCall(from));
			    }
			  else
			    { /* do nothing, closures prefer not be overwritten */ }
			}
		    }
		  else
		    dst.structure(l->first, what);
		}
	      else
		dst.structure(l->first, what);
	    }
	}
    }

    void Env::import_object(Symbol module, Symbol name)
    {
      if (_loaded_modules.find(module) == _loaded_modules.end())
	RAISE("importing module", "module not loaded: " + module.value());

      ObjectCatalog& mod = _loaded_modules[module].second;

      if (! mod.contains(name))
	RAISE("importing object", name.value() + "not found in module " + module.value());
	
      Object what = mod[name];
      ObjectCatalog& top = _scopes.top();

      if (top.contains(name))
	{
	  Object ow = top[name];
	  if (OBJECT_IS_A(ow, Closure))
	    {
	      Closure& c = *OBJECT_CAST(ow, Closure);
	      if (OBJECT_IS_A(what, Closure))
		{
		  Closure& from = *OBJECT_CAST(what, Closure);
		  for (Closure::funs_t::const_iterator f = from.funs().begin();
		       f != from.funs().end();
		       ++f)
		    c.merge_fun(*f);
		}
	      else
		{ 
		  if (OBJECT_IS_A(what, Callable))
		    {
		      Callable& from = *OBJECT_CAST(what, Callable);
		      c.merge_fun(PartialCall(from));
		    }
		  else
		    { /* do nothing, closures prefer not be overwritten */ }
		}
	    }
	  else
	    top.structure(name, what);
	}
      else
	top.structure(name, what);
    }

//     void Env::set_front(Object& other)
//     {
//       if (other.cpp_type() != typeid(ObjectCatalog))
// 	RAISE("front change", "not a catalog");
//       _front = other;
//     }

//     void Env::clear_front()
//     {
//       _front = Object(ObjectCatalog());
//     }

    std::list<Object>& Env::history()
    {
      return _history;
    }
    const std::list<Object>& Env::history() const
    {
      return _history;
    }

    bool Env::contains(Symbol mod, Symbol id) const
    {
      module_map_t::const_iterator i;
      if ((i = _loaded_modules.find(mod)) == _loaded_modules.end())
	return false;
      return i->second.second.contains(id);
    }

    bool Env::contains(Symbol id) const
    {
      return /* _front.cast<ObjectCatalog>()->contains(id) || */
	_scopes.top().contains(id);
    }

    typeinfo_t Env::describe_type(Symbol id) const
    {

      type_map_t::const_iterator i;

      if ((i = _types.find(id)) != _types.end())
	return utility::make_triplet(id.value(), 
				     i->second.first.value(), 
				     i->second.second);
      return utility::make_triplet(id.value(), std::string("?"), std::string("?"));
    }

    typeinfo_t Env::reverse_type_lookup(Symbol id) const
    {
      type_map_t::const_iterator i;

      for (i = _types.begin(); i != _types.end(); ++i)
	if (i->second.first == id)
	  return utility::make_triplet(i->first.value(), id.value(), i->second.second);
      return utility::make_triplet(std::string("?"), id.value(), std::string("?"));
    }      

    typeinfo_t Env::type_of(Object obj) const 
    {
      Symbol id = obj.cpp_type().name();
      return describe_type(id);
    }

    Object Env::at(Symbol mod, Symbol id) const
    {
      module_map_t::const_iterator i;

      if ((i = _loaded_modules.find(mod)) == _loaded_modules.end())
	RAISE("getting object", "module not loaded: " + mod.value());

      const ObjectCatalog& c = i->second.second;
      if (! c.contains(id))
	RAISE("getting object", "object " + id.value() + " not found in module " + mod.value());

      return c[id];
    }

//     Object Env::front() const
//     {
//       return _front;
//     }

    Object Env::at(Symbol id) const
    {
//       if (_front.cast<ObjectCatalog>()->contains(id))
// 	return (*_front.cast<ObjectCatalog>())[id];

      if (_scopes.top().contains(id))
	return _scopes.top()[id];

      RAISE("getting object", "object not found: " + id.value());
    }
	 
    const ObjectCatalog& Env::get_scope() const
    {
      return _scopes.top();
    }

    void Env::kill(Symbol id) 
    {
      _scopes.top().erase(id);
    }

    void Env::assign(Symbol id, Object obj)
    {
      _scopes.top().structure(id, obj);
    }

    std::list<Symbol> Env::modules() const
    {
      std::list<Symbol> ret;
      for (module_map_t::const_iterator i = _loaded_modules.begin();
	   i != _loaded_modules.end();
	   ++i)
	ret.push_back(i->first);
      return ret;
    }

  }
}
