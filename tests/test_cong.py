# -*- coding: utf-8 -*-

# Copyright (c) 2021-2024 J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

"""
This file contains tests for Congruence from libsemigroups_pybind11.
"""

# pylint: disable=no-name-in-module, missing-function-docstring, invalid-name

from datetime import timedelta

import pytest

from libsemigroups_pybind11 import (
    Congruence,
    ReportGuard,
    congruence_kind,
    Presentation,
    presentation,
    POSITIVE_INFINITY,
    ToddCoxeter,
    Kambites,
    KnuthBendix,
    LibsemigroupsError,
    congruence,
)


def test_018():
    ReportGuard(False)
    p = Presentation([0, 1, 2])
    presentation.add_rule(p, [0, 0], [0, 0])
    presentation.add_rule(p, [0, 1], [1, 0])
    presentation.add_rule(p, [0, 2], [2, 0])
    presentation.add_rule(p, [0, 0], [0])
    presentation.add_rule(p, [0, 2], [0])
    presentation.add_rule(p, [2, 0], [0])
    presentation.add_rule(p, [1, 0], [0, 1])
    presentation.add_rule(p, [1, 1], [1, 1])
    presentation.add_rule(p, [1, 2], [2, 1])
    presentation.add_rule(p, [1, 1, 1], [1])
    presentation.add_rule(p, [1, 2], [1])
    presentation.add_rule(p, [2, 1], [1])

    cong = Congruence(congruence_kind.twosided, p)
    cong.add_generating_pair([0], [1])
    assert not cong.finished()
    assert cong.number_of_classes() == POSITIVE_INFINITY
    assert cong.finished()

    assert sorted(congruence.non_trivial_classes(cong, p)) == [
        [[1], [0, 1], [1, 1], [0, 1, 1], [0]]
    ]
    # The next line does nothing except check that it's possible to call
    # `run_for` with a timedelta
    cong.run_for(timedelta(seconds=1))


def test_has_get():
    p = Presentation("ab")
    presentation.add_rule(p, "abab", "a" * 6)
    presentation.add_rule(p, "ba", "ababbb")

    c = Congruence(congruence_kind.twosided, p)

    assert c.number_of_runners() == 4
    assert c.has(ToddCoxeter)
    tc = c.get(ToddCoxeter)

    assert c.number_of_classes() == POSITIVE_INFINITY
    assert c.number_of_runners() == 1
    assert not c.has(ToddCoxeter)
    assert not c.has(Kambites)
    assert c.has(KnuthBendix)
    assert c.get(KnuthBendix).confluent()

    # Check that the ToddCoxeter returned above outlives its deletion in
    # Congruence
    assert tc.number_of_classes() == POSITIVE_INFINITY

    with pytest.raises(LibsemigroupsError):
        c.get(ToddCoxeter)
