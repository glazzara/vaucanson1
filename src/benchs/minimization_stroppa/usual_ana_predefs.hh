// usual_ana_predefs.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_BENCHS_MINIMIZATION_STROPPA_USUAL_ANA_PREDEFS_HH
# define VCSN_BENCHS_MINIMIZATION_STROPPA_USUAL_ANA_PREDEFS_HH


# include <vaucanson/algebra/implementation/letter/char_letter.hh>
# include <vaucanson/algebra/implementation/letter/range.hh>
# include <vaucanson/algebra/implementation/alphabets/set_alphabet.hh>
# include <vaucanson/algebra/implementation/alphabets/decorated_alphabet.hh>
# include <vaucanson/algebra/implementation/free_monoid/str_words.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/automata/implementation/graph.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>

# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>
# include <vaucanson/algebra/implementation/semiring/tropical_semiring.hh>

# include <minimization_stroppa/int_traits.hh>

# include <map>



namespace vcsn {

  namespace algebra {

    template <typename LetterImpl, typename WordImpl>
    struct AlgebraPredefs {
      typedef LetterImpl                                        Letter;
      typedef AlphabetSet<Letter>				Alphabets;
      typedef Element<Alphabets, std::set<Letter> >		Alphabet;
      typedef AlphabetDecorator<Letter, std::set<Letter> >	DAlphabetImpl;
      typedef Element<Alphabets, DAlphabetImpl>		        DAlphabet;

      typedef FreeMonoid<Alphabet>		        	Words;
      typedef WordImpl                                          WordValue;
      typedef Element<Words, WordValue>	        	        Word;
      };

    template <typename StateLabel>
    struct FeatureStructurePredefs {
      typedef StateLabel                                        state_label_t;
    };

    typedef AlgebraPredefs<static_ranged<char, static_char_interval<'a','z'> >, std::basic_string<static_ranged<char, static_char_interval<'a','z'> > > > small_alpha_letter;
    typedef AlgebraPredefs<char, std::string> char_letter;
    typedef AlgebraPredefs<unsigned int, std::basic_string<unsigned int> > int_letter;

    typedef FeatureStructurePredefs<std::string>  string_fs;
    typedef FeatureStructurePredefs<unsigned int> int_fs;
    typedef FeatureStructurePredefs<char> char_fs;


  } // algebra


  namespace tools {

    using namespace vcsn::algebra;

    typedef polynom<char_letter::WordValue, bool>                       usual_char_serie_value_t;
    typedef polynom<char_letter::WordValue, float>                      weighted_char_serie_value_t;

    typedef polynom<int_letter::WordValue, bool>                        usual_int_serie_value_t;
    typedef polynom<int_letter::WordValue, float>                       weighted_int_serie_value_t;

    typedef Series<NumericalSemiring, char_letter::Words>               usual_char_series_t;
    typedef Series<TropicalSemiring<TropicalMax>, char_letter::Words>   tropical_max_char_series_t;
    typedef Series<TropicalSemiring<TropicalMin>, char_letter::Words>   tropical_min_char_series_t;
    typedef Series<usual_char_series_t, char_letter::Words>             usual_t_char_series_t;

    typedef Series<NumericalSemiring, int_letter::Words>                usual_int_series_t;
    typedef Series<TropicalSemiring<TropicalMax>, int_letter::Words>    tropical_max_int_series_t;
    typedef Series<TropicalSemiring<TropicalMin>, int_letter::Words>    tropical_min_int_series_t;
    typedef Series<usual_int_series_t, int_letter::Words>               usual_t_int_series_t;


    typedef Graph
    <
      labels_are_series,
      //labels_are_letters,
      char_letter::WordValue,
      bool,
      usual_char_serie_value_t,
      char_letter::Letter,
      NoTag,
      NoTag>
    usual_char_automaton_impl_t;

    typedef Graph
    <
      labels_are_series,
      //      labels_are_letters,
      int_letter::WordValue,
      bool,
      usual_int_serie_value_t,
      int_letter::Letter,
      NoTag,
      NoTag>
    usual_int_automaton_impl_t;


    typedef Graph
    <
      labels_are_series,
      //labels_are_couples,
      char_letter::WordValue,
      float,
      weighted_char_serie_value_t,
      char_letter::Letter,
      NoTag,
      NoTag>
    weighted_char_automaton_impl_t;

    typedef Graph
    <
      labels_are_series,
      //labels_are_couples,
      int_letter::WordValue,
      float,
      weighted_int_serie_value_t,
      int_letter::Letter,
      NoTag,
      NoTag>
    weighted_int_automaton_impl_t;


    typedef Graph
    <
      labels_are_series,
      char_letter::WordValue,
      rat::exp<char_letter::WordValue, bool>,
      polynom<char_letter::WordValue, rat::exp<char_letter::WordValue, bool> >,
      char_letter::Letter,
      NoTag,
      NoTag>
    usual_char_transducer_impl_t;

    typedef Graph
    <
      labels_are_series,
      int_letter::WordValue,
      rat::exp<int_letter::WordValue, bool>,
      polynom<int_letter::WordValue, rat::exp<int_letter::WordValue, bool> >,
      int_letter::Letter,
      NoTag,
      NoTag>
    usual_int_transducer_impl_t;

    typedef Graph
    <
      labels_are_series,
      char_letter::WordValue,
      rat::exp<char_letter::WordValue, float>,
      polynom<char_letter::WordValue, rat::exp<char_letter::WordValue, float> >,
      char_letter::Letter,
      NoTag,
      NoTag>
    weigthed_char_transducer_impl_t;

    typedef Graph
    <
      labels_are_series,
      int_letter::WordValue,
      rat::exp<int_letter::WordValue, float>,
      polynom<int_letter::WordValue, rat::exp<int_letter::WordValue, float> >,
      int_letter::Letter,
      NoTag,
      NoTag>
    weigthed_int_transducer_impl_t;


    typedef Graph
    <
      labels_are_series,
      //labels_are_letters,
      int_letter::WordValue,
      bool,
      usual_int_serie_value_t,
      int_letter::Letter,
      std::map<hstate_t, int_fs::state_label_t>,
      NoTag>
    usual_int_int_feature_structure_impl_t;

    typedef Graph
    <
      labels_are_series,
      //labels_are_letters,
      int_letter::WordValue,
      bool,
      usual_int_serie_value_t,
      int_letter::Letter,
      std::map<hstate_t, string_fs::state_label_t>,
      NoTag>
    usual_int_string_feature_structure_impl_t;



    typedef Element<Automata<usual_char_series_t>, usual_char_automaton_impl_t>             usual_char_automaton_t;
    typedef Element<Automata<usual_char_series_t>, weighted_char_automaton_impl_t>          numerical_char_automaton_t;
    typedef Element<Automata<tropical_max_char_series_t>, weighted_char_automaton_impl_t>   tropical_max_char_automaton_t;
    typedef Element<Automata<tropical_min_char_series_t>, weighted_char_automaton_impl_t>   tropical_min_char_automaton_t;

    typedef Element<Automata<usual_int_series_t>, usual_int_automaton_impl_t>               usual_int_automaton_t;
    typedef Element<Automata<usual_int_series_t>, weighted_int_automaton_impl_t>            numerical_int_automaton_t;
    typedef Element<Automata<tropical_max_int_series_t>, weighted_int_automaton_impl_t>     tropical_max_int_automaton_t;
    typedef Element<Automata<tropical_min_int_series_t>, weighted_int_automaton_impl_t>     tropical_min_int_automaton_t;

    typedef Element<Transducer<usual_t_char_series_t>, usual_char_transducer_impl_t>        usual_char_transducer_t;
    typedef Element<Transducer<usual_t_char_series_t>, weigthed_char_transducer_impl_t>     numerical_char_transducer_t;

    typedef Element<Transducer<usual_t_int_series_t>, usual_int_transducer_impl_t>          usual_int_transducer_t;
    typedef Element<Transducer<usual_t_int_series_t>, weigthed_int_transducer_impl_t>       numerical_int_transducer_t;


    typedef Element<Automata<usual_int_series_t>, usual_int_int_feature_structure_impl_t>    usual_int_int_feature_structure_t;
    typedef Element<Automata<usual_int_series_t>, usual_int_string_feature_structure_impl_t> usual_int_string_feature_structure_t;


    //    typedef usual_automaton<FreeMonoidBase<M>, instance_value_t> Auto;

//     typedef usual_char_automaton_t SimpleAutomaton<char>;
//     typedef usual_int_automaton_t SimpleAutomaton<unsigned int>;



    class ascii_alphabet :
      public char_letter::Alphabet
    {
    public:
      static ascii_alphabet *instance() {
        if (_instance == 0) {
          _instance = new ascii_alphabet;
        }
        return _instance;
      }

    protected:
      ascii_alphabet() {
	for (unsigned int l = 0; l <= 255; ++l)
	  if (isprint(l))
	    insert(char(l));
      }

    private:
      static ascii_alphabet *_instance;
    };

    ascii_alphabet *ascii_alphabet::_instance = 0;


    class int_alphabet :
      public int_letter::Alphabet
    {
    public:
      static int_alphabet *instance(unsigned int size) {
        if (_instances[size] == 0) {
          _instances[size] = new int_alphabet(size);
        }
        return _instances[size];
      }

    protected:
      int_alphabet(unsigned int size) {
        for (unsigned int i = 2; i < (size + 2); i++)
          insert(i);
      }

    private:
      static std::map<unsigned int, int_alphabet*> _instances;
    };

    std::map<unsigned int, int_alphabet*> int_alphabet::_instances;



  }  // tools

}  // vcsn

# include<minimization_stroppa/usual.hxx>


#endif // ! VCSN_BENCHS_MINIMIZATION_STROPPA_USUAL_ANA_PREDEFS_HH
