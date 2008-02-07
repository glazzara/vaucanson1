// builders.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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

#ifndef BUILDERS_HXX
# define BUILDERS_HXX

/**
 * @file builders.hxx
 *
 * dispatch functions for handlers classes (automaton loading)
 *
 * @see vcsn::xml
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */


# include <vaucanson/xml/handlers.hh>
# include <vaucanson/xml/xmleq.hh>

namespace vcsn
{
  namespace xml
  {
    namespace builders
    {
      // Processing monoid

      template <typename T>
      inline
      typename T::monoid_t*
      create_monoid (T&,
		     const xercesc::Attributes&)
      {
	typename T::monoid_t::alphabet_t	at;
	typedef typename T::monoid_t	monoid_t;

	monoid_t*		monoid = new monoid_t(at);
	return monoid;
      }

      TParmFMP
      inline
      typename FMPtype::monoid_t*
      create_monoid (FMPtype&,
		     const xercesc::Attributes&)
      {
	typename FMPtype::monoid_t::first_monoid_t::alphabet_t	at1;
	typename FMPtype::monoid_t::second_monoid_t::alphabet_t	at2;
	typename FMPtype::monoid_t::first_monoid_t	md1(at1);
	typename FMPtype::monoid_t::second_monoid_t	md2(at2);
	typedef typename FMPtype::monoid_t		monoid_t;

	monoid_t* monoid = new monoid_t(md1, md2);
	return monoid;
      }

      template <typename T>
      MonoidHandler*
      monoidh_factory(T& monoid,
		      const xercesc::Attributes& attrs,
		      xercesc::DefaultHandler& root,
		      xercesc::SAX2XMLReader* parser,
		      XMLEq& eq)
      {
	check_consistency (attrs, "monoid", "type",
			   tools::get_monoid_type(monoid));
	return new vcsn::xml::FreeMonoidHandler<T>(root, monoid, parser, eq);
      }

      template <typename T1, typename T2>
      MonoidHandler*
      monoidh_factory(vcsn::algebra::FreeMonoidProduct<T1, T2>& monoid,
		      const xercesc::Attributes& attrs,
		      xercesc::DefaultHandler& root,
		      xercesc::SAX2XMLReader* parser,
		      XMLEq& eq)
      {
	check_consistency (attrs, "monoid", "type",
			   tools::get_monoid_type(monoid));
	typedef typename vcsn::algebra::FreeMonoidProduct<T1, T2> monoid_t;
	return new ProdMonoidHandler<monoid_t>(root, monoid, parser, eq);
      }

      template <typename T>
      inline
      void
      insert_letter (T& monoid,
		     std::string letter)
      {
	tools::insert_letter(monoid.alphabet(), letter);
      }

      // Processing semiring

      template <typename T>
      inline
      typename T::semiring_t*
      create_semiring (T&,
		       const xercesc::Attributes&)
      {
	typedef typename T::semiring_t semiring_t;
	semiring_t*	semiring = new semiring_t();
	return semiring;
      }

      TParm
      inline
      typename TRANStype::semiring_t*
      create_semiring (TRANStype&,
		       const xercesc::Attributes&)
      {
	typename TRANStype::semiring_t::monoid_t::alphabet_t	at;
	typename TRANStype::semiring_t::monoid_t	md(at);
	typename TRANStype::semiring_t::semiring_t	ssg;
	typedef typename TRANStype::semiring_t	semiring_t;

	semiring_t*	semiring = new semiring_t(ssg, md);
	return semiring;
      }

      template <typename V, typename T>
      SemiringHandler*
      semiringh_factory(V&,
			const xercesc::Attributes& attrs,
			T& semiring,
			xercesc::DefaultHandler& root,
			xercesc::SAX2XMLReader* parser,
			XMLEq& eq)
      {
	typedef typename V::series_set_elt_t::semiring_elt_t::value_t value_t;
	check_consistency (attrs, "semiring", "set",
			   tools::get_semiring_set(semiring, value_t()));
	return new NumSemiringHandler<T>(root, semiring, parser, eq);
      }

#define SSEMIRINGtype \
      vcsn::algebra::Series<U, V>

      template <typename U, typename V, typename T>
      SemiringHandler*
      semiringh_factory(SSEMIRINGtype&,
			const xercesc::Attributes&,
			T& semiring,
			xercesc::DefaultHandler& root,
			xercesc::SAX2XMLReader* parser,
			XMLEq& eq)
      {
	// FIXME Check_consistency of a semiring_t::semiring_t.
	// Need to find how to get the set of a semiring_t

	// typedef typename SSEMIRINGtype::semiring_t value_t;
	//check_consistency (attrs, "semiring", "set",
	//		   tools::get_semiring_set(semiring, value_t()));
	return new NumSemiringHandler<T>(root, semiring, parser, eq);
      }

#undef SSEMIRINGtype

      TParm
      SemiringHandler*
      semiringh_factory(TRANStype&,
			const xercesc::Attributes& attrs,
			typename TRANStype::semiring_t& semiring,
			xercesc::DefaultHandler& root,
			xercesc::SAX2XMLReader* parser,
			XMLEq& eq)
      {
	typedef typename TRANStype::series_set_elt_t::semiring_elt_t::value_t value_t;
	check_consistency (attrs, "semiring", "set",
			   tools::get_semiring_set(semiring, value_t()));
	typedef typename TRANStype::semiring_t	semiring_t;
	return new SeriesSemiringHandler<semiring_t>(root, semiring, parser, eq);
      }

      // Processing label attribute

      template<typename T>
      inline
      void
      get_weight(T& res,
		 std::map<std::string, std::string>& attrs)
      {
	typename std::map<std::string, std::string>::iterator i;
	if ((i = attrs.find("weight")) != attrs.end())
	{
	  typename T::semiring_elt_t weight(res.structure().semiring());
	  const std::string& str = i->second;
	  std::string::const_iterator it = str.begin();
	  if (parse_weight(weight, str, it))
	    res = res * weight;
	  else
	    FAIL(std::string ("Weight in wrong format"));
	}
      }

      template <typename T>
      typename T::series_set_elt_t
      get_series (T& aut,
		  std::map<std::string, std::string>& attrs,
		  const char* token)
      {
	typedef typename
	  rat::exp<typename T::monoid_elt_value_t,
	  typename T::semiring_elt_value_t> krat_exp_impl_t;
	typedef Element<typename T::series_set_t, krat_exp_impl_t> krat_exp_t;
	krat_exp_t res (aut.structure().series());
	typename std::map<std::string, std::string>::iterator i;
	if ((i = attrs.find(token)) == attrs.end())
	  return
	    vcsn::algebra::identity_as<typename T::series_set_elt_t::value_t>
	      ::of(aut.structure().series());
	else
	{
	  std::pair<bool, std::string> err = parse(i->second, res);
	  if (err.first)
	    FAIL(std::string ("Error while parsing: ") + err.second + "\n");
	}
	get_weight(res, attrs);
	return res;
      }

      TParmFMP
      typename FMPtype::series_set_elt_t
      get_series (FMPtype& a,
		  std::map<std::string, std::string>& attrs,
		  const char*)
      {
	typename FMPtype::series_set_elt_t res(a.structure().series());

	parse_label(a,
		    a.structure().series().monoid().first_monoid().alphabet(),
		    a.structure().series().monoid().second_monoid().alphabet(),
		    attrs,
		    res);
	get_weight(res, attrs);
	return res;
      }

      TParm
      typename TRANStype::series_set_elt_t
      get_series (TRANStype& a,
		  std::map<std::string, std::string>& attrs,
		  const char*)
      {
	typename TRANStype::series_set_elt_t res(a.structure().series());

	parse_label(a,
		    a.structure().series().monoid().alphabet(),
		    a.structure().series().semiring().monoid().alphabet(),
		    attrs,
		    res);
	return res;
      }

      template <class Auto, class A1, class A2, class S>
      void
      parse_label (Auto& a,
		   const A1& al1,
		   const A2& al2,
		   std::map<std::string, std::string>& attrs,
		   S& res)
      {
	typedef typename std::map<std::string, std::string>::iterator	it_t;
	using namespace vcsn::r_automaton;
	automaton_t bin = make_automaton(al1);
	automaton_t bout = make_automaton(al2);
	rat_exp_t i_exp(bin.structure().series());
	rat_exp_t o_exp(bout.structure().series());
	std::string in, out;

	std::pair<bool, std::string> i_res;
	std::pair<bool, std::string> o_res;

	it_t it;
	if ((it = attrs.find("label")) != attrs.end())
	{
	  std::string label = it->second;
	  std::size_t pos = label.find("|");
	  if (pos != std::string::npos)
	  {
	    in = label.substr(0, pos);
	    out = label.substr(pos + 1);
	    i_res = parse(in, i_exp);
	    o_res = parse(out, o_exp);
	  }
	  else
	  {
	    i_res = parse(label, i_exp);
	    if (label == "0")
	      return;
	  }
	  if ((it = attrs.find("weight")) != attrs.end())
	      o_res = parse(it->second, o_exp);
	}
	else // No expression tag, no label attribute.
	{
	  if ((it = attrs.find("in")) != attrs.end())
	    i_res = parse(it->second, i_exp);
	  if ((it = attrs.find("out")) != attrs.end())
	    o_res = parse(it->second, o_exp);
	}
	tools::assoc_exp(a, i_exp, o_exp, res, i_res.first, o_res.first);
      }


      // Ensuring correct attributes

      inline
      void
      check_consistency (const xercesc::Attributes& attrs,
			 const std::string& kind,
			 const char* key,
			 const std::string& expected)
      {

	// If SeriesSemiring is expected, we can't know what we
	// should except.
	if (expected == "ratSeries")
	  return;

	std::string observed = xml2str(get_attribute(attrs, key));

	if (expected != observed)
	  FAIL(std::string ("invalid ") + kind + ": " + observed
	       + ", expected: " + expected);
      }

      // Getters

      inline
      bool
      has_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* const uri)
      {
	return (get_attribute(attrs, key, uri) != 0);
      }

      inline
      const XMLCh*
      get_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* const uri)
      {
	XMLCh* xkey = transcode(key);
	const XMLCh* tmp = attrs.getValue(uri, xkey);
	xercesc::XMLString::release(&xkey);
	return tmp;
      }

      // Labels
      template <typename T>
      RegExpHandler<T>*
      labelh_factory(xercesc::DefaultHandler& root,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq,
		     const XMLCh* const localname,
		     const xercesc::Attributes& attrs)
      {
	if (xercesc::XMLString::equals(eq.label, localname))
	  return new LabelHandler<T>(root, aut, parser, eq);

	if (xercesc::XMLString::equals(eq.sum, localname))
	  return new SumHandler<T>(root, aut, parser, eq);
	if (xercesc::XMLString::equals(eq.product, localname))
	  return new ProdHandler<T>(root, aut, parser, eq);
	if (xercesc::XMLString::equals(eq.star, localname))
	  return new StarHandler<T>(root, aut, parser, eq);


	if (xercesc::XMLString::equals(eq.word, localname))
	{
	  std::map<std::string, std::string > m;
	  for (unsigned int i = 0; i < attrs.getLength(); i++)
	    m[xml2str(attrs.getLocalName(i))] =  xml2str(attrs.getValue(i));
	  return new WordHandler<T>(root, aut, parser, eq, get_series(aut, m, "value"));
	}

	typename T::series_set_elt_t val(aut.structure().series());
	if (xercesc::XMLString::equals(eq.identity, localname))
	  val = vcsn::algebra::identity_as<typename T::series_set_elt_t::value_t>::of(val.structure());
	if (xercesc::XMLString::equals(eq.zero, localname))
	  val = vcsn::algebra::zero_as<typename T::series_set_elt_t::value_t>::of(val.structure());
	return new WordHandler<T>(root, aut, parser, eq, val);
      }

      template <typename T>
      typename T::series_set_elt_t
      get_series_transition(T& aut,
			    std::map<std::string, std::string>& attrs,
			    LabelHandler<T>& labelh)
      {
	std::map<std::string, std::string>::const_iterator i =
	  attrs.find("label");
	// Uncommment for a future version.
	//if (labelh.used() == (i != attrs.end()))
	//  FAIL("No labels / or too many labels found.");
	return (i != attrs.end() || !labelh.used()) ?
	  builders::get_series(aut, attrs, "label") :
	  labelh.value();
      }
      TParm
      typename TRANStype::series_set_elt_t
      get_series_transition(TRANStype& aut,
			    std::map<std::string, std::string>& attrs,
			    LabelHandler<TRANStype>& labelh)
      {
	std::map<std::string, std::string>::const_iterator i =
	  attrs.find("in");
	std::map<std::string, std::string>::const_iterator o =
	  attrs.find("out");
	bool inout = ((i != attrs.end()) || (o != attrs.end()));
	// Uncommment for a future version.
	//if (labelh.used() == inout)
	//  FAIL("No labels / or too many labels found.");
	//if ((i != attrs.end() != (o != attrs.end())))
	//  FAIL("Missing in or out attribute.")
	return (inout || !labelh.used()) ?
	  builders::get_series(aut, attrs, "label") :
	  labelh.value();
      }
      TParmFMP
      typename FMPtype::series_set_elt_t
      get_series_transition(FMPtype& aut,
			    std::map<std::string, std::string>& attrs,
			    LabelHandler<FMPtype>& labelh)
      {
	std::map<std::string, std::string>::const_iterator i =
	  attrs.find("in");
	std::map<std::string, std::string>::const_iterator o =
	  attrs.find("out");
	bool inout = ((i != attrs.end()) || (o != attrs.end()));
	// Uncommment for a future version.
	//if (labelh.used() == inout)
	//  FAIL("No labels / or too many labels found.");
	//if ((i != attrs.end() != (o != attrs.end())))
	//  FAIL("Missing in or out attribute.")
	return (inout || !labelh.used()) ?
	  builders::get_series(aut, attrs, "label") :
	  labelh.value();
      }
    } // !builders
  } // !xml
} // !vcsn

#endif // !BUILDERS_HXX
