// usual_io.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_USUAL_IO_HH
# define VCSN_TOOLS_USUAL_IO_HH

# include <string>

namespace vcsn
{
  namespace io
  {
    struct usual_converter_exp
    {
      template<typename Auto>
      typename Auto::series_set_elt_t operator()(const Auto&, const std::string& lbl) const;
      template<typename Auto>
      std::string operator()(const Auto&, const typename Auto::series_set_elt_t& exp_series) const;
    };

    template<typename ExpType>
    struct usual_converter_poly
    {
      template<typename Auto>
      typename Auto::series_set_elt_t operator()(const Auto&, const std::string& lbl) const;
      template<typename Auto>
      std::string operator()(const Auto&, const typename Auto::series_set_elt_t& poly_series) const;
    };
  }
}


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/tools/usual_io.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_TOOLS_USUAL_IO_HH
