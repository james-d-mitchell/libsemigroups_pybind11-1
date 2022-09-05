.. Copyright (c) 2022, J. D. Mitchell

   Distributed under the terms of the GPL license version 3.

   The full license is in the file LICENSE, distributed with this software.

Presentation
============

.. py:class:: Presentation

   This page contains the documentation for functionality in
   ``libsemigroups_pybind11`` for the creating finite semigroup and monoid
   presentations.

   While :py:class:`Presentation` is not a class, the objects returned by
   :py:class:`Presentation` have identical methods, and so we document
   :py:class:`Presentation` as if it was a class.

.. toctree::
   :hidden:

   init
   generators
   settings
   membership
   accessors
   attributes
   idempotents
   cayley-graphs
   factorisation
   prefix
   runner

Constructors
------------

.. list-table::
   :widths: 50 50
   :header-rows: 0

   * - :py:meth:`FroidurePin.__init__`
     - Overloaded function.

Generators
----------

.. list-table::
   :widths: 50 50
   :header-rows: 0

   * - :py:meth:`FroidurePin.add_generator`
     - Add a copy of an element to the generators.
