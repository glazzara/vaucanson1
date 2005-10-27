// equivalent_functions.hh: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/complement.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/algorithms/product.hh>
#include CONTEXT_HEADER

using namespace CONTEXT_NAMESPACE;

bool are_equivalent(const automaton_t& a,
		    const automaton_t& b);

automaton_t get_aut(std::string s);

rat_exp_t get_exp(std::string s);

