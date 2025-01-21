# -*- coding: utf-8 -*-

# Copyright (c) 2024 J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

# pylint: disable=unused-import, no-name-in-module

"""
This package provides the user-facing python part of libsemigroups_pybind11 for
the libsemigroups::kambites namespace from libsemigroups.
"""

from _libsemigroups_pybind11 import (
    kambites_normal_forms as normal_forms,
    kambites_non_trivial_classes as non_trivial_classes,
    kambites_partition as partition,
    Kambites,
)

from .detail.decorators import (
    may_return_positive_infinity as _may_return_positive_infinity,
)

Kambites.number_of_classes = _may_return_positive_infinity(Kambites._number_of_classes)
Kambites.number_of_classes.__doc__ = "\n".join(
    Kambites._number_of_classes.__doc__.split("\n")[1:]
)

Kambites.small_overlap_class = _may_return_positive_infinity(
    Kambites._small_overlap_class
)
Kambites.small_overlap_class.__doc__ = "\n".join(
    Kambites._small_overlap_class.__doc__.split("\n")[1:]
)
