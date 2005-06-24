// tools.hxx: this file is part of the Vaucanson project.
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
#include <vector>
#include <fstream>


namespace ana {


  namespace misc {

    template<typename Word, typename Weight>
    std::pair< std::vector<Word>, std::vector<Weight> >
    file_to_vector_pair(const char *file_name)
    {
      std::vector<Word>		words;
      std::vector<Weight>	weights;

      std::ifstream input_file(file_name);

      while (input_file) {
	Word	word;
	Weight	weight;
	input_file >> word >> weight;
	words.push_back(word);
	weights.push_back(weight);
      }

      input_file.close();
      words.pop_back();
      weights.pop_back();

      return std::pair<std::vector<Word>, std::vector<Weight> >(words, weights);
    }


    template<typename Word>
    std::vector<Word>
    file_to_vector(const char *file_name)
    {
      std::vector<Word>		words;

      std::ifstream input_file(file_name);

      while (input_file) {
	Word	word;
	input_file >> word;
	words.push_back(word);
      }

      input_file.close();
      words.pop_back();

      return words;
    }


  }




//    namespace misc_tools {

//      template <class C>
//      std::vector<C> file_to_vector(std::ifstream& input) {
//        std::vector<C> vec;
//        while (input) {
//  	C val;
//  	input >> val;
//  	vec.push_back(val);
//        }

//        return vec;
//      }

//      template <class C>
//      std::vector<C> file_to_vector(const char *input) {
//        std::vector<C> vec;
//        std::ifstream f_input(input);

//        while (f_input) {
//  	C val;
//  	f_input >> val;
//  	vec.push_back(val);
//        }

//        f_input.close();
//        return vec;
//      }

//      void fsm_acceptor_to_fsm_transducer(std::ifstream& input, std::ofstream& output) {

//        // BUG: last line with a single NL is not correctly handled

//        std::string field1, field2, field3, field4;
//        char sep;

//        while (input) {
//  	input >> field1 >> field2;

//  	input.get(sep);

//  	if (sep == 9) {  // -> not a final state
//  	  input >> field3 >> field4;
//  	  if (field3 == "1") {  // epsilon transition
//  	    output << field1 << "\t" << field2 << "\t" << "\t<eps>\t<eps>\t" << field4 << "\n";
//  	  }
//  	  else {
//  	    output << field1 << "\t" << field2 << "\t" << field3 << "\t<eps>\t" << field4 << "\n";
//  	    output << field1 << "\t" << field2 << "\t<eps>\t" << field3 << "\t" << field4 << "\n";
//  	  }
//  	}
//  	else {  // -> final state
//  	  output << field1 << "\t" << field2 << "\n";
//  	}

//        }
//      }

//      void word_to_fsm(const std::string& word, std::ofstream& fsm_file) {
//        for (unsigned i=0; i < word.size(); i++) {
//  	fsm_file << i << "\t" << i+1 << "\t" << word[i] << "\t0\n";
//        }
//        fsm_file << word.size() << "\t0\n";
//      }

//    }  // misc_tools

}  // ana

