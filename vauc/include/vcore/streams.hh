/*********************
 * <vcore/streams.hh> *
 *********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_STREAMS_HH
#define CORE_STREAMS_HH

#include <iostream>
#include <vaucanson/misc/ref.hh>

namespace vcsn
{
  namespace vauc
  {
    // streams are not clonable.
    struct StreamSlot
    {
      enum access_type { input = 1, output = 2, both = 3 };

      virtual ~StreamSlot();

      virtual access_type kind() const = 0;
      virtual std::istream& as_istream();
      virtual std::ostream& as_ostream();
      virtual std::iostream& as_iostream();

      virtual const std::string& describe() const = 0;

      //// FIXME ////
      // this is a miserable kludge, but a simple way to get back the
      // readlinebuf from read_cmd.
      virtual void* private_data();

    };

    class Stream
    {
    public:
      Stream(StreamSlot *s);
      Stream(utility::ref<StreamSlot> other);
      
      StreamSlot::access_type kind() const;
      std::istream& as_istream();
      std::ostream& as_ostream();
      std::iostream& as_iostream();
      void* private_data();
      
      const std::string& describe() const;

      Stream(const Stream& other);

    protected:
      utility::ref<StreamSlot> s_;
    };
  }
}
      
      

  

#endif
