/*--------------------------------------------------------------.
| lang/lemon_parser.hh : cppsh lang support / lemon parser base |
`--------------------------------------------------------------*/
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
#ifndef _CPPSH_LEMON_PARSER_HH
#define _CPPSH_LEMON_PARSER_HH

#include "lang/parse_base.hh"
#include <iostream>

namespace cppsh
{
  namespace lang
  {
    namespace internals
    {

      class LemonParser : public cppsh::lang::parse::ParserBase
      {
      public:
	virtual void open();
	virtual void feed(int token, 
			  cppsh::Cell *,
			  cppsh::lang::parse::ParseArg&);
	virtual void finish(cppsh::lang::parse::ParseArg&);
	virtual void close();
	virtual void enable_trace(std::ostream& o,
				  const char *prefix);
	virtual ~LemonParser();


      protected:
	typedef void *(*alloc_func_t)(void *(*)(size_t));
	typedef void (*free_func_t)(void*, void (*)(void *));
	typedef void (*trace_func_t)(std::ostream*, const char*);
	typedef void (*parse_func_t)(void *, int, 
				     cppsh::Cell *,
				     cppsh::lang::parse::ParseArg *);

	LemonParser(alloc_func_t alloc,
		    free_func_t ffunc,
		    trace_func_t trace,
		    parse_func_t parse);

	alloc_func_t alloc_;
	free_func_t free_;
	trace_func_t trace_;
	parse_func_t parse_;

	void *state_;
	std::ostream* trace_stream_;
	std::string trace_prefix_;

      };

    }
  }
}


#endif
