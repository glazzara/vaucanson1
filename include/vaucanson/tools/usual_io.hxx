#ifndef USUAL_IO_HXX
# define USUAL_IO_HXX

# include <vaucanson/tools/usual_io.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
# include <vaucanson/algorithms/finite_support_conversion.hh>
# include <sstream>

namespace vcsn
{
  namespace io
  {
    template<typename ExpType>
    template<typename Auto>
    std::string usual_converter_poly<ExpType>::operator()(const Auto& a, const typename Auto::serie_t& p) const
    {
      ExpType e = ExpType(a.set().series());
      finite_support_convert(e, p);
      std::ostringstream os;
      os << e;
      return os.str();
    }

    template<typename ExpType>
    template<typename Auto>
    typename Auto::serie_t usual_converter_poly<ExpType>::operator()(const Auto& a, const std::string& str) const
    {
      ExpType e = ExpType(a.set().series());
      algebra::parse(str, e);
      typename Auto::serie_t s = typename Auto::serie_t(a.set().series());
      finite_support_convert(s, e);
      return s;
    }

    template<typename Auto>
    std::string usual_converter_exp::operator()(const Auto& a, const typename Auto::serie_t& e) const
    {
      std::ostringstream os;
      os << e;
      return os.str();
    }

    template<typename Auto>
    typename Auto::serie_t usual_converter_exp::operator()(const Auto& a, const std::string& s) const
    {
      typedef typename Auto::serie_t exp_t;
      exp_t ret = exp_t(a.set().series());
      algebra::parse(s, ret);
      return ret;
    }

  }


}

#endif
