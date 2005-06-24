// readlinebuf.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_READLINEBUF_HH
# define VCSN_VAUC_INCLUDE_READLINEBUF_HH

#include <iostream>
#include <cstdlib>
#include <cstdio>


#include <streambuf>
#include <string>

/// Here is some documentation about the class:
// 
// Terminology:
//   The [prompt] is the string which is printed each time an input line
//   is requested from the readline library.
//   The [history] is at any time the sequence of text strings that have
//   been entered at the readline prompt so far.
//
// Constructor:
//   The readlinebuf::readlinebuf() constructor takes 4 optional arguments:
//     - prompt (const char*, default = NULL)
//         the initial readline prompt. It can be changed later via the
//         set_prompt() method. a NULL pointers disables printing of a prompt.
//
//     - history (bool, default = true)
//         enables or disables the use of the readline history buffer, and
//         recording it into a file.
//         Initially, recording of the history is disabled. It can be enabled
//         later by a call to set_hist_file().
//
//     - append_char (bool, default = false)
//         by default, each input line is made available to the stream as is,
//         with the terminating newline stripped.
//         setting append_char to true forces appending some string of
//         character to each line of input before use by the stream.
//
//     - appended_string (const char*, default = "\n")
//         the string given here is the one appended to each input
//         text when append_char is true.
//
// Methods:
//     (those requested by inheritance from streambuf) - refer to
//     standard C++ documentation.
//
//     void set_prompt(const char *prompt)
//         changes the prompt printed before each line of input.
//
//     void set_hist_file(const std::string& fname)
//         enables or disables history recording, and changes the name
//         of the file used for the recording.
//         The empty string given as argument disables the recording.
//         Any non-empty string enables recording to the specified file name.
//
//     void write_history(const char*)
//         request recording the whole current history to a specified file.
//         This method is equivalent to a library call to the GNU readline 
//         function of the same name. Refer to readline documentation for
//         further details.
//     void read_history(const char*)
//         likewise. Refer to GNU readline documentation.

class readlinebuf : public std::streambuf 
{
public:

  static const int eof = EOF; // this is -1
  static const int not_eof = 0;

private:
  const char* prompt_;
  bool history_;
  char* line_;
  int low_;
  int high_;
  bool append_semicolon_;
  const char* appended_string_;
  std::string history_file_;

protected:
		
  virtual int showmanyc() const;
		
  virtual std::streamsize xsgetn( char* buf, std::streamsize n );

  virtual int underflow();
		
  virtual int uflow();
		
  virtual int pbackfail(int c = eof );


public:
  readlinebuf( const char* prompt = NULL, 
	       bool history = true, 
	       bool append_char = false,
	       const char *appended_string = "\n");


  // readline functions
  typedef char *(rl_compentry_func_t) (const char *, int);
  typedef char **(rl_completion_func_t) (const char *, int, int);

  static void rl_readline_name(const char *name);
  static const char *rl_readline_name();

  static char** rl_completion_matches(const char *text, 
				      rl_compentry_func_t *f);
  static void rl_attempted_completion_function(rl_completion_func_t *f);
  static rl_completion_func_t* rl_attempted_completion_function();

  void set_prompt(const char *prompt);
  void set_hist_file(const std::string& fname);
  int write_history(const char *) const;
  int read_history(const char *) const;

};

#endif // ! VCSN_VAUC_INCLUDE_READLINEBUF_HH
