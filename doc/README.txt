Vaucanson, a generic library for finite state machines.
Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The
Vaucanson Group.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

The complete GNU General Public Licence Notice can be found as the
'COPYING' file in the root directory.

The Vaucanson Group consists of people listed in the 'AUTHORS' file.

===========================
 Introduction to Vaucanson
===========================

:Date: 2006-05-31

Vaucanson_, a C++ generic library for weighted finite state machines.

.. _Vaucanson: http://vaucanson.lrde.epita.fr

.. contents::


Overview
========

Initiated  by Jacques  Sakarovitch  in 2000,  Vaucanson  is a  project
developed by the École Nationale Supérieure des Télécommunications [1]
and the EPITA Research and Development Laboratory (LRDE) [2].

.. [1] http://www.enst.fr

.. [2] http://www.lrde.epita.fr

The goal of this library is  to enable the development of C++ programs
in  an abstract  and  general way  with,  at the  same  time, a  large
specialization  power.   Indeed,  on   the  one  hand,  we  can  write
algorithms working on every  automaton with weights over any semirings
and  with words  from any  free  monoids.  And  on the  other hand,  a
particular  algorithm  can  be   specialized  for  a  particular  data
structure implementing only a pseudo behaviour.

Yet,   Vaucanson  is  an   ongoing  development   project.   Therefore
algorithms,  data  structures and  the  general  architecture are  not
totally stable and well tested.

Please send  any question or comments  to vaucanson@lrde.epita.fr, and
report bugs to either our issue tracker http://vaucanson.lrde.org/, or
to vaucanson-bugs@lrde.epita.fr.

Installation
============

To install Vaucanson on your system, type in the classical sequence at
the command prompt::

	./configure
	make
	make install (as root)

Note that an installation is  specific to the compiler used to install
it. Indeed, the call  to ``./configure`` enables some workarounds and,
consequently,  users must  compile  with the  same  compiler to  avoid
compatibility problems.

Between ``make`` and ``make install``, you may also want to run::

	make demos
	make sanity-check
	make check

``make demos`` will build example binaries in ``src/demos/``.  ``make
sanity-check`` will make sure that Vaucanson's header files can be
included and compiled.  ``make check`` will run the test suite to
check the whole library.  Running the test suite may require up to
1.5GB of free space and several hours.


Additional features
-------------------

There  is a  Python  interpreter in  the  package. It  is disabled  by
default because its compilation takes  several hours. If you have time
to spare, use::

	./configure --enable-vaucanswig

To specify a special path for the Xerces-C library::

	./configure --with-xerces=/absolute/path/to/xerces

To specify a special path for the Boost-C++ library::

	./configure --with-boost=/absolute/path/to/boost

For further configure options, type::

	./configure --help


Tweaking compilation options
----------------------------

Use  ``CXXFLAGS_DEBUG``  or  ``CXXFLAGS_OPTIMIZE``  to pass  debug  or
optimization flags, not ``CXXFLAGS``.  For example::

	./configure CXXFLAGS_DEBUG='-fstack-check -fbounds-check -ggdb'

This is because  Vaucanson tries to use some  particular default flags
with some specific  compilers such as GCC or  ICC.  Using ``CXXFLAGS``
conflicts   with   those   specific  flags;   ``CXXFLAGS_DEBUG``   and
``CXXFLAGS_OPTIMIZE`` override these default flags.


Layout of the tarball
---------------------

The Vaucanson project directory layout is as follows:

argp
   A freestanding version of the GNU C Library's argp, a powerful
   command line argument parser.  Used by TAF-Kit.

build-aux
   Auxialiary tools used by the GNU Build System during "make"
   stages.

data
   Files to be installed on your system.

debian
   Data to generated Debian packages.

doc
   The documentations.

   manual
      The Vaucanson User Guide.
   share
      LaTeX components used to generate the documentation.
   xml
      The XML Proposal for Automata I/O.

include
   The code of the Vaucanson C++ Library.

src
   Demonstration tools, tests.

taf-kit
   TAF-Kit sources and tests.

vaucanswig
   VaucanSWIG sources and tests.  Very experimental.

Requirements
============

Vaucanson was tested with the `GNU Compiler Collection (GCC)`_ version 4.1.x
and 4.2.x, and with ICC_ version 9 and 10.1.   The code is  fully compliant
with  the  ISO  C++  standard  (ISO-IEC  14882)  to  permit  a  higher
portability in the future.

.. _GNU Compiler Collection (GCC): http://gcc.gnu.org/
.. _ICC: http://www.intel.com/software/products/compilers/

High verbose  mode of the testing  suites uses the AT&T  dot format to
save automaton in  a human readable file.  Use  Graphviz_ to visualize
these .dot files.

.. _Graphviz: http://www.research.att.com/sw/tools/graphviz/

If  you want  to use  the XML  I/O system,  you will  need  the Apache
`Xerces-C++`_ library version 2.3 or above.

.. _Xerces-C++: http://xml.apache.org/xerces-c/

The C++ Application Binary Interface (ABI) of the Xerces-C++ library
must be the same as the C++ ABI of the compiler used to built
Vaucanson's XML I/O system.  In particular, users of Fink or
DarwinPorts on MacOS should pay attention to the compiler that was
used to build their version of the Xerces-C++ library, as it might
differ from the one used to build Vaucanson.

.. _Boost-C++: http://www.boost.org/

`Boost-C++`_ has been introduced since Vaucanson 1.1. It is a C++ library
which provides many useful objects, including hash tables. Currently,
Boost is used in algorithms only, but its use shall be extended to
automata structures and other portions of code. You must install this
library on your system.

.. _python-docutils: http://www.python.org

You may need python-docutils_ if you want to build the documentation.


Using Vaucanson
===============

Vaucanson comes with several demos.  Looking  at them is a good way to
see what Vaucanson can do and how  it works.  They can be found in the
``src/demos`` directory.

The TAF-Kit  (Typed Automata Functions) documentation can  be found as
the first chapter of the User's Manual (see ``doc/manual``).


See Also
========

There are other sources of interest in the distribution.

- Headline news about the project can be found in the file ``NEWS`` at
  the root of the source tree.

- Frequently asked questions are answered in the file ``FAQ``.

- Some information about input and output of automata can be found in
  the file ``README-IO``.

- Documentation  about the  XML  I/O  subsystem can  be  found in  the
  ``doc/xml`` subdirectory.

- The library  reference manual, generated by Doxygen_,  is located in
  ``doc/ref``. It comes distributed as an archive of HTML files called
  ``ref.tar.gz``.

- Information about  the test suite generation mechanism  can be found
  in the file ``src/tests/test-suites/README``.

.. _Doxygen: http://www.doxygen.org


Licence
=======

Vaucanson is now released under the GNU General Public Licence. See the
file ``COPYING`` (at the root of the source tree) for details.

Vaucanson was released under the GNU Lesser General Public Licence until
version 0.7.


Contacts
========

The team can be reached by mail at vaucanson@lrde.epita.fr. Snail mail
addresses follow.

* Vaucanson - ENST

  | Jacques Sakarovitch
  | 46, rue Barrault
  | F-75013 Paris
  | France

* Vaucanson - LIAFA

  | Sylvain Lombardy
  | 175, rue du Chevaleret
  | F-75013 Paris
  | France

* Vaucanson - LRDE

  | 24,rue Pasteur
  | Paristalie, batiment X, aile Mistral
  | F-94270 Le Kremlin Bicêtre cedex
  | France

.. Local Variables:
.. mode: rst
.. End:
