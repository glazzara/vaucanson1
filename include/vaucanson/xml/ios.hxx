#ifndef VCSN_XML_IOS_HXX
# define VCSN_XML_IOS_HXX

# include <vaucanson/xml/ios.hh>

namespace vcsn
{
    namespace xml
    {
      unsigned
      BinCxxInputStream::readBytes (XMLByte *const toFill,
				    const unsigned int maxToRead)
      {
	// istream::readsome does not seem to work on SunOS
	unsigned s = _in->rdbuf()->sgetn((char *)toFill, maxToRead);
	_pos += s;
	return s;
      }

      unsigned int
      BinCxxInputStream::curPos() const
      {
	return _pos;
      }

      BinCxxInputStream*
      CxxInputSource::makeStream() const
      {
	return new BinCxxInputStream(_in);
      }
  }
}

#endif // VCSN_XML_IOS_HXX
