#ifndef CONSTANTS_INF_HH
#define CONSTANTS_INF_HH

namespace vcsn
{
  namespace vauc
  {
    struct Inf 
    {
      bool negated;
      Inf operator-() const
      {
	Inf res;
	res.negated = !(this->negated);
	return res;
      }
    };
  }
}
    

#endif
