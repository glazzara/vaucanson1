// arg.hh: this file is part of the Vaucanson project.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_DEMOS_FSM_USUAL_AUTOMATON_T_ARG_HH
# define VCSN_DEMOS_FSM_USUAL_AUTOMATON_T_ARG_HH

# include <list>
# include <map>
# include <vector>
# include <string>

namespace toolbox {

  enum option_type_e
    {
      o_string,
      o_int,
      o_none
    };
  
  struct Options 
  {
    std::string		name;
    option_type_e	type;
    std::string		descr;
    bool		optional;
  };

  union option_value_u
  {
    std::string*	string_value;
    int			int_value;
  };

  struct option_value
  {
    option_type_e	type;
    option_value_u      value;
  };

  class OptionsValues
  {
  public:
    OptionsValues(const std::vector<Options>& options, 
		  unsigned argc, 
		  const char**argv);

    bool				get(std::string name) const;
    const int*	      			get_int(std::string name) const;
    const std::string*		       	get_string(std::string name) const;
    std::list<std::string>		get_remainder() const;
    void				usage_msg(void) const;

  private:
    static std::string			type_to_label(option_type_e);
    std::map<std::string, option_value>	values_;  
    const char**			argv_;
    unsigned				argc_;
    const std::vector<Options>		options_;
    std::list<std::string>		remainder_;
  };


} // toolbox

#endif // ! VCSN_DEMOS_FSM_USUAL_AUTOMATON_T_ARG_HH
