%module vaucanswig_core
%include vaucanswig_exception.i

%include std_list.i

%{
#include "vcontext.hh"
%}
%include vcontext.hh
%{
#include "vauto.hh"
%}
%include vauto.hh

%include std_string.i

%template (hlist) std::list<int>;
%template (clist) std::list<char>;
%template (slist) std::list<std::string>;
