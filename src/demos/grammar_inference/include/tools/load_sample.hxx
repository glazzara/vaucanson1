// load_sample.hxx

#ifndef   LOAD_SAMPLE_HXX_
# define   LOAD_SAMPLE_HXX_

#include <set>
#include <iostream>
#include <fstream>
#include <utility>

// very simple code
// FIXME: parametrize it with an alphabet
template <typename W>
std::pair<std::set<W>, std::set<W> >
load_samples(SELECTOR(W), const char* name_file)
{
  typedef std::set<W> sample_t;
  typedef typename W::value_t value_t;

  // FIXME: static check

  std::ifstream is;
  char c;
  bool first = true;

  sample_t i_plus;
  sample_t i_minus;
  sample_t* ptr_sample;
  value_t str;

  is.open(name_file);

  while (is.good())     
    {
      c = is.get();     
      

      switch (c)
	{
	case ' ' : 
	  {
	    break;
	  }
	case '\n' :
	  {
	    first = true;
	    break;
	  }
	case 'a' : 
	  {
	    if (first)
	      {
		ptr_sample = &i_plus;
		first = false;
	      }
	    else
	      str += 'a';
	    break;
	  }
	case 'b' :
	  {
	    if (first)
	      {
		ptr_sample = &i_minus;
		first = false;
	      }
	    else
	      str += 'b';
	    break;
	  }
	}

      if (first)
	{
	  if (str.size())
	    ptr_sample->insert(str);
	  str = "";
	}
    }

  is.close();           

  return std::pair<sample_t, sample_t>(i_plus, i_minus);
}



#endif /* !LOAD_SAMPLE_HXX_ */
