#ifndef MODULE_MANGLING_HH
#define MODULE_MANGLING_HH

#include <string>
#include <map>

/* 
   Example use.

   Given a function ret_t foo(bar<yay>,baz), mangling is done by:
      Mangler m;
      m.append("foo");
      m.sep();
      m.append("bar");
      m.inc();
      m.append("yay");
      m.dec();
      m.sep();
      m.append("baz");
      m.sep();
      m.append("ret_t");

   std::cout << "mangled name = " << m.mangled() << std::endl;
   std::cout << "compressed mangled = " << m.zip64(m.mangled()) << std::endl;
   std::cout << "identifier mangled = " << m.escape(m.zip64(m.mangled())) << std::endl;

   You can revert the operations by using unescape, unzip64 and demangle.

NOTES:
   m.demangle(m.mangled()) is compresses better than m.mangled(). Go figure.

   the output of m.demangle(...) is human-readable
   the output of m.mangle(...) is nearly human-readable
   the output of m.zip64(...) is clearly not human-readable.

*/

class Mangler
{
public:
  Mangler(const char *punct = "()-~");

  // augment one level in parameter depth
  void inc();
  // ...
  void dec();
  // insert a separator (between a function name and argument types)
  void sep();

  // Insert a component
  void append(const std::string& component);


  // get the mangled representation
  std::string mangled() const;
  // demangle a representation (throws on error)
  std::string demangle(const std::string& mangled);

  // compress a string to another (throws on error), output uses charset [0-9a-zA-Z_$] only 
  static std::string zip64(const std::string& s, int level = 9);
  // decompress a string to another (throws on error)
  static std::string unzip64(const std::string& s);

  // theses function can be used to reduce charset [0-9a-zA-Z_$] to [0-9a-zA-Z_] suitable
  // for C/C++ identifiers ($ is not a valid identifier character)
  static std::string escape(const std::string& st, char what = '$', char with = '_');
  static std::string unescape(const std::string& st, char what = '$', char with = '_');

protected:
  static char counter_repr(unsigned c);
  static unsigned counter_of(char repr);
  unsigned counter_;
  const char *punct_;
  std::string mangled_;
  std::map<std::string, unsigned> table_;
};



#endif
