// bencher.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_TOOLS_BENCHER_HXX
# define VCSN_TOOLS_BENCHER_HXX

# include <vaucanson/tools/bencher.hh>

namespace vcsn
{

  bencher::bencher() : start_(0), stop_(0)
  {}

  bencher::~bencher()
  {}

  void bencher::start()
  { start_ = dtime(); }


  void bencher::stop()
  { stop_ = dtime(); }


  double bencher::get_time()
  { return stop_ - start_; }

  double	bencher::dtime()
  {
    double		q;
    struct rusage	rusage;

    getrusage(RUSAGE_SELF, &rusage);
    q = (double)(rusage.ru_utime.tv_sec);
    q = q + (double)(rusage.ru_utime.tv_usec) * 1.0e-06;
    return q;
  }
}
#endif // VCSN_TOOLS_BENCHER_HXX
