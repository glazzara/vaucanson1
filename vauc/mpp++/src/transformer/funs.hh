#ifndef TR_FUNS_HH
#define TR_FUNS_HH

#include <cctype>
#include <sstream>
#include <algorithm>


static inline std::string norm(const std::string& in)
{
  std::ostringstream s;
  for (std::string::const_iterator i = in.begin();
       i != in.end();
       ++i)
    {
      if (((i - in.begin()) > 0) && isupper(*i))
	s << '_';
      s << *i;
    }
  return s.str();
}

static inline std::string upper(const std::string& in)
{
  std::ostringstream s;
  for (std::string::const_iterator i = in.begin();
       i != in.end();
       ++i)
    s << char(toupper(*i));
  return s.str();
}

static inline std::string lower(const std::string& in)
{
  std::ostringstream s;
  for (std::string::const_iterator i = in.begin();
       i != in.end();
       ++i)
    s << char(tolower(*i));
  return s.str();
}
 
static inline std::string make_type(const std::string& in)
{
  std::ostringstream n;
  n << "TYPE(";
  for (std::string::const_iterator i = in.begin();
       i != in.end();
       ++i)
      if (*i == '.')
	n << ",";
      else
	n << char(tolower(*i));
  n << ")";
  return n.str();
}

static inline std::string make_type2(const std::string& in)
{
  std::ostringstream n;
  for (std::string::const_iterator i = in.begin();
       i != in.end();
       ++i)
      if (*i == '.')
	{
	  std::string s = n.str();
	  n << "/" << s << "_t_";
	}
      else
	n << char(tolower(*i));
  return n.str();
}
 
static inline std::string transform(const std::string& in)
{
  if (std::find(in.begin(), in.end(), '.') != in.end())
    return make_type(in);
  return in;
}

static inline std::string transform2(const std::string& in)
{
  if (std::find(in.begin(), in.end(), '.') != in.end())
    return make_type2(in);
  return "";
}

static inline std::string escape(const std::string& in)
{
  std::string out;
  for (std::string::const_iterator i = in.begin();
       i != in.end();
       ++i)
    {
      if (*i == '\n')
	out += " \\";
      out += *i;
    }
  return out;
}



#endif
