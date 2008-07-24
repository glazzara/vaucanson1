// krat_exp_parser.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HH

/** @addtogroup algebra *//** @{ */
/** @addtogroup series *//** @{ */
/**
 * @file krat_exp_parser.hh
 *
 * This file declares the parse() function.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>,
 *         Thomas Claveirole <thomas@lrde.epita.fr>
 *	   Vivien Delmon <vivien@lrde.epita.fr>
 * @see parse()
 */
/** @} */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vector>
# include <string>

namespace vcsn {

  namespace algebra {
    /** @addtogroup algebra *//** @{ */
    /** @addtogroup series *//** @{ */

    struct token_representation_t
    {
      std::string		open_par;
      std::string		close_par;
      std::string		plus;
      std::string		times;
      std::string		star;
      std::string		one;
      std::string		zero;
      std::string		open_weight;
      std::string		close_weight;
      std::vector<std::string>	spaces;
    };

    /**
     * Parse a rational expression.
     *
     * This fonction parses any kind of rational expression using the bison
     * generated parser.
     *
     * The grammar is :
     *
     @verbatim
     %start rexp

     rexp ::= OPAR exp CPAR
         |   rexp PLUS rexp
         |   rexp TIMES rexp
         |   rexp rexp
         |   rexp STAR
         |   WEIGHT rexp
         |   rexp WEIGHT
         |   ONE
         |   ZERO
         |   WORD
     @endverbatim
     *
     * @todo The token representation must be contain in the automaton.
     *
     * This function returns  a pair which first element  is a Boolean
     * indicating whether an error  occured or not. The second element
     * is an error message when a parse error have been ecountered.
     *
     * @param from The rational expression, as a string.
     * @param exp The element to store the result in. Be sure its set
     *            is correct before calling parse.
     * @param lex_trace Enable lexer trace (for debuging purposes).
     * @param parse_trace Enable parser trace (for debuging purposes).
     *
     * @author Yann Régis-Gianas <yann@lrde.epita.fr>,
     *         Thomas Claveirole <thomas@lrde.epita.fr>
     *	       Vivien Delmon <vivien@lrde.epita.fr>
     */


    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from,
	  Element<S, T>& exp,
	  token_representation_t tok_rep = token_representation_t(),
	  bool lex_trace = false,
	  bool parse_trace = false);

    /** @} */
    /** @} */

  } // algebra

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/series/krat_exp_parser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HH
