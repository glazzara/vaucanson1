#include <vaucanson/misc/unique.hh>
#include <vaucanson/misc/unique.hcc>
#include <cassert>
#include <set>
#include <string>

#define MAXITER 10000

struct A {};
std::string tag;
bool operator==(const A&, const A&)
{
  tag += "A";
  return true;
}

int main()
{
  std::set<const int*> s;
  
  for (int i = 0; i < MAXITER; ++i)
    {
      const int *p = & utility::unique::get(i);
      assert(s.find(p) == s.end());
      s.insert(p);
    }

  const A *p1 = & utility::unique::get(A());
  const A *p2 = & utility::unique::get(A());
  const A *p3 = & utility::unique::get(A());
  assert(tag.size() != 0);
  assert(p1 == p2 && p2 == p3);
  return 0;
}
