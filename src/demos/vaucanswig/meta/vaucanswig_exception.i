// -*- C++ -*-

%include exception.i

%{
#include <stdexcept>
%}

%define START_PROTECT()
%exception {
  try {
    $action
      } 
  catch(std::exception &e)
    {
      // FIXME: do we need to copy the string here ?
      SWIG_exception(SWIG_RuntimeError, const_cast<char*>(e.what()));
    }
  catch(...)
    {
      SWIG_exception(SWIG_UnknownError, __FUNCTION__);
    }
}
%enddef

%define END_PROTECT()
%exception;
%enddef

START_PROTECT()
