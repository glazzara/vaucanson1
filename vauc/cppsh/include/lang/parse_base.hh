/*------------------------------------------------------.
| include/lang/parse_base.hh : cppsh lang support / parser base |
`------------------------------------------------------*/
//     Copyright (C) 2002  LRDE.

//     libcppshls is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.

//     libcppshls is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#ifndef CPPSH_PARSE_BASE_HH
#define CPPSH_PARSE_BASE_HH

#include "kern/object.hh"
#include <string>

namespace cppsh
{
  namespace lang
  {
    namespace parse
    {
      class ParseArg
      {
      public:
	// accessors for use by the parser
	virtual void report_success(Object) = 0;
	virtual void report_empty_parse() = 0;
	virtual void report_syntax_error(const std::string& reason) = 0;
	
	// accessors to report parsing status
	virtual Object exp() const = 0;
	virtual size_t errors() const = 0;
	
      protected:
	virtual ~ParseArg();
      };
      
      class ParserBase
      {
      public:
	virtual void open() = 0;
	virtual void feed(int token, Cell*, ParseArg&) = 0;
	virtual void finish(ParseArg&) = 0;
	virtual void close() = 0;
	virtual void enable_trace(std::ostream& o, 
				  const char *prefix = "parse:") = 0;
	void disable_trace()
	{ enable_trace(*((std::ostream*)0), 0); }
	virtual ~ParserBase();
      };
      
      class ScannerArg
      {
      public:
	// accessors for use by the lexer
	virtual void report_lexical_error(const std::string& reason) = 0;
	virtual void report_success() = 0;

	// accessors to report scanning status
	virtual size_t errors() const = 0;

      protected:
	virtual ~ScannerArg();
      };

      class ScannerBase
      {
      public:
	virtual void reset(ScannerArg&, std::istream& i, std::ostream* o = 0) = 0;
	virtual int yylex() = 0;
	virtual int get_current_token() const = 0;
	virtual Cell* get_current_token_value() const = 0;
	virtual void enable_trace(std::ostream& o,
				   const char *prefix = "scan:") = 0;
	void disable_trace()
	{ enable_trace(*((std::ostream*)0), 0); }
	virtual ~ScannerBase();
      };

    }

  }
}


#endif
