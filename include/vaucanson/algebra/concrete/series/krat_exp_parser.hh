// krat_exp_parser.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HH

/**
 * @file krat_exp_parser.hh
 *
 * @brief This file declare the parse() function.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>,
 *         Thomas Claveirole <thomas@lrde.epita.fr>
 * @see parse()
 */

# include <vaucanson/fundamental/fundamental.hh>
# include <utility>
# include <string>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra */ /** @{ */
    /** @addtogroup series */ /** @{ */
    
    /**
     * @brief Parse a rational expression.
     *
     * <p>This functions parses any numerical rational expression.</p>
     * <p>The grammar is:</p>
     *
     * <pre>
     * exp ::= '(' exp ')'
     *     |   exp '+' exp
     *     |   exp '.' exp
     *     |   exp exp
     *     |   exp '*'
     *     |   weight ' ' exp
     *     |   exp ' ' weight
     *     |   0
     *     |   1
     *     |   word
     * </pre>
     * <p>Priority for operators is: '*' > ' ' > '.' > '+'.</p>
     *
     * <p>This function returns a pair which first element is a boolean
     * indicating whether an error occured or not. The second element
     * is an error message when a parse error have been ecountered.</p>
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


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/concrete/series/krat_exp_parser.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HH
