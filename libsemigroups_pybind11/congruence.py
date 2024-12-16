# -*- coding: utf-8 -*-

# Copyright (c) 2024 J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

# pylint: disable=no-name-in-module, invalid-name, unused-import, fixme

"""
This package provides the user-facing python part of libsemigroups_pybind11 for
the libsemigroups::congruence namespace from libsemigroups.
"""

from typing import Union

from _libsemigroups_pybind11 import (
    ToddCoxeter,
    Kambites,
    Congruence,
    LibsemigroupsError,
)

from .knuth_bendix import KnuthBendix

from .detail.decorators import (
    may_return_positive_infinity as _may_return_positive_infinity,
)


def _get(self: Congruence, t: type) -> Union[KnuthBendix, ToddCoxeter, Kambites]:
    """
    TODO
    """
    if t is KnuthBendix:
        return self._get_knuth_bendix()
    if t is ToddCoxeter:
        return self._get_todd_coxeter()
    if t is Kambites:
        return self._get_kambites()


def _has(self: Congruence, t: type) -> bool:
    """
    TODO
    """
    if t is KnuthBendix:
        return self._has_knuth_bendix()
    if t is ToddCoxeter:
        return self._has_todd_coxeter()
    if t is Kambites:
        return self._has_kambites()


Congruence.get = _get
Congruence.has = _has

Congruence.number_of_classes = _may_return_positive_infinity(
    Congruence._number_of_classes
)
Congruence.number_of_classes.__doc__ = "\n".join(
    Congruence._number_of_classes.__doc__.split("\n")[1:]
)

Congruence.max_threads = _may_return_positive_infinity(Congruence._max_threads)
Congruence.max_threads.__doc__ = "\n".join(
    Congruence._max_threads.__doc__.split("\n")[1:]
)
