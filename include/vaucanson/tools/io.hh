// io.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_IO_HH
# define VCSN_TOOLS_IO_HH

# include <vaucanson/automata/concept/handlers.hh>
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

    template<typename Auto, typename EdgeConverter, typename Format>
    struct automaton_saver_
    {
      typedef Auto automaton_t;
      typedef EdgeConverter edge_converter_t;
      typedef Format format_t;

      automaton_saver_(const Auto&, const EdgeConverter&, const Format&);

      automaton_t& automaton();
      const automaton_t& automaton() const;

    protected:
      const automaton_t& a_;
      edge_converter_t conv_;
      format_t format_;

      template<typename A, typename E, typename F>
      friend std::ostream&
      operator<<(std::ostream&, const automaton_saver_<A, E, F>&);
    };


    template<typename Auto, typename EdgeConverter, typename Format>
    std::ostream&
    operator<<(std::ostream&,
	       const automaton_saver_<Auto, EdgeConverter, Format>&);

    struct string_out
    {
      template<typename A, typename T>
      std::string operator()(const A&, const T&) const;
    };

  }

  template<typename Auto, typename EdgeConverter, typename Format>
  io::automaton_saver_<Auto, EdgeConverter, Format>
  automaton_saver(const Auto&,
		  const EdgeConverter& e = EdgeConverter(),
		  const Format& f = Format());


  namespace io
  {
    /*------.
    | Input |
    `------*/

    template<typename Auto, typename EdgeConverter, typename Format>
    struct automaton_loader_
    {
      typedef Auto automaton_t;
      typedef EdgeConverter edge_converter_t;
      typedef Format format_t;

      automaton_loader_(automaton_t& a,
			const edge_converter_t& conv,
			const format_t& format,
			bool merge_states);

      automaton_t& automaton();
      const automaton_t& automaton() const;

      hstate_t add_state(unsigned);
      void set_initial(unsigned, const std::string&);
      void set_final(unsigned, const std::string&);
      void add_edge(unsigned, unsigned, const std::string&);
      void add_spontaneous(unsigned, unsigned);

    protected:
      automaton_t& a_;
      edge_converter_t conv_;
      format_t format_;
      unsigned scount_;
      std::map<unsigned, hstate_t> smap_;
      bool merge_states_;

      template<typename A, typename E, typename F>
      friend std::istream&
      operator>>(std::istream&, automaton_loader_<A, E, F>);
    };

    template<typename Auto, typename EdgeConverter, typename Format>
    std::istream&
    operator>>(std::istream&, automaton_loader_<Auto, EdgeConverter, Format>);


  }


  template<typename Auto, typename EdgeConverter, typename Format>
  io::automaton_loader_<Auto, EdgeConverter, Format>
  automaton_loader(Auto& a,
		   const EdgeConverter& e = EdgeConverter(),
		   const Format& f = Format(),
		   bool merge_states = false);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/tools/io.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_TOOLS_IO_HH
