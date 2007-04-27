// io.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_IO_HH
# define VCSN_TOOLS_IO_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <iostream>
# include <string>
# include <map>

namespace vcsn
{

  namespace io
  {

    /*-------.
    | Output |
    `-------*/

    template<typename Auto, typename TransitionConverter, typename Format>
    struct automaton_saver_
    {
	typedef Auto automaton_t;
	typedef TransitionConverter transition_converter_t;
	typedef Format format_t;

	automaton_saver_(const Auto&, 
			 const TransitionConverter&, 
			 const Format&);

	automaton_t& automaton();
	const automaton_t& automaton() const;

      protected:
	const automaton_t& a_;
	transition_converter_t conv_;
	format_t format_;

	template<typename A, typename E, typename F>
	friend std::ostream&
	operator<<(std::ostream&, const automaton_saver_<A, E, F>&);
    };


    template<typename Auto, typename TransitionConverter, typename Format>
    std::ostream&
    operator<<(std::ostream&,
	       const automaton_saver_<Auto, TransitionConverter, Format>&);

    struct string_out
    {
	std::string check_empty_word(const std::string&) const;

	template<typename S, typename T>
	std::string operator()(const AutomataBase<S>&, const T&) const;

	template<typename S, typename T>
	std::string operator()(const TransducerBase<S>&, const T&) const;

    };

  }

  template<typename Auto, typename TransitionConverter, typename Format>
  io::automaton_saver_<Auto, TransitionConverter, Format>
  automaton_saver(const Auto&,
		  const TransitionConverter& e = TransitionConverter(),
		  const Format& f = Format());


  namespace io
  {
    /*------.
    | Input |
    `------*/

    template<typename Auto, typename TransitionConverter, typename Format>
    struct automaton_loader_
    {
	typedef Auto automaton_t;
	typedef TransitionConverter transition_converter_t;
	typedef Format format_t;

	automaton_loader_(automaton_t& a,
			  const transition_converter_t& conv,
			  const format_t& format,
			  bool merge_states);

	automaton_t& automaton();
	const automaton_t& automaton() const;

	hstate_t add_state(unsigned);
	void set_initial(unsigned, const std::string&);
	void set_final(unsigned, const std::string&);
	void add_transition(unsigned, unsigned, const std::string&);
	void add_spontaneous(unsigned, unsigned);

      protected:
	automaton_t& a_;
	transition_converter_t conv_;
	format_t format_;
	unsigned scount_;
	std::map<unsigned, hstate_t> smap_;
	bool merge_states_;

	template<typename A, typename E, typename F>
	friend std::istream&
	operator>>(std::istream&, automaton_loader_<A, E, F>);
    };

    template<typename Auto, typename TransitionConverter, typename Format>
    std::istream&
    operator>>(std::istream&, automaton_loader_<Auto, TransitionConverter, Format>);


  }


  template<typename Auto, typename TransitionConverter, typename Format>
  io::automaton_loader_<Auto, TransitionConverter, Format>
  automaton_loader(Auto& a,
		   const TransitionConverter& e = TransitionConverter(),
		   const Format& f = Format(),
		   bool merge_states = false);

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/tools/io.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_TOOLS_IO_HH
