// cpp_code.hh
//
//
#ifndef SPEC_CPP_CODE_HH
# define SPEC_CPP_CODE_HH

# include <list>
# include <string>
# include <map>

namespace spec {

class CppParamCode
{
public :
  typedef std::string				code_t;
  typedef std::string				param_t;
  typedef std::string				value_t;
  typedef std::list<param_t>			param_set_t;
  typedef std::map<param_t, value_t>		param_value_t;

public :
  CppParamCode();
  CppParamCode(const std::string& param_code);

  const param_set_t& params() const
  { return parameters_; }

  const code_t
  instanciated_code(const param_value_t& values) const;
  
private :
  param_set_t		parameters_;
  code_t		param_code_;
};

} // spec

#endif // SPEC_CPP_CODE_HH
