/******************************************************************
 * Implementation of readlinebuf, a streambuf which uses the GNU  *
 * readline library for line I/O.  (c) 2001 by Dimitris Vyzovitis *
 * [vyzo@media.mit.edu] (c) 2001,2002,2003 by Raphael Poss        *
 * [r.poss@online.fr]                                             *
 *                                                                *
 * See readlinebuf.hh for more information and licensing terms.   *
 ******************************************************************/

#include <readlinebuf.hh>

#include <cstring>
#include <cassert>

extern "C" {
extern char* readline(const char *);
extern void add_history(const char *);
extern int rl_set_signals(void);
extern int write_history(const char *);
extern int read_history(const char *);
typedef char *rl_compentry_func_t (const char *, int);
extern char** rl_completion_matches(const char *, rl_compentry_func_t*);
extern char ** (*rl_attempted_completion_function) (const char *, int, int);
  extern const char *rl_readline_name;
}

char** 
readlinebuf::rl_completion_matches(const char *text, 
				   readlinebuf::rl_compentry_func_t *f)
{
  return ::rl_completion_matches(text, f);
};
void readlinebuf::rl_attempted_completion_function(rl_completion_func_t *f)
{
  ::rl_attempted_completion_function = f;
};
readlinebuf::rl_completion_func_t* readlinebuf::rl_attempted_completion_function()
{
  return ::rl_attempted_completion_function;
}

const char * readlinebuf::rl_readline_name()
{
  return ::rl_readline_name;
}

void readlinebuf::rl_readline_name(const char *name)
{
  ::rl_readline_name = name;
}



void 
readlinebuf::set_prompt(const char *prompt)
{ prompt_ = prompt; }

int 
readlinebuf::showmanyc() const { return high_ - low_; }

int 
readlinebuf::uflow()
{
  int_type c = underflow();
  if ( c != eof ) ++low_;
  return c;
}

void 
readlinebuf::set_hist_file(const std::string& fname)
{
  history_file_ = fname;
  if (history_file_ != "")
    write_history(history_file_.c_str());
}

int
readlinebuf::write_history(const char *fname) const
{
  return ::write_history(fname);
}

int
readlinebuf::read_history(const char *fname) const
{
  return  ::read_history(fname);
}

readlinebuf::readlinebuf( const char* prompt, 
			  bool history, 
			  bool append_char,
			  const char *appended_string) 
  : prompt_( prompt ), history_( history ),
    line_( NULL ), low_( 0 ), high_( 0 ),
    append_semicolon_(append_char),
    appended_string_(appended_string),
    history_file_()
{
  rl_set_signals(); 
  setbuf( 0, 0 ); 
}


std::streamsize 
readlinebuf::xsgetn(char* buf, std::streamsize n )
{	
  int rd = n > (high_ - low_)? (high_ - low_) : n;
  memcpy( buf, line_ + low_, rd );
  low_ += rd;
  
  if ( rd < n ) {
    low_ = high_ = 0;
    free( line_ ); // free( NULL ) is a noop
    line_ = readline( prompt_ );
    if ( line_ ) {
      high_ = strlen( line_ );
      if ( history_ && high_ ) {
	add_history( line_ );
	if (history_file_ != "")
	  write_history(history_file_.c_str());
      }
      if (append_semicolon_)
	{
	  char *tmp = line_;
	  line_ = (char*)malloc((high_ = strlen( line_ ) + 1) + 1);
	  strcpy(line_, tmp);
	  strcat(line_, appended_string_);
	  free(tmp);
	}
      rd += xsgetn( buf + rd, n - rd );
    }
  }
  
  return rd; 
}

int 
readlinebuf::underflow() 
{
  if ( high_ == low_ ) {
    low_ = high_ = 0;
    free( line_ ); // free( NULL ) is a noop
    line_ = readline( prompt_ );
    if ( line_ ) {
      high_ = strlen( line_ );
      if ( history_ && high_ ) {
	add_history( line_ );
	if (history_file_ != "")
	  write_history(history_file_.c_str());
      }
      if (append_semicolon_)
	{
	  char *tmp = line_;
	  line_ = (char*)malloc((high_ = strlen( line_ ) + 1) + 1);
	  strcpy(line_, tmp);
	  strcat(line_, appended_string_);
	  free(tmp);
	}
    }
  }
  
  if ( low_ < high_ ) return line_[low_];
  else if ( line_ ) return underflow(); // empty line - retry
  else return eof;
}

int
readlinebuf::pbackfail( int c ) 
{
  if ( low_ > 0 )	--low_;
  else if ( c != eof ) {
    if ( high_ > 0 ) {
      char* nl = (char*)realloc( line_, high_ + 1 );
      if ( nl ) {
	line_ = (char*)memmove( nl + 1, line_, high_ );
	high_ += 1;
	line_[0] = char( c );
      } else return eof;
    } else {
      assert( !line_ );
      line_ = (char*)malloc( sizeof( char ) );
      *line_ = char( c );
      high_ = 1;
    }
  } else return eof;
  
  return not_eof;
}
