# -*- coding: utf-8 -*-

# Copyright (c) 2024, J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

# pylint:disable=no-name-in-module, unused-import

"""
This package provides the user-facing python part of libsemigroups_pybind11 for
the Action class from libsemigroups.
"""

from _libsemigroups_pybind11 import RowActionBMat8 as _RowActionBMat8
from _libsemigroups_pybind11 import BMat8
from .adapters import ImageRightAction


def RightAction(
    func=ImageRightAction, **kwargs
):  # pylint: disable=invalid-name
    """
    Construct a RightAction instance.

    :Keyword Arguments:
        * *element* -- the type of the elements in the action
        * *point* -- the type of the points acted on
        * *func* -- the function defining the action
    """
    if len(kwargs) != 2:
        raise TypeError(
            f"expected 3 keyword arguments, found {len(kwargs) + 1}"
        )
    for kwarg in ("element", "point"):
        if kwarg not in kwargs:
            raise ValueError(
                f'unexpected keyword argument "{kwarg}", expected'
                + '"element", "point", and "func"'
            )

    if (
        kwargs["element"] == BMat8
        and kwargs["point"] == BMat8
        and func == ImageRightAction
    ):
        return _RowActionBMat8()
    raise ValueError("unexpected keyword argument combination")
