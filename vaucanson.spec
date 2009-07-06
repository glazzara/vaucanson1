Name: vaucanson
Summary: C++ generic library for weighted finite state machine
Vendor: LRDE
Version: 0.7.2
Release: 1
License: GPL
URL: http://vaucanson.lrde.epita.fr/
Group: Development/Tools
Source: %{name}-%{version}.tar.gz
BuildRoot: /var/tmp/%{name}-%{version}-%{release}-buildroot
BuildArch: noarch
# Requires:

%description
The goal of this library is to enable the development of C++ programs
in an abstract and general way with, at the same time, a large
specialization power. Indeed, on the one hand, we can write algorithms
working on every automaton with weights over any semirings and with
words from any free monoids. And on the other hand, a particular
algorithm can be specialized for a particular data structure
implementing only a pseudo behaviour.

Yet, Vaucanson is an ongoing development project. Therefore
algorithms, data structures and the general architecture are not
totally stable and well tested.

%prep
%setup -n %{name}-%{version}*

%build
./configure --prefix=/usr
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
/usr/include/*
/usr/share/aclocal/*
/usr/share/vaucanson/*
%doc /usr/share/doc/vaucanson/*
%doc AUTHORS COPYING NOTICE CONTRIBUTORS README ChangeLog

%changelog
* Tue Jul 5 2005 Olivier Gournet <victor@lrde.epita.fr>
- Change to noarch
- Add docs and examples

* Mon Jul 4 2005 Olivier Gournet <victor@lrde.epita.fr>
- RPM integration.
