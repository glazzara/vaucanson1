#include <vaucanson/misc/unique.hh>
#include <cassert>
#include <set>
#include <string>

#define MAXITER 10000

struct I : public utility::unique::unifiable
{
  I(int x) : x_(x) {}

  int x_;
};
bool operator==(const I& i1, const I& i2)
{ return i1.x_ == i2.x_; }

struct A : public utility::unique::unifiable 
{ };

std::string tag;
bool operator==(const A&, const A&)
{
  tag += "A";
  return true;
}

int main()
{
  std::set<const I*> s;
  
  for (int i = 0; i < MAXITER; ++i)
    {
      const I *p = & utility::unique::get(I(i));
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
