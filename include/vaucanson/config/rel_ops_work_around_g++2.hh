// rel_ops_work_around_g++2.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_CONFIG_REL_OPS_WORK_AROUND_GXX2_HH
# define VCSN_CONFIG_REL_OPS_WORK_AROUND_GXX2_HH

#if (defined __GNUC__) && (__GNUC__ < 3) 
namespace std {
# include <vaucanson/config/system.hh>
# include <map>  
# include <set>
# include <vector>
# include <utility>

  template <class T_>
  bool operator!=(const std::set<T_>& lhs, const std::set<T_>& rhs)
  {
    return !(lhs == rhs);
  }

  template <class T_>
  bool operator<=(const std::set<T_>& lhs, const std::set<T_>& rhs)
  {
    return (lhs < rhs) || (lhs == rhs);
  } 


  template <class T_>
  bool operator>(const std::set<T_>& lhs, const std::set<T_>& rhs)
  {
    return !(lhs <= rhs);
  }

  template <class T_>
  bool operator>=(const std::set<T_>& lhs, const std::set<T_>& rhs)
  {
    return !(lhs < rhs);
  }


  template <class T_>
  bool operator!=(const std::vector<T_>& lhs, 
		  const std::vector<T_>& rhs)
  {
    if (lhs.size() != rhs.size())
      return false;
    for (unsigned i = 0; i < lhs.size(); ++i)
      if (lhs[i] != rhs[i])
	return false;
    return true;
  }

  template <class T_, class P_>
  bool operator!=(const std::pair<T_, P_>& lhs, 
		  const std::pair<T_, P_>& rhs)
  {
    return ((lhs.first != rhs.first) || (lhs.second != rhs.second));
  }

  template <class T_>
  bool operator!=(const std::reverse_iterator<T_>& lhs, const std::reverse_iterator<T_>& rhs)
  {
    return !(lhs == rhs);
  }

} // std

#endif

#endif // VCSN_CONFIG_REL_OPS_WORK_AROUND_GXX2_HH
