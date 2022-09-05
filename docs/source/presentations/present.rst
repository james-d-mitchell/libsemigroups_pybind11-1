.. Copyright (c) 2022, J. D. Mitchell

   Distributed under the terms of the GPL license version 3.

   The full license is in the file LICENSE, distributed with this software.

Presentation
============

.. py:class:: Presentation

   This page describes the functionality in ``Presentation``.

   The objects returned by ``Presentation`` can be used to construction
   presentations for semigroups or monoids and is intended to be used as the
   input to other algorithms. The idea is to provide a shallow wrapper around a
   list of words represented by lists of integers or strings. We refer to this
   list of words as the **rules** of the presentation. The objects returned by ``Presentation``
   also provide some methods for checking that the rules really defines a
   presentation, (i.e. it's consistent with its alphabet). Some related
   functionality is available in ``libsemigroups_pybind11.presentation``.

   While :py:class:`Presentation` is not a class, the objects returned by
   :py:class:`Presentation` have identical methods, and so we document
   :py:class:`Presentation` as if it was a class.


.. py:method:: Presentation.__init__(self: FroidurePin, that: FroidurePin) -> None

     Copy constructor.

     Constructs a new :py:class:`FroidurePin` which is an exact copy of
     ``that``. No enumeration is triggered for either ``that`` or of the newly
     constructed :py:class:`FroidurePin`.

     :Parameters:
       **that** (FroidurePin) the ``FroidurePin`` to copy.
