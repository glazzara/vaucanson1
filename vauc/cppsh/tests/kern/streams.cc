#include "kern/stdstreams.hh"
#include <cassert>

using namespace cppsh;

int main()
{
  Stream cin = Stream(sslot_of_cin());
  Stream cout = Stream(sslot_of_cout());
  Stream cerr = Stream(sslot_of_cerr());

  assert(cin.kind() == StreamSlot::input);
  assert(cout.kind() == StreamSlot::output);
  assert(cerr.kind() == StreamSlot::output);

  assert(&cin.as_istream() != NULL);
  assert(&cout.as_istream() == NULL);
  
  std::ostream& o = cout.as_ostream();
  o << "hello world" << std::endl;
}
