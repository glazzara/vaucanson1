// bencher.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//

#ifndef VCSN_TOOLS_BENCHER_HH
# define VCSN_TOOLS_BENCHER_HH

# ifdef VCSN_BENCH

#  include <sys/time.h>
#  include <sys/resource.h>
#  include <stdio.h>
#  include <string.h>
#  include <stdlib.h>
#  include <time.h>
#  include <iostream>
#  include <vector>
#  include <string>
#  include <utility>

namespace vcsn
{
  class bencher {
    public:
      bencher();
      ~bencher();

    public:
      void	start();
      void	stop();
      double	get_time();

    private:
      double	dtime();

      double	start_;
      double	stop_;
  };

  unsigned int					n_bench_indent;
  std::vector<bencher*>				v_benchers;
  std::vector< std::pair<int, bencher*> >	v_old_benchers;

#  define VCSN_BENCH_START_QUIET					\
  {									\
    v_benchers.push_back(new bencher);					\
    v_benchers.back()->start();						\
  }

#  define VCSN_BENCH_START						\
  {									\
    v_benchers.push_back(new bencher);					\
    v_benchers.back()->start();						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      "Start bench in " << __FUNCTION__ << "..." << std::endl;		\
    n_bench_indent += 3;						\
  }

#  define VCSN_BENCH_STOP_QUIET(Result)					\
  {									\
    v_benchers.back()->stop();						\
    Result = v_benchers.back()->get_time();				\
    delete v_benchers.back();						\
    v_benchers.pop_back();						\
  }

#  define VCSN_BENCH_STOP						\
  {									\
    v_benchers.back()->stop();						\
    v_old_benchers.insert(v_old_benchers.begin(),			\
			  std::pair<int, bencher*>(n_bench_indent,	\
						   v_benchers.back()));	\
    n_bench_indent -= 3;						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      "Stop bench in " << __FUNCTION__ << "..." << std::endl;		\
    v_benchers.pop_back();						\
  }

#  define VCSN_BENCH_PRINT						\
  {									\
    std::cerr << std::string(v_old_benchers.back().first, ' ') <<	\
      __FUNCTION__ << ": " <<						\
      v_old_benchers.back().second->get_time() << std::endl;		\
    delete v_old_benchers.back().second;				\
    v_old_benchers.pop_back();						\
  }

#  define VCSN_BENCH_STOP_AND_PRINT					\
  {									\
    v_benchers.back()->stop();						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      __FUNCTION__ << ": " <<						\
      v_benchers.back()->get_time() << std::endl;			\
    n_bench_indent -= 3;						\
    std::cerr << std::string(n_bench_indent, ' ') <<			\
      "Stop bench in " << __FUNCTION__ << "..." << std::endl;		\
    delete v_benchers.back();						\
    v_benchers.pop_back();						\
  }

} // vcsn



#  ifndef VCSN_USE_INTERFACE_ONLY
#   include <vaucanson/tools/bencher.hxx>
#  endif // VCSN_USE_INTERFACE_ONLY

# else // VCSN_BENCH

#  define VCSN_BENCH_START
#  define VCSN_BENCH_STOP
#  define VCSN_BENCH_PRINT
#  define VCSN_BENCH_STOP_AND_PRINT

# endif // ! VCSN_BENCH
#endif // ! VCSN_TOOLS_BENCHER_HH
