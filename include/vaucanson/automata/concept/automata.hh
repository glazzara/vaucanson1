// automata.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/slots.hh>

namespace vcsn {

  template <class Series>
  struct Automata;
  
  template <class Series>
  struct dynamic_traits<Automata<Series> >
    : dynamic_traits<AutomataBase<Automata<Series> > >
  {
    static const bool ret = dynamic_traits<Series>::ret;    
  };
  
  template <class Series, typename T>
  struct MetaElement<Automata<Series>, T>
    : MetaElement<AutomataBase<Automata<Series> >, T>
  {};

  template <class Series>
  struct virtual_types<Automata<Series> >
    : virtual_types<AutomataBase<Automata<Series> > >
  {
    typedef Series		series_t;
  };


  template <class Series>
  class Automata
    : public AutomataBase<Automata<Series> >
  {
  public:
    typedef Automata<Series>				     self_t;
    typedef Series series_t;

    Automata(const series_t&);

    const series_t&	series() const;

  private:
    SetSlot<series_t> series_;
  };

  template <class Series>
  bool
  operator==(const Automata<Series>&, const Automata<Series>&);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/automata.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
