// io.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_IO_HXX
# define VCSN_TOOLS_IO_HXX

# include <vaucanson/tools/io.hh>
# include <sstream>

namespace vcsn
{

  namespace io
  {

    /*-------.
    | Output |
    `-------*/

    template<typename Auto, typename EdgeConverter, typename Format>
    Auto& automaton_saver_<Auto, EdgeConverter, Format>::automaton()
    {
      return a_;
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    const Auto& automaton_saver_<Auto, EdgeConverter, Format>::
    automaton() const
    {
      return a_;
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    automaton_saver_<Auto, EdgeConverter, Format>::
    automaton_saver_(const Auto& a,
		       const EdgeConverter& c,
		       const Format& f)
      : a_(a), conv_(c), format_(f)
    {}

    template<typename Auto, typename EdgeConverter, typename Format>
    std::ostream&
    operator<<(std::ostream& o,
	       const automaton_saver_<Auto, EdgeConverter, Format>& s)
    {
      s.format_(o, s, s.conv_);
      return o;
    }

    template<typename A, typename T>
    std::string string_out::operator()(const A&, const T& t) const
    {
      std::ostringstream os;
      os << t;
      return os.str();
    }

  } // io

  template<typename Auto, typename EdgeConverter, typename Format>
  io::automaton_saver_<Auto, EdgeConverter, Format>
  automaton_saver(const Auto& a,
		  const EdgeConverter& e = EdgeConverter(),
		  const Format& f = Format())
  {
    return io::automaton_saver_<Auto, EdgeConverter, Format>(a, e, f);
  }

  namespace io
  {

    /*------.
    | Input |
    `------*/


    template<typename Auto, typename EdgeConverter, typename Format>
    Auto& automaton_loader_<Auto, EdgeConverter, Format>::automaton()
    {
      return a_;
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    const Auto&
    automaton_loader_<Auto, EdgeConverter, Format>::automaton() const
    {
      return a_;
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    automaton_loader_<Auto, EdgeConverter, Format>::
    automaton_loader_(Auto& a,
		      const EdgeConverter& conv,
		      const Format& format,
		      bool merge_states)
      : a_(a),
	conv_(conv),
	format_(format),
	scount_(0),
	smap_(),
	merge_states_(merge_states)
    {}

    template<typename Auto, typename EdgeConverter, typename Format>
    hstate_t automaton_loader_<Auto, EdgeConverter, Format>::
    add_state(unsigned s)
    {
      if (smap_.find(s) == smap_.end())
	{
	  if (a_.has_state(s) && merge_states_)
	    smap_[s] = s;
	  else
	    smap_[s] = a_.add_state();
	}
      return smap_[s];
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    void automaton_loader_<Auto, EdgeConverter, Format>::
    set_initial(unsigned s, const std::string& lbl)
    {
      a_.set_initial(add_state(s), conv_(a_, lbl));
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    void automaton_loader_<Auto, EdgeConverter, Format>::
    set_final(unsigned s, const std::string& lbl)
    {
      a_.set_final(add_state(s), conv_(a_, lbl));
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    void automaton_loader_<Auto, EdgeConverter, Format>::
    add_spontaneous(unsigned from, unsigned to)
    {
      a_.add_spontaneous(add_state(from), add_state(to));
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    void automaton_loader_<Auto, EdgeConverter, Format>::
    add_edge(unsigned from, unsigned to, const std::string& lbl)
    {
      a_.add_series_edge(add_state(from), add_state(to), conv_(a_, lbl));
    }

    template<typename Auto, typename EdgeConverter, typename Format>
    std::istream&
    operator>>(std::istream& in,
	       automaton_loader_<Auto, EdgeConverter, Format> l)
    {
      l.format_(in, l);
      return in;
    }


  }

  template<typename Auto, typename EdgeConverter, typename Format>
  io::automaton_loader_<Auto, EdgeConverter, Format>
  automaton_loader(Auto& a,
		   const EdgeConverter& e = EdgeConverter(),
		   const Format& f = Format(),
		   bool merge_states = false)
  {
    return io::
      automaton_loader_<Auto, EdgeConverter, Format>(a, e, f, merge_states);
  }

} // vcsn


#endif // ! VCSN_TOOLS_IO_HXX
