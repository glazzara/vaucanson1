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
      return this->param_;
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
      this->end_ = this->eq_.star;
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
      if (in_ == 1 && (this->lefth_ = this->create(localname)))
	this->parser_->setContentHandler(this->lefth_);
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
      if (XMLString::equals(this->end_, localname))
      {
	this->param_ = this->lefth_->series().star();
	this->parser_->setContentHandler(&this->root_);
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
      if (XMLString::equals(this->end_, localname))
	this->parser_->setContentHandler(&this->root_);
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
      this->end_ = this->eq_.weight;
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
      if (XMLString::equals(this->end_, localname))
	this->parser_->setContentHandler(&this->root_);
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
	this->end_ = this->eq_.leftExtMul;
      else
	this->end_ = this->eq_.rightExtMul;
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
      if (XMLString::equals(this->eq_.weight, localname) &&
	  (this->lefth_ = this->create_weight(attrs)))
	this->parser_->setContentHandler(this->lefth_);
      else if ((this->righth_ = this->create(localname)))
	this->parser_->setContentHandler(this->righth_);
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
      if (XMLString::equals(this->end_, localname))
      {
	if (left_)
	  this->param_ = this->lefth_->series() * this->righth_->series();
	else
	  this->param_ = this->righth_->series() * this->lefth_->series();
	this->parser_->setContentHandler(&this->root_);
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
      this->end_ = this->eq_.product;
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
      if (in_ == 1 && (this->lefth_ = this->create(localname)))
	this->parser_->setContentHandler(this->lefth_);
      else if (in_ == 2 && (this->righth_ = this->create(localname)))
	this->parser_->setContentHandler(this->righth_);
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
      if (XMLString::equals(this->end_, localname))
      {
	this->param_ = this->lefth_->series() * this->righth_->series();
	this->parser_->setContentHandler(&this->root_);
      }
      else if (!XMLString::equals(this->eq_.monGen, localname))
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
      this->end_ = this->eq_.sum;
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
      if (in_ == 1 && (this->lefth_ = this->create(localname)))
	this->parser_->setContentHandler(this->lefth_);
      else if (in_ == 2 && (this->righth_ = this->create(localname)))
	this->parser_->setContentHandler(this->righth_);
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
      if (XMLString::equals(this->end_, localname))
      {
	this->param_ = this->lefth_->series() + this->righth_->series();
	this->parser_->setContentHandler(&this->root_);
      }
      else if (!XMLString::equals(this->eq_.monGen, localname))
	error::token(localname);
    }

    /*
     * MonElmtHandler
     */
    template <typename T>
    MonElmtHandler<T>::MonElmtHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param)
    {
      this->end_ = this->eq_.monElmt;
    }

    template <typename T>
    void
    MonElmtHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(this->eq_.monGen, localname))
      {
	typename T::monoid_elt_t m(this->param_.structure().monoid());
	const std::string val(xmlstr(tools::get_attribute(attrs, "value")));
	std::set<char> escaped;
	std::string::const_iterator i = val.begin();
	if (!parse_word(m, val, i, escaped))
	  error::attrs(localname, "value", val);
	T tmp(this->param_.structure(), m);
	this->param_ = this->param_ * tmp;
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
      if (XMLString::equals(this->end_, localname))
	this->parser_->setContentHandler(&this->root_);
      else if (!XMLString::equals(this->eq_.monGen, localname))
	error::token(localname);
    }

  } // !xml
} // !vcsn

#endif // !VCSN_XML_REGEXP_HXX
