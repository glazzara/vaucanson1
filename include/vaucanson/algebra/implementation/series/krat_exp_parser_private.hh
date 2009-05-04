// krat_exp_parser.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_PRIVATE_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_PRIVATE_HH

# include <vaucanson/algebra/implementation/series/krat_exp_proxy.hh>

// These definitions really belong to lib/krat_exp/krat_exp_bison.yy,
// but we need to have them in the public headers so they are installed.
namespace vcsnyy
{
  struct token_queue;

  struct krat_exp_parser
  {
    krat_exp_parser();
    ~krat_exp_parser();
    void insert_word(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_weight(vcsn::algebra::semiring_virtual* sem);
    void insert_zero(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_token(int i, std::string* str);
    int parse(vcsn::algebra::krat_exp_virtual& rexp, std::string& error);

    token_queue* tok_q_;
   };
} // vcsnyy

#endif // VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_PRIVATE_HH
