===========================
 Introduction to Vaucanson
===========================

:Date: 2005-01-15

Vaucanson_, a C++ generic library for weighted finite state machine.

.. _Vaucanson: http://www.lrde.epita.fr/vaucanson

.. contents::


Overview
========

Firstly  initiated by  Jacques  Sakarovitch in  2000,  Vaucanson is  a
project   developed   by   the   Ecole   Nationale   Supérieure   des
Télécommunications [1] and the EPITA Research and Development Laboratory
(LRDE) [2].

.. [1] http://www.enst.fr

.. [2] http://www.lrde.epita.fr

The goal of this library is  to enable the development of C++ programs
in  an abstract  and  general way  with,  at the  same  time, a  large
specialization power. Indeed, on the one hand, we can write algorithms
working on  every automaton with  weights over any semirings  and with
words  from any  free monoids.  And on  the other  hand,  a particular
algorithm  can   be  specialized  for  a   particular  data  structure
implementing only a pseudo behaviour.

Yet,  Vaucanson  is  still  in  a fundamental  development  phase  and
algorithms, data  structures and  global architecture are  not totally
stable and well tested.  In the ``doc/help`` directory, you can find a
short howto to start programming with Vaucanson. The ``src`` directory
contains  several  demonstrations,  but  you  can  also  look  at  the
``include/vaucanson/algorithms``  to be  introduced to  the  basics of
Vaucanson.

Please send  any question or  comments to ``vaucanson@lrde.epita.fr``,
and bug reports to ``vaucanson-bugs@lrde.epita.fr``.

Installation
============

See   the   documentation   file  ``INSTALL.txt``   for   installation
instructions.

Licence
=======

Vaucanson  is released under  the GNU  Lesser General  Public Licence.
See the file ``COPYING`` for details.


Contacts
========

The team can be  reached by mail at ``vaucanson@lrde.epita.fr``. Snail
mail addresses follow.

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

