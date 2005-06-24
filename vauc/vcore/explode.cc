// explode.cc: this file is part of the Vaucanson project.
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
#include "explode.hh"
#include <limits>
#include <utility>

namespace vcsn
{
  namespace vauc
  {
    struct not_found {};

    typedef std::pair<unsigned, Callable> mat_value_t;

    class Composition : public FunctionImpl
    {
    public:
      virtual const sig_t& signature() const
      {
	return _inside.signature();
      }
      virtual std::string return_type(const sig_t& sig) const
      {
	return "";
      }
      virtual const std::string& description() const
      {
	return _description;
      }

      virtual const std::string& origin() const
      {
	return _origin;
      }
      virtual ~Composition() {}

      Composition(Callable in, Callable out)
	: _inside(in), _outside(out),
	  _origin("<composition for conversions>")
      {
	_description = '(' + out.description() 
	  + ") o (" + in.description() + ')';
      }

      virtual Object call(Env& context,
			  const std::vector<Object>& args) const
      {
	std::vector<Object> inter_args;
	inter_args.push_back(_inside.call(context, args));
	return _outside.call(context, inter_args);
      }

    protected:
      Callable _inside;
      Callable _outside;
      std::string _origin;
      std::string _description;
    };


    static Callable compose_callables(Callable in, Callable out)
    {
      return Callable(new Composition(in, out));
    }

    mat_value_t floyd_warshall(const std::vector<Symbol>& v,
						 const std::pair<Symbol, Symbol>& ij,
						 const Env::converters_map_t& wmap,
						 size_t k, size_t i, size_t j)
    {
      static const unsigned max = std::numeric_limits<unsigned>::max();
      if (k == 0)
	{
	  Env::converters_map_t::const_iterator w = 
	    wmap.find(ij);
	  if (w == wmap.end())
	    return mat_value_t(max, Callable());
	  return w->second;
	}

      mat_value_t ijkp = floyd_warshall(v, ij, wmap, k-1, i, j);
      std::pair<Symbol, Symbol> ik(v[i],v[k-1]);
      mat_value_t ikkp = floyd_warshall(v, ik, wmap, k-1, i, k);
      std::pair<Symbol, Symbol> kj(v[k-1],v[j]);
      mat_value_t kjkp = floyd_warshall(v, kj, wmap, k-1, k, j);

      unsigned sum = ikkp.first + kjkp.first;
      if (sum < ikkp.first || sum < kjkp.first)
	sum = max;
      if (ijkp.first <= sum)
	  return ijkp;
      if (sum == max)
	return mat_value_t(max, Callable());
      return mat_value_t(sum, compose_callables(ikkp.second, kjkp.second));
    }


    // this function computes all possible shortest conversion paths
    void explode_converters(const Env::type_map_t& types,
			    const Env::converters_map_t& given,
			    Env::all_converters_map_t& to)
    {
      std::vector<Symbol> all_types;
      for (Env::type_map_t::const_iterator i = types.begin();
	   i != types.end();
	   ++i)
	all_types.push_back(i->second.first);

      for (size_t i = 0; i < all_types.size(); ++i)
	for (size_t j = 0; j < all_types.size(); ++j)
	  {
	    std::pair<Symbol,Symbol> ij(all_types[i],all_types[j]);
	    mat_value_t d = floyd_warshall(all_types, ij, given, all_types.size(), i, j);
	    if (d != std::numeric_limits<unsigned>::max())
	      to.insert(Env::all_converters_map_t::value_type(ij, d));
	  };
      
    }
  }
}

