#ifndef VCSN_XML_IOS_HH
# define VCSN_XML_IOS_HH

# include <xercesc/util/BinInputStream.hpp>
# include <xercesc/sax/InputSource.hpp>
# include <iostream>

namespace vcsn
{
    namespace xml
    {
      class BinCxxInputStream : public xercesc::BinInputStream
      {
      private:
	std::istream* _in;
	unsigned int _pos;

      public:
	BinCxxInputStream(std::istream* in) : _in(in), _pos(0) { }
	virtual unsigned int curPos() const;
	virtual unsigned readBytes (XMLByte *const toFill,
				    const unsigned int maxToRead);
      };

      class CxxInputSource : public xercesc::InputSource
      {
      private:
	std::istream* _in;

      public:
	CxxInputSource(std::istream* in) : InputSource(), _in(in) {}
	virtual BinCxxInputStream* makeStream() const;
      };
    }
}

# include <vaucanson/xml/ios.hxx>

#endif // VCSN_XML_IOS_HH
