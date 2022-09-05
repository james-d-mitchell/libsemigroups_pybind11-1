# -*- coding: utf-8 -*-
# pylint: disable=no-name-in-module, missing-function-docstring
# pylint: disable=missing-class-docstring, invalid-name, redefined-outer-name

# Copyright (c) 2022, J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

"""
This module contains some tests for the Presentation class.
"""

import pytest

from libsemigroups_pybind11 import Presentation
from libsemigroups_pybind11 import presentation


def check_constructors(p):
    p.validate()
    pp = Presentation(p)
    pp.validate()
    assert pp.alphabet() == p.alphabet()
    assert pp.rules == p.rules


def test_constuctors():
    p = Presentation([0, 1, 2])
    presentation.add_rule(p, [0, 0, 0], [0])
    assert len(p.rules) == 2
    presentation.add_rule_and_check(p, [0, 0, 0], [0])
    p.validate()
    check_constructors(p)

    p = Presentation("abc")
    presentation.add_rule(p, "aaa", "a")
    assert len(p.rules) == 2
    presentation.add_rule_and_check(p, "aaa", "a")
    p.validate()
    check_constructors(p)
