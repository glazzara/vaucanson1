// arg.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_DEMOS_UTILITIES_FSM_ARG_HH
# define VCSN_DEMOS_UTILITIES_FSM_ARG_HH

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

#endif // ! VCSN_DEMOS_UTILITIES_FSM_ARG_HH