%module vaucanswig_core
%include vaucanswig_exception.i

%include std_list.i

%{
#include <vaucanson/misc/unique.hcc>
#include "vcontext.hh"
%}
%include vcontext.hh
%{
#include "vauto.hh"
%}
%include vauto.hh

%template (hlist) std::list<int>;
%template (clist) std::list<char>;
