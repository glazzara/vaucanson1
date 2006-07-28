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
	make sanity-check
	make check ([1])
	make install (as root)

Note that an installation is  specific to the compiler used to install
it. Indeed, the call  to ``./configure`` enables some workarounds and,
consequently,  users must  compile  with the  same  compiler to  avoid
compatibility problems.

[1]: Optional: check  the whole library. Note that  this process takes
about 1.5 Go of free space (memory swap included) and several hours.

Additional features
-------------------

There  is a  Python  interpreter in  the  package. It  is disabled  by
default because its compilation takes  several hours. If you have time
to spare, use::

	./configure --enable-vaucanswig

There  is an  XML  I/O subsystem  in  the library.  It  is enabled  by
default,  but  requires a  working  installation  of another  software
package called Xerces-C++. If you do  not have this package, or if you
do not want to use XML I/O in Vaucanson, you can use::

	./configure --disable-xml

To specify a special path for the Xerces-C library::

	./configure --with-xerces=/absolute/path/to/xerces

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

Vaucanson was tested with the `GNU C++ Compiler (GCC)`_ version 3.[34]
and 4.0,  and should work  with ICC_ 9.   The code is  fully compliant
with  the  ISO  C++  standard  (ISO-IEC  14882)  to  permit  a  higher
portability in the future.

.. _GNU C++ Compiler (GCC): http://gcc.gnu.org/
.. _ICC: http://www.intel.com/software/products/compilers/

A  known bug in  GCC 4.0.0  for MacOs  is supported  to make  the code
compliant  with this specific  compiler version,  but MacOs  users are
encouraged to  upgrade their compiler.   They should also  notice that
their  platform   allows  to  select  their   default  compiler  using
``gcc_select``.  GCC 4.0 is preferred.

High verbose  mode of the testing  suites uses the AT&T  dot format to
save automaton in  a human readable file.  Use  Graphviz_ to visualize
these .dot files.

.. _Graphviz: http://www.research.att.com/sw/tools/graphviz/

If  you want  to use  the XML  I/O system,  you will  need  the Apache
`Xerces-C++`_ library version 2.3 or above.

.. _Xerces-C++: http://xml.apache.org/xerces-c/


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
