// rel_ops_work_around_g++2.hh
//
// $Id$
// VCSN_HEADER
#ifndef REL_OPS_WORK_AROUND_GXX2_HH
# define REL_OPS_WORK_AROUND_GXX2_HH

namespace std {
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


#endif // REL_OPS_WORK_AROUND_GXX2_HH
