// usual_io.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_USUAL_IO_HXX
# define VCSN_TOOLS_USUAL_IO_HXX

# include <vaucanson/tools/usual_io.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <vaucanson/algorithms/finite_support_conversion.hh>
# include <sstream>

namespace vcsn
{
  namespace io
  {
    template<typename ExpType>
    template<typename Auto>
    std::string
    usual_converter_poly<ExpType>::
    operator()(const Auto& a,
	       const typename Auto::series_set_elt_t& p) const
    {
      ExpType e = ExpType(a.structure().series());
      finite_support_convert(e, p);
      std::ostringstream os;
      os << e;
      return os.str();
    }

    template<typename ExpType>
    template<typename Auto>
    typename Auto::series_set_elt_t
    usual_converter_poly<ExpType>::operator()(const Auto& a,
					      const std::string& str) const
    {
      ExpType e = ExpType(a.structure().series());
      algebra::parse(str, e);
      typename Auto::series_set_elt_t s =
	typename Auto::series_set_elt_t(a.structure().series());
      finite_support_convert(s, e);
      return s;
    }

    template<typename Auto>
    std::string
    usual_converter_exp::operator()(const Auto& a,
				    const typename Auto::series_set_elt_t& e) const
    {
      std::ostringstream os;
      os << e;
      return os.str();
    }

    template<typename Auto>
    typename Auto::series_set_elt_t
    usual_converter_exp::operator()(const Auto& a, const std::string& s) const
    {
      typedef typename Auto::series_set_elt_t exp_t;
      exp_t ret = exp_t(a.structure().series());
      algebra::parse(s, ret);
      return ret;
    }

  }

}

#endif // ! VCSN_TOOLS_USUAL_IO_HXX
