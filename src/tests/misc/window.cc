// window.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

#include <vaucanson/misc/random.hh>
#include <vaucanson/misc/special_char_traits.hh>
#include <vaucanson/misc/window.hh>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

/*-------.
| append |
`-------*/

// Multiple  versions  of append  are  here  to  test Window  both  on
// std::basic_string and std::vector.

template <class Letter, typename S, typename T>
void
append(std::basic_string<Letter, S, T>& s, const Letter l)
{
  s += l;
}

template <class Letter, typename T>
void
append(std::vector<Letter, T>& s, const Letter l)
{
  s.push_back(l);
}

/*------------.
| test_window |
`------------*/

template <class String, class Letter, int Size, int Length>
void
test_window(const Letter weol)
{
  using namespace utility;
  typedef Window<typename String::const_iterator, Letter>	window_t;
  typedef typename window_t::iterator_t				iterator_t;

  // String initialization.
  String	wstring;
  for (int i = 0; i < Size; ++i)
    {
      for (int j = 0; j < i; ++j)
	append(wstring, Letter (j % 10 + weol + 1));
      append(wstring, weol);
    }

  window_t	w(wstring.begin(), wstring.end(), weol, Length);

  // Test accessors.
  assert(w.begin() == wstring.begin());
  assert(w.end() == wstring.end());
  assert(w.eol_value() == weol);
  assert(w.length() == Length);

  // The created window should be empty as the string begins with an eol.
  assert(w.eol());
  assert(w.window() == std::basic_string<Letter>());
  assert(!w.eof());
  assert(w.size() == 0);
  assert(w.offset() == 0);

  // The following window should be 1 character long.
  w.shift();
  assert(!w.eof());
  assert(!w.eol());
  assert(w.size() == 1);
  assert(w.offset() == 1);

  // shift until a window which size is Length is reached.
  for (unsigned i = 2; i <= Length; ++i)
    {
      w.shift(); // After this shift, the window has reached the end of the line
	         // and is empty.
      w.shift(); // This shift jump to next line.
      assert(w.size() == i);
    }

  // Save position.
  iterator_t	saved_pos	= w.stream();
  size_t	saved_offset	= w.offset();

  // This loop is primary designed to test the moveto method.
  for (int pass = 0; pass < 3; ++pass)
    {
      // Test the content of the window.
      for (int i = 0; i < Length; ++i)
	assert(w[i] == wstring[w.offset() + i]);

      // Since  the window  should match  exactly the  content  of the
      // line, shifting it should lead us to an empty window.
      w.shift();
      assert(w.eol());
      assert(w.size() == 0);

      // The next window should be on a line which length is Length + 1.
      w.shift();
      assert(w.size() == Length);
      assert(!w.eol());
      for (int i = 0; i < Length; ++i)
	assert(w[i] == Letter(i % 10 + weol + 1));
      w.shift();
      assert(w.size() == 1);
      assert(w[0] == Letter(Length % 10 + weol + 1));
      assert(w.window()[0] == Letter(Length % 10 + weol + 1));
      w.shift();
      assert(w.eol());

      // Try to reach the end of the stream, with a timeout.
      unsigned int timeout;
      for (timeout = 0; !w.eof() and (timeout < Size * Size / Length); ++timeout)
	w.shift();
      assert(timeout < Size * Size / Length);

      // Finaly, test accessors again.
      assert(w.begin() == wstring.begin());
      assert(w.end() == wstring.end());
      assert(w.eol_value() == weol);
      assert(w.length() == Length);

      // Use moveto to do the test twice!
      if (pass)
	w.moveto(saved_pos);
      else
	w.moveto(saved_offset);
    }
}

/*------------------.
| test_window_print |
`------------------*/

void
test_window_print(unsigned int wlength, unsigned int nb_tests)
{
  using namespace utility;
  typedef Window<std::string::const_iterator, char>	window_t;

  for (unsigned int i = 0; i < nb_tests; ++i)
    {
      std::string		s;
      for(unsigned int i = 0; i < wlength; ++i)
	s += utility::random::generate<char>('0', 'z');

      window_t			w(s.begin(), s.end(), '\n', wlength);
      std::ostringstream	ostr;

      assert(w.window() == s);
      ostr << w;
      assert(ostr.str() == s);
    }
}

/*-----.
| main |
`-----*/

int main()
{
  test_window<std::string, char, 128, 4>('\n');
  test_window<std::string, char, 1000, 700>('X');
  test_window<std::basic_string<int>, int, 512, 16>(-1);
  test_window<std::vector<unsigned int>, unsigned int, 2048, 64>(42);
  test_window<std::vector<char*>, char*, 1500, 20>(0);

  for (unsigned int wlength = 1; wlength < 1000; wlength += 10)
    test_window_print(wlength, 10);
}
