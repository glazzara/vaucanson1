// parse_base.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_VAUC_CPPSH_INCLUDE_LANG_PARSE_BASE_HH
# define VCSN_VAUC_CPPSH_INCLUDE_LANG_PARSE_BASE_HH

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
	virtual void restructure(ScannerArg&, std::istream& i, std::ostream* o = 0) = 0;
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


#endif // ! VCSN_VAUC_CPPSH_INCLUDE_LANG_PARSE_BASE_HH
