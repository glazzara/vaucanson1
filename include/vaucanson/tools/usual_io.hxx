// usual_io.hxx: this file is part of the Vaucanson project.
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
