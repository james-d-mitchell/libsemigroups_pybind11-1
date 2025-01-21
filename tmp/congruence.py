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
    congruence_non_trivial_classes as non_trivial_classes,
    congruence_partition as partition,
)

from .knuth_bendix import KnuthBendix

from .detail.decorators import (
    may_return_positive_infinity as _may_return_positive_infinity,
)


def _get(self: Congruence, t: type) -> Union[KnuthBendix, ToddCoxeter, Kambites]:
    """
    Returns the *t* instance used to compute the congruence (if any).

    This function returns (a copy of) the object of type *t* used to compute
    the congruence (if any). If there is no such object, then an exception is
    raised.

    :param t:
        The type of object being sought (must be :any:`Kambites`,
        :any:`KnuthBendixRewriteTrie`, or :any:`ToddCoxeter`).
    :type t: type

    :returns: A copy of the instance of type *t*.

    :raises LibsemigroupsError:
        if there is no object of type *t* within *self*.
    """
    if t is KnuthBendix:
        return self._get_knuth_bendix()
    if t is ToddCoxeter:
        return self._get_todd_coxeter()
    if t is Kambites:
        return self._get_kambites()


def _has(self: Congruence, t: type) -> bool:
    """
    Returns whether or not there is an instance of type *t* within the
    congruence.

    This function returns ``True`` if *self* contains an instance of type *t*,
    and ``False`` if not.

    :param t:
        The type of object being sought (must be :any:`Kambites`,
        :any:`KnuthBendixRewriteTrie`, or :any:`ToddCoxeter`).
    :type t: type

    :returns: Whether or not there is an object of type *t* in *self*.
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
