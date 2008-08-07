// io.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_TOOLS_IO_HXX
# define VCSN_TOOLS_IO_HXX

# include <vaucanson/tools/io.hh>
# include <sstream>

namespace vcsn
{

  namespace tools
  {

    /*-------.
    | Output |
    `-------*/

    template<typename Auto, typename TransitionConverter, typename Format>
    Auto& automaton_saver_<Auto, TransitionConverter, Format>::automaton()
    {
      return a_;
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    const Auto& automaton_saver_<Auto, TransitionConverter, Format>::
    automaton() const
    {
      return a_;
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    automaton_saver_<Auto, TransitionConverter, Format>::
    automaton_saver_(const Auto& a,
		     const TransitionConverter& c,
		     const Format& f)
      : a_(a), conv_(c), format_(f)
    {}

    template<typename Auto, typename TransitionConverter, typename Format>
    std::ostream&
    operator<<(std::ostream& o,
	       const automaton_saver_<Auto, TransitionConverter, Format>& s)
    {
      TIMER_SCOPED ("automaton output");
      s.format_(o, s, s.conv_);
      return o;
    }

    template<typename S, typename T>
    std::string string_out::operator()(const AutomataBase<S>&, const T& t) const
    {
      std::ostringstream os;
      os << t;
      return os.str();
    }

    template<typename S, typename T>
    std::string string_out::operator()(const TransducerBase<S>&, const T& t) const
    {
      std::ostringstream os;
      os << t;
      return os.str();
    }

  } // ! tools

  template<typename Auto, typename TransitionConverter, typename Format>
  tools::automaton_saver_<Auto, TransitionConverter, Format>
  automaton_saver(const Auto& a,
		  const TransitionConverter& e,
		  const Format& f)
  {
    return tools::automaton_saver_<Auto, TransitionConverter, Format>(a, e, f);
  }

  namespace tools
  {

    /*------.
    | Input |
    `------*/

    template<typename Auto, typename TransitionConverter, typename Format>
    Auto& automaton_loader_<Auto, TransitionConverter, Format>::automaton()
    {
      return a_;
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    const Auto&
    automaton_loader_<Auto, TransitionConverter, Format>::automaton() const
    {
      return a_;
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    automaton_loader_<Auto, TransitionConverter, Format>::
    automaton_loader_(Auto& a,
		      const TransitionConverter& conv,
		      const Format& format,
		      bool merge_states)
      : a_(a),
	conv_(conv),
	format_(format),
	scount_(0),
	smap_(),
	merge_states_(merge_states)
    {}

    template<typename Auto, typename TransitionConverter, typename Format>
    typename Auto::hstate_t
    automaton_loader_<Auto, TransitionConverter, Format>::
    add_state(unsigned s)
    {
      if (smap_.find(s) == smap_.end())
      {
	if (a_.has_state(s) && merge_states_)
	  smap_[s] = hstate_t(s);
	else
	  smap_[s] = a_.add_state();
      }
      return smap_[s];
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    void automaton_loader_<Auto, TransitionConverter, Format>::
    set_initial(unsigned s, const std::string& lbl)
    {
      a_.set_initial(add_state(s), conv_(a_, lbl));
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    void automaton_loader_<Auto, TransitionConverter, Format>::
    set_final(unsigned s, const std::string& lbl)
    {
      a_.set_final(add_state(s), conv_(a_, lbl));
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    void automaton_loader_<Auto, TransitionConverter, Format>::
    add_spontaneous(unsigned from, unsigned to)
    {
      a_.add_spontaneous(add_state(from), add_state(to));
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    void automaton_loader_<Auto, TransitionConverter, Format>::
    add_transition(unsigned from, unsigned to, const std::string& lbl)
    {
      a_.add_series_transition(add_state(from), add_state(to), conv_(a_, lbl));
    }

    template<typename Auto, typename TransitionConverter, typename Format>
    std::istream&
    operator>>(std::istream& in,
	       automaton_loader_<Auto, TransitionConverter, Format> l)
    {
      TIMER_SCOPED ("automaton input");
      l.format_(in, l);
      return in;
    }

  } // ! tools

  template<typename Auto, typename TransitionConverter, typename Format>
  tools::automaton_loader_<Auto, TransitionConverter, Format>
  automaton_loader(Auto& a,
		   const TransitionConverter& e,
		   const Format& f,
		   bool merge_states)
  {
    return tools::automaton_loader_<Auto, TransitionConverter, Format>
      (a, e, f, merge_states);
  }

} // ! vcsn

#endif // ! VCSN_TOOLS_IO_HXX
