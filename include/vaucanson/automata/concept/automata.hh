// automata.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and 
// Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/internal/traits.hh>

namespace vcsn {

  template <class Series>
  struct Automata;
  
  template <class Series>
  struct MetaSet<Automata<Series> >
  {
    static const bool dynamic_set = MetaSet<Series>::dynamic_set;    
  };
  
  template <class Series, typename T>
  struct MetaElement<Automata<Series>, T>
    : MetaElement<AutomataBase<Automata<Series> >, T>
  {};

  namespace traits {
    
    template <class Series>
    struct virtual_types<Automata<Series> >
    {
      typedef Series		series_t;
    };
    
  } // traits.


  template <class Series>
  class Automata
    : public AutomataBase<Automata<Series> >
  {
  public:
    typedef Automata<Series>				     self_t;
    typedef typename traits::virtual_types<self_t>::series_t series_t;

    Automata(const series_t&);

    const series_t&	series() const;

  private:
    series_t	series_;
  };

} // vcsn

# include <vaucanson/automata/concept/automata.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH

