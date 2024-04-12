.. Copyright (c) 2024, James D. Mitchell

    Distributed under the terms of the GPL license version 3.

    The full license is in the file LICENSE, distributed with this software.

.. currentmodule:: _libsemigroups_pybind11

Actions
=======

This page contains details of the `RowActionBMat8` and `LeftAction` classes in
``libsemigroups_pybind11`` for finding actions of semigroups, or groups, on sets.  The
notion of an "action" in the context of ``libsemigroups_pybind11`` is analogous to the
notion of an orbit of a group.

The function :any:`RowActionBMat8.run` finds points that can be obtained by acting
on the seeds of ``self`` by the generators of ``self`` until no further points
can be found, or :any:`RowActionBMat8.stopped` returns ``True``.  This is achieved
by performing a breadth first search.

In this documentation we refer to:

* elements (being the elements of the underlying semigroup)

* points (being the objects on which the semigroup elements act)

* the side of the action (if it is a left or a right action).

.. doctest::

  >>> from libsemigroups_pybind11 import RightAction, BMat8
  ... o = RightAction(element=BMat8, point=BMat8)
  ... o.add_seed(BMat8([[1, 1, 1, 0], 
  ...                   [1, 1, 0, 0], 
  ...                   [0, 1, 0, 1], 
  ...                   [0, 1, 0, 0]]).row_space_basis())
  ... o.add_generator(
  ...     BMat8([[1, 0, 0, 0], 
  ...            [0, 1, 0, 0], 
  ...            [0, 0, 1, 0], 
  ...            [0, 0, 0, 1]]))
  ... o.add_generator(
  ...     BMat8([[0, 1, 0, 0], 
  ...            [1, 0, 0, 0], 
  ...            [0, 0, 1, 0], 
  ...            [0, 0, 0, 1]]))
  ... o.add_generator(
  ...     BMat8([[0, 1, 0, 0], 
  ...            [0, 0, 1, 0], 
  ...            [0, 0, 0, 1], 
  ...            [1, 0, 0, 0]]))
  ... o.add_generator(
  ...     BMat8([[1, 0, 0, 0], 
  ...            [0, 1, 0, 0], 
  ...            [0, 0, 1, 0], 
  ...            [1, 0, 0, 1]]))
  ... o.add_generator(
  ...     BMat8([[1, 0, 0, 0], 
  ...            [0, 1, 0, 0], 
  ...            [0, 0, 1, 0], 
  ...            [0, 0, 0, 0]]))
  ... o.size()
  553

Contents
--------

.. autosummary::
    :nosignatures:

    ~RowActionBMat8
    RowActionBMat8.add_generator
    RowActionBMat8.add_seed
    RowActionBMat8.at
    RowActionBMat8.cache_scc_multipliers
    RowActionBMat8.current_size
    RowActionBMat8.empty
    RowActionBMat8.init
    RowActionBMat8.iterator
    RowActionBMat8.multiplier_from_scc_root
    RowActionBMat8.multiplier_to_scc_root
    RowActionBMat8.position
    RowActionBMat8.reserve
    RowActionBMat8.root_of_scc
    RowActionBMat8.scc
    RowActionBMat8.size
    RowActionBMat8.word_graph


RightAction Methods
-------------------
.. autoclass:: RowActionBMat8
    :no-undoc-members:
    :members:

Runner Methods
--------------
.. autoclass:: RowActionBMat8
   :noindex:
   :inherited-members:
