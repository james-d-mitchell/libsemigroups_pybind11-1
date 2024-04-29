# -*- coding: utf-8 -*-

# Copyright (c) 2024, J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

"""
This module contains some tests for the libsemigroups_pybind11 functionality
arising from action.*pp in libsemigroups.
"""

# pylint: disable=no-name-in-module, missing-function-docstring, invalid-name


from libsemigroups_pybind11 import RightAction, LeftAction, BMat8, PPerm
from libsemigroups_pybind11.bmat8 import row_space_basis, col_space_basis
from _libsemigroups_pybind11 import PPerm16


def test_action_001():
    rows = RightAction(Point=BMat8, Element=BMat8)
    rows.add_seed(
        row_space_basis(
            BMat8([[1, 1, 1, 0], [1, 1, 0, 0], [0, 1, 0, 1], [0, 1, 0, 0]])
        )
    )

    rows.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    )
    rows.add_generator(
        BMat8([[0, 1, 0, 0], [1, 0, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    )
    rows.add_generator(
        BMat8([[0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1], [1, 0, 0, 0]])
    )
    rows.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [1, 0, 0, 1]])
    )
    rows.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 0]])
    )

    assert rows.size() == 553
    rows.init()

    rows.add_seed(
        row_space_basis(
            BMat8([[1, 1, 1, 0], [1, 1, 0, 0], [0, 1, 0, 1], [0, 1, 0, 0]])
        )
    )

    rows.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    )
    rows.add_generator(
        BMat8([[0, 1, 0, 0], [1, 0, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    )
    rows.add_generator(
        BMat8([[0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1], [1, 0, 0, 0]])
    )
    rows.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [1, 0, 0, 1]])
    )
    rows.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 0]])
    )

    assert rows.size() == 553

    cols = LeftAction(Point=BMat8, Element=BMat8)
    cols.add_seed(
        col_space_basis(
            BMat8([[1, 1, 1, 0], [1, 1, 0, 0], [0, 1, 0, 1], [0, 1, 0, 0]])
        )
    )

    cols.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    )
    cols.add_generator(
        BMat8([[0, 1, 0, 0], [1, 0, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
    )
    cols.add_generator(
        BMat8([[0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1], [1, 0, 0, 0]])
    )
    cols.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [1, 0, 0, 1]])
    )
    cols.add_generator(
        BMat8([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 0]])
    )

    assert cols.size() == 553
    assert cols != rows


def test_action_002():
    o = RightAction(Point=PPerm16, Element=PPerm16)

    o.add_seed(PPerm(list(range(8)), list(range(8)), 8))
    o.add_generator(
        PPerm([0, 1, 2, 3, 4, 5, 6, 7], [1, 2, 3, 4, 5, 6, 7, 0], 8)
    )
    o.add_generator(
        PPerm([0, 1, 2, 3, 4, 5, 6, 7], [1, 0, 2, 3, 4, 5, 6, 7], 8)
    )
    o.add_generator(PPerm([1, 2, 3, 4, 5, 6, 7], [0, 1, 2, 3, 4, 5, 6], 8))
    o.add_generator(PPerm([0, 1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6, 7], 8))
    assert o.size() == 256
    o.init()
    assert o.size() == 0
    o.add_seed(PPerm(list(range(8)), list(range(8)), 8))
    o.add_generator(
        PPerm([0, 1, 2, 3, 4, 5, 6, 7], [1, 2, 3, 4, 5, 6, 7, 0], 8)
    )
    o.add_generator(
        PPerm([0, 1, 2, 3, 4, 5, 6, 7], [1, 0, 2, 3, 4, 5, 6, 7], 8)
    )
    o.add_generator(PPerm([1, 2, 3, 4, 5, 6, 7], [0, 1, 2, 3, 4, 5, 6], 8))
    o.add_generator(PPerm([0, 1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6, 7], 8))
    assert o.size() == 256
