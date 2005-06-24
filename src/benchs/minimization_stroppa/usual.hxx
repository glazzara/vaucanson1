// usual.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_BENCHS_MINIMIZATION_STROPPA_USUAL_HXX
# define VCSN_BENCHS_MINIMIZATION_STROPPA_USUAL_HXX

namespace vcsn {

  namespace tools {


    template <typename Auto, typename Alphabet>
    inline
    Auto new_automaton(const Alphabet& alpha)
    {
      AUTOMATON_TYPES(Auto);

      monoid_t freemonoid(alpha);
      semiring_t semiring;
      series_set_t series(semiring, freemonoid);
      typename Auto::set_t automata_set(series);

      return Auto(automata_set);
    }


    template <typename Trans, typename Alphabet>
    inline
    Trans new_transducer(const Alphabet& alpha)
    {

      //      TRANSDUCER_TYPES(Trans);

      typename Trans::input_monoid_t	input_freemonoid(alpha);
      typename Trans::output_monoid_t	output_freemonoid(alpha);

      typename Trans::output_semiring_t	semiring;
      typename Trans::semiring_t output_series(semiring, output_freemonoid);
      typename Trans::series_t series(output_series, input_freemonoid);

      typename Trans::transducer_set_t	transducer_set(series);
      return		Trans(transducer_set);
    }

  } // tools


} // vcsn

#endif // ! VCSN_BENCHS_MINIMIZATION_STROPPA_USUAL_HXX
