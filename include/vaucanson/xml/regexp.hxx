// regexp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_XML_REGEXP_HXX
# define VCSN_XML_REGEXP_HXX

# include <set>

# include <xercesc/util/XMLString.hpp>

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>

# include <vaucanson/xml/tools.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * RegexpHandler
     */
    template <typename T>
    RegexpHandler<T>::RegexpHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : Handler(parser, root),
	end_(eq_.typedRegExp),
	param_(param),
	lefth_(0)
    {
    }

    template <typename T>
    RegexpHandler<T>::RegexpHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param,
			       XMLCh* end)
      : Handler(parser, root),
	end_(end),
	param_(param),
	lefth_(0)
    {
    }

    template <typename T>
    RegexpHandler<T>::~RegexpHandler()
    {
      if (lefth_)
	delete lefth_;
    }

    template <typename T>
    void
    RegexpHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      if (!(lefth_ = create(localname)))
	error::token(localname);
      else
	parser_->setContentHandler(lefth_);
    }

    template <typename T>
    void
    RegexpHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
      {
	param_ = lefth_->series();
	parser_->setContentHandler(&root_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    T&
    RegexpHandler<T>::series()
    {
      return param_;
    }

    /*
     * StarHandler
     */
    template <typename T>
    StarHandler<T>::StarHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param)
    {
      end_ = eq_.star;
    }

    template <typename T>
    void
    StarHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      in_++;
      if (in_ == 1 && (lefth_ = create(localname)))
	parser_->setContentHandler(lefth_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    StarHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
      {
	param_ = lefth_->series().star();
	parser_->setContentHandler(&root_);
      }
      else
	error::token(localname);
    }

    /*
     * AtomHandler
     */
    template <typename T>
    AtomHandler<T>::AtomHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param,
			       XMLCh* end)
      : RegexpHandler<T>(parser, root, param, end)
    {
    }

    template <typename T>
    void
    AtomHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      error::token(localname);
    }

    template <typename T>
    void
    AtomHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }

    /*
     * WeightHandler
     */
    template <typename T>
    WeightHandler<T>::WeightHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param)
    {
      end_ = eq_.weight;
    }

    template <typename T>
    void
    WeightHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      error::token(localname);
    }

    template <typename T>
    void
    WeightHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }

    /*
     * ExtMulHandler
     */
    template <typename T>
    ExtMulHandler<T>::ExtMulHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param,
			       bool left)
      : RegexpHandler<T>(parser, root, param),
	left_(left),
	righth_(0)
    {
      if (left)
	end_ = eq_.leftExtMul;
      else
	end_ = eq_.rightExtMul;
    }

    template <typename T>
    ExtMulHandler<T>::~ExtMulHandler ()
    {
      delete righth_;
    }

    template <typename T>
    void
    ExtMulHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.weight, localname) &&
	  (lefth_ = create_weight(attrs)))
	parser_->setContentHandler(lefth_);
      else if ((righth_ = create(localname)))
	parser_->setContentHandler(righth_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    ExtMulHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
      {
	if (left_)
	  param_ = lefth_->series() * righth_->series();
	else
	  param_ = righth_->series() * lefth_->series();
	parser_->setContentHandler(&root_);
      }
      else
	error::token(localname);
    }

    /*
     * ProductHandler
     */
    // FIXME: should factorize
    template <typename T>
    ProductHandler<T>::ProductHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param),
	in_(1),
	righth_(0)
    {
      end_ = eq_.product;
    }

    template <typename T>
    ProductHandler<T>::~ProductHandler()
    {
      delete righth_;
    }

    template <typename T>
    void
    ProductHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      if (in_ == 1 && (lefth_ = create(localname)))
	parser_->setContentHandler(lefth_);
      else if (in_ == 2 && (righth_ = create(localname)))
	parser_->setContentHandler(righth_);
      else
	error::token(localname);
      in_++;
    }

    template <typename T>
    void
    ProductHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
      {
	param_ = lefth_->series() * righth_->series();
	parser_->setContentHandler(&root_);
      }
      else if (!XMLString::equals(eq_.monGen, localname))
	error::token(localname);
    }
    /*
     * SumHandler
     */
    template <typename T>
    SumHandler<T>::SumHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param),
	in_(1),
	righth_(0)
    {
      end_ = eq_.sum;
    }

    template <typename T>
    SumHandler<T>::~SumHandler ()
    {
      delete righth_;
    }

    template <typename T>
    void
    SumHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;

      if (in_ == 1 && (lefth_ = create(localname)))
	parser_->setContentHandler(lefth_);
      else if (in_ == 2 && (righth_ = create(localname)))
	parser_->setContentHandler(righth_);
      else
	error::token(localname);

      in_++;
    }

    template <typename T>
    void
    SumHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;

      if (XMLString::equals(end_, localname))
      {
	param_ = lefth_->series() + righth_->series();
	parser_->setContentHandler(&root_);
      }
      else if (!XMLString::equals(eq_.monGen, localname))
	error::token(localname);
    }

    /*
     * MonElmtHandler
     */
    template <typename T>
    MonElmtHandler<T>::MonElmtHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param),
        mongenh_(0)
    {
      end_ = eq_.monElmt;
    }

    template <typename T>
    void
    MonElmtHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      // FIXME: This code is very similar to the one used by
      // FreeMonoidHandler::start. Ultimately we should provide a way to
      // parse "sequences of" (to promote reusability, and ease transcription
      // from the XSD to parser code).
      using namespace xercesc;

      if (XMLString::equals(eq_.monGen, localname))
      {
	typedef typename T::set_t::monoid_t monoid_t;
	typedef T actee_t;

	// When we have a monGen, we will concatenate param_ with it.
	monGenAction<actee_t> action(param_);

	// Delete the old handler.
	if (mongenh_)
	  delete mongenh_;

	// Choose statically the kind of generator.
	if (algebra::letter_traits<typename monoid_t::alphabet_t::letter_t>::kind() == "simple")
	{
	  const XMLCh* value = tools::get_attribute(attrs, "value");
	  mongenh_ = new monGenHandler<monoid_t, actee_t>(parser_, *this, action, value);
	}
	else
	  mongenh_ = new monGenTupleHandler<monoid_t, actee_t>(parser_, *this, action);

	// Setup the new handler.
	parser_->setContentHandler(mongenh_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    MonElmtHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;

      if (XMLString::equals(end_, localname))
      {
	// We are done with the "parent", so delete remaining data.
	if (mongenh_)
	  delete mongenh_;

	// Go up one level.
	parser_->setContentHandler(&root_);
      }
      else if (!XMLString::equals(eq_.monGen, localname))
	error::token(localname);
    }

  } // !xml
} // !vcsn

#endif // !VCSN_XML_REGEXP_HXX
