#include "mangling.hh"
#include <utility>
#include <sstream>
#include <stdexcept>
#include <cstring>

Mangler::Mangler(const char *punct)
  : counter_(1), punct_(punct), mangled_(), table_()
{ }

void Mangler::inc()
{ mangled_ += punct_[0]; }

void Mangler::dec()
{ mangled_ += punct_[1]; }

void Mangler::sep()
{ mangled_ += punct_[0]; mangled_ += punct_[1]; }

std::string Mangler::mangled() const
{ 
  std::ostringstream prefix;

  for (std::map<std::string, unsigned>::const_iterator i = table_.begin();
       i != table_.end();
       ++i)
    prefix << counter_repr(i->second) << i->first << punct_[3]; 

  return prefix.str() + punct_[2] + mangled_; 
}

void Mangler::append(const std::string& component)
{
  unsigned s = table_[component];
  table_[component] = s ? s : (s = counter_++);
  mangled_ += counter_repr(s);
}

char Mangler::counter_repr(unsigned i)
{
  if (i < 10)
    return '0' + i;
  if (i < 36)
    return i - 10 + 'a';
  if (i < 62)
    return i - 36 + 'A';
  if (i == 62)
    return '_';
  if (i == 63)
    return '$';
  throw std::logic_error("too many parts");
}  

unsigned Mangler::counter_of(char repr)
{
  if (repr >= '0' && repr <= '9')
    return repr - '0';
  if (repr >= 'a' && repr <= 'z')
    return repr - 'a' + 10;
  if (repr >= 'A' && repr <= 'Z')
    return repr - 'A' + 36;
  if (repr == '_')
    return 62;
  if (repr == '$')
    return 63;
  throw std::invalid_argument("unknown part number");
}

std::string Mangler::demangle(const std::string& mangled) 
{
  std::ostringstream st;
  table_.clear();

  unsigned pos;
  for (pos = 0; pos < mangled.size() && mangled[pos] != punct_[2]; ++pos)
    {
      counter_ = counter_of(mangled[pos]);
      for (mangled_.clear(), ++pos; 
	   pos < mangled.size() && mangled[pos] != punct_[3];
	   mangled_ += mangled[pos++]);
      if (pos >= mangled.size())
	throw std::logic_error("incomplete part list");
      table_[mangled_] = counter_;
    }
  if (pos >= mangled.size())
    throw std::logic_error("incomplete type");
  for (++pos; pos < mangled.size(); ++pos)
    {
      if (mangled[pos] != punct_[0] && mangled[pos] != punct_[1])
	{
	  for (std::map<std::string, unsigned>::const_iterator i = table_.begin();
	       i != table_.end();
	       ++i)
	    if (i->second == counter_of(mangled[pos]))
	      st << i->first;
	}
      else
	st << mangled[pos];
    }
	  
  return st.str();
}

#include <iostream>
#include <cassert>

std::string Mangler::escape(const std::string& in, char what, char with)
{
  assert(with != what);
  assert(with != '0');
  assert(with != '1');
  std::ostringstream out;
  for (unsigned s = 0; s < in.size(); ++s)
    if (in[s] == what || in[s] == with)
      out << with << (char)((in[s] == what) ? (('0' == what) ? '1' : '0') : with);
    else
      out << in[s];
  return 'x' + out.str();
}

std::string Mangler::unescape(const std::string& in, char what, char with)
{
  assert(with != what);
  std::ostringstream out;
  for (unsigned s = 1; s < in.size(); ++s)
    {
      if (in[s] == with && s < in.size() - 1)
	out << ((in[++s] == with) ? with : what);
      else
	out << in[s];
    }
  return out.str();
}

extern "C" void compress2(char *, unsigned long *, const char *, unsigned long, int);
extern "C" int uncompress(char *, unsigned long *, const char *, unsigned long);

std::string Mangler::unzip64(const std::string& s) 
{
  unsigned pos;
  std::ostringstream inc;
//   unsigned long l;
  unsigned j, heads;
  for (pos = 0; pos < s.size(); pos += 3)
    {
      heads = counter_of(s[pos++]);
      for (j = pos; j < s.size() && j < pos + 3; ++j)
	{
	  unsigned v = (heads << (2 + ((j - pos) * 2))) & 0xc0 ;
	  v = v | counter_of(s[j]);
	  inc << (char)v;
	}
    }
  char out[1024];
  unsigned long len = 1024;
  if (uncompress(out, &len, inc.str().c_str(), inc.str().size()) < 0)
    throw std::logic_error("corrupted data");
  return std::string(out, len);
}

std::string Mangler::zip64(const std::string& s, int comp_level)
{
  char out[1024];
  unsigned long len = 1024;
  compress2(out, &len, s.c_str(), s.size(), comp_level);

  std::ostringstream st;
  unsigned j, heads;
  unsigned pos;
  for (pos = 0; pos < len; pos += 3)
    {
      for (heads = 0, j = pos; j < len && j < pos + 3; ++j)      
	heads = heads | ((out[j] & 0xc0) >> (2 + ((j - pos) * 2)));
      st << counter_repr(heads);
      for (j = pos; j < len && j < pos + 3; ++j)
	{
	  st << counter_repr(out[j] & 0x3f);
	}
    }
  return st.str();
}

