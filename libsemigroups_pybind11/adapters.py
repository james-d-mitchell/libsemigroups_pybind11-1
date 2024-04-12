# -*- coding: utf-8 -*-

# Copyright (c) 2024, J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

# pylint:disable=no-name-in-module, unused-import

"""
This package provides the user-facing python part of libsemigroups_pybind11 for
various adapters from libsemigroups.
"""
from _libsemigroups_pybind11 import (
    ImageRightActionBMat8BMat8 as _ImageRightActionBMat8BMat8,
)
from _libsemigroups_pybind11 import BMat8


def ImageRightAction(**kwargs):  # pylint: disable=invalid-name
    """
    Construct a ImageRightAction instance.

    :Keyword Arguments:
        * *element* -- the type of the elements in the action
        * *point* -- the type of the points acted on
    """
    if len(kwargs) != 2:
        raise TypeError(f"expected 2 keyword arguments, found {len(kwargs)}")
    for kwarg in ("element", "point"):
        if kwarg not in kwargs:
            raise ValueError(
                f'unexpected keyword argument "{kwarg}", expected'
                + '"element", "point", and "func"'
            )

    if kwargs["element"] == BMat8 and kwargs["point"] == BMat8:
        return _ImageRightActionBMat8BMat8

    raise ValueError("unexpected keyword argument combination")
