// krat_exp_parser.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
 * @see parse()
 */
/** @} */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <utility>
# include <string>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup series *//** @{ */

    /**
     * Parse a rational expression.
     *
     * This functions parses any numerical rational expression.
     * The grammar is:
     *
     @verbatim
     exp ::= '(' exp ')'
         |   exp '+' exp
         |   exp '.' exp
         |   exp exp
         |   exp '*'
         |   weight ' ' exp
         |   exp ' ' weight
         |   0
         |   1
         |   word
     @endverbatim
     *
     * Priority for operators is, from the most important to the least
     * important:
     *
     *  - * (star), to star a series.
     *  - ' ' (space), to weight a series either on the right or on the left.
     *  - . (dot), to concatenate two series.
     *  - + (plus), to do the union of two series.
     *
     * This function returns  a pair which first element  is a Boolean
     * indicating whether an error  occured or not. The second element
     * is an error message when a parse error have been ecountered.
     *
     * Note that this function requires exception support from the compiler.
     *
     * @param from The rational expression, as a string.
     * @param exp The element to store the result in. Be sure its set
     *            is correct before calling parse.
     * @param lex_trace Enable lexer trace (for debuging purposes).
     * @param parse_trace Enable parser trace (for debuging purposes).
     *
     * @author Yann Régis-Gianas <yann@lrde.epita.fr>,
     *         Thomas Claveirole <thomas@lrde.epita.fr>
     */
    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from,
	  Element<S, T>& exp,
	  bool lex_trace = false,
	  bool parse_trace = false);

    /** @} */
    /** @} */

  } // algebra

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/krat_exp_parser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HH
