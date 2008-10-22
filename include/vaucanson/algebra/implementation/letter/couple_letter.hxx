// couple_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson
// Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX

# include <stdexcept>
# include <sstream>

# include <vaucanson/algebra/implementation/letter/couple_letter.hh>

namespace vcsn {

  namespace algebra {

    template <typename U, typename V>
    struct letter_traits< std::pair<U, V> >
    {
      // we only consider letters of the form (u, v)
      typedef misc::true_t is_char_letter;

      enum
      {
	/*
	 * Theoretically   cardinal	should	 be   the   product   of
	 * letter_traits<U>::cardinal and letter_traits<V>::cardinal.
	 * But to  avoid overflows and for
	 * practical reasons, it is better to consider it infinite.
	 *
	 * FIXME: Maybe doing this is not a good idea?
	 */
	cardinal = INT_MAX
      };

      // A pair letter has two projections available: U and V.
      typedef U first_projection_t;
      typedef V second_projection_t;

      static
      std::pair<U, V>
      literal_to_letter(const std::string& str)
      {
	std::stringstream sstr(str);
	std::pair<U, V> ret;
	sstr >> ret;
	return ret;
      }

      static
      std::string
      letter_to_literal(const std::pair<U, V>& c)
      {
	std::stringstream sstr;
	sstr << c;
	return sstr.str();
      }

      // A pair is a "tuple" with dimension 2.
      static std::string kind() { return "tuple"; }
      static int dim() { return 2; }

    };

    // Specialization for pairs.
    // FIXME: we should share the taf-kit parser with letters op_parse.
    // FIXME: this parser is very weak.
    template <typename S, typename U, typename V, typename CharContainer>
    bool op_parse(const algebra::FreeMonoidBase<S>& set,
		  std::basic_string< std::pair<U, V> >& v,
		  const std::string& s,
		  typename std::string::const_iterator& i,
		  const CharContainer&)
    {
      while (i != s.end())
      {
	if (*i != '(')
	  break ;

	std::string sub(i, s.end());
	std::stringstream is(sub);

	std::pair<U,V> p;
	is >> p;
	int pos = is.tellg();

	// We didn't parse anything.
	if (pos == 0)
	  break;

	// Unknown letter.
	if (!set.alphabet().contains(p))
	{
	  std::stringstream sstr;
	  sstr << p;
	  throw std::logic_error(std::string("Letter not in the alphabet: ") + sstr.str());
	}

	// Advance the iterator.
	for (int k = 0; k < pos; ++k)
	  ++i;

	// Concatenate the letter.
	v += p;
      }

      return (i == s.end());
    }

  } // ! algebra

} // ! vcsn

namespace std
{

  template <typename U, typename V>
  std::ostream& operator<< (std::ostream& o, std::pair<U, V> p)
  {
    return o << "(" << p.first << "," << p.second << ")";
  }

  template <typename U, typename V, class Traits, class Allocator>
  std::ostream& operator<< (std::ostream& o,
			    std::basic_string<std::pair<U, V>, Traits, Allocator> s)
  {
    typename
      std::basic_string<std::pair<U, V>, Traits, Allocator>::const_iterator i;
    for (i = s.begin (); i != s.end (); ++i)
      o << "(" << i->first << "," << i->second << ")";
    return o;
  }

  template <typename U, typename V>
  std::istream& operator>> (std::istream& i, std::pair<U, V>& p)
  {
    char c = i.get ();
    if (c != '(')
      i.unget ();
    i >> p.first;
    c = i.get ();
    if (c != ',')
      i.unget ();
    i >> p.second;
    c = i.get ();
    if (c != ')')
      i.unget ();
    return i;
  }

} // ! std

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX
