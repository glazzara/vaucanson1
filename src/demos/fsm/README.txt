===================================
 FSM_ -like toolbox for Vaucanson_
===================================

:Author: Yann Regis-Gianas
:Date: March 2004
:Version: $Id$

.. contents::

Introduction
============

This  demo is  meant  to generate  toolboxes  "à la"  FSM_ [1] from  a
configuration file ``toolbox.hh`` that  defines what kind of automaton
the user wants to manipulate.

The generated files can be  used to benchmark Vaucanson_ in comparison
with FSM when it is instantiated with different implementations.

.. _Vaucanson: http://www.lrde.epita.fr/vaucanson

.. _FSM:
.. [1] http://www.research.att.com/~mohri/fsm/

Usage
=====

1. create a directory (e.g. ``automaton_t``),
	
2. in   this   directory,   create   the  files   ``toolbox.hh``   and
   ``toolbox.cc``. They should define a type ``automaton_t`` (the type
   of automaton)  and a function  ``series`` which returns  the series
   that are used in the toolbox.  For example, look at the distributed
   files ``usual_automaton_t/toolbox.{hh,cc}``.

3. use  the script ``./generate_toolbox.sh``  to generate  the toolbox
   sources, like this::
	
     ./generate_toolbox.sh [dirname]

4. in the directory, do::

     autoreconf
     ./configure CPPFLAGS="-I your_vaucanson_include_dir"
     make

Contact
=======

Please send any comments or wanted features to
``vaucanson@lrde.epita.fr``.

