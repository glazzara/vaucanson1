/*********************
 * "core/streams.cc" *
 *********************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/streams.hh>

namespace vcsn
{
  namespace vauc
  {
    StreamSlot::~StreamSlot()
    {}

    Stream::Stream(StreamSlot* s)
      : s_(s)
    {}

    Stream::Stream(const Stream& other)
      : s_(other.s_)
    {}

    Stream::Stream(utility::ref<StreamSlot> other)
      : s_(other)
    {}

    std::istream& StreamSlot::as_istream()
    {
      return *static_cast<std::istream*>((void*)0);
    }

    std::ostream& StreamSlot::as_ostream()
    {
      return *static_cast<std::ostream*>((void*)0);
    }

    std::iostream& StreamSlot::as_iostream()
    {
      return *static_cast<std::iostream*>((void*)0);
    }

    StreamSlot::access_type Stream::kind() const
    {
      return s_->kind();
    }

    void* StreamSlot::private_data()
    {
      return 0;
    }
    
    std::ostream& Stream::as_ostream()
    {
      return s_->as_ostream();
    }

    std::istream& Stream::as_istream()
    {
      return s_->as_istream();
    }

    std::iostream& Stream::as_iostream()
    {
      return s_->as_iostream();
    }

    void* Stream::private_data()
    {
      return s_->private_data();
    }

    const std::string& Stream::describe() const
    {
      return s_->describe();
    }

  }
}

