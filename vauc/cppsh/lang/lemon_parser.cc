/*-----------------------------------------------------------------.
| lang/lemon_parser.cc : cppsh language syntax / lemon parser base |
`-----------------------------------------------------------------*/
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
#include "lemon_parser.hh"
#include <cstdlib>
#include <stdexcept>

namespace cppsh
{
  namespace lang
  {
    namespace internals
    {
      LemonParser::LemonParser(LemonParser::alloc_func_t alloc,
			       LemonParser::free_func_t free,
			       LemonParser::trace_func_t trace,
			       LemonParser::parse_func_t parse)
	: alloc_(alloc),
	  free_(free),
	  trace_(trace),
	  parse_(parse)
      { }

      LemonParser::~LemonParser()
      {
	if (state_)
	  close();
      }

      void LemonParser::open()
      {
	if (state_)
	  close();
	if ((state_ = alloc_(std::malloc)) == 0)
	  throw std::runtime_error("failed to alloc parser");
      }
	
      void LemonParser::close()
      {
	if (state_)
	  free_(state_, std::free);
	state_ = 0;
      }

      void LemonParser::feed(int token,
			     cppsh::Cell* t,
			     cppsh::lang::parse::ParseArg& a)
      {
	if (!state_)
	  {
	    delete t;
	    throw std::runtime_error("parser uninitialized");
	  }
	if (trace_stream_)
	  trace_(trace_stream_, trace_prefix_.c_str());
	parse_(state_, token, t, &a);
	trace_(0, 0);
      }
      
      void LemonParser::finish(cppsh::lang::parse::ParseArg& a)
      {
	if (!state_)
	  throw std::runtime_error("parser uninitialized");
	if (trace_stream_)
	  trace_(trace_stream_, trace_prefix_.c_str());
	parse_(state_, 0, 0, &a);
	trace_(0, 0);
	// FIXME: check lemon doc & sources and see
	// if the state is still valid after the end of
	// the parse (question: the call to close()
	// is there to ensure there is no state left,
	// but is it really necessary ?)
	close();
      }
      
      void LemonParser::enable_trace(std::ostream& o,
				     const char *prefix)
      {
	trace_stream_ = &o;
	trace_prefix_ = prefix ? prefix : "";
      }

    }
  }
}
