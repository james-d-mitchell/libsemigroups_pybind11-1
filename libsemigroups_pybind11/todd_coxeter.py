# -*- coding: utf-8 -*-

# Copyright (c) 2024 J. D. Mitchell
#
# Distributed under the terms of the GPL license version 3.
#
# The full license is in the file LICENSE, distributed with this software.

# pylint: disable=no-name-in-module, invalid-name, missing-function-docstring
# pylint: disable=unused-import, missing-module-docstring, protected-access

from typing import Union, List, Iterator, Self

from _libsemigroups_pybind11 import (
    PositiveInfinity,
    PresentationStrings as _PresentationStrings,
    PresentationWords as _PresentationWords,
    ToddCoxeterBase,
    ToddCoxeterString as _ToddCoxeterString,
    ToddCoxeterWord as _ToddCoxeterWord,
    Undefined,
    WordGraph as _WordGraph,
    class_by_index,
    class_of,
    congruence_kind as _congruence_kind,
    todd_coxeter_non_trivial_classes as non_trivial_classes,
    todd_coxeter_normal_forms as normal_forms,
    todd_coxeter_partition as partition,
    todd_coxeter_redundant_rule as redundant_rule,
)

from .detail.decorators import (
    may_return_positive_infinity as _may_return_positive_infinity,
    may_return_undefined as _may_return_undefined,
    template_params_as_kwargs as _template_params_as_kwargs,
)

from .detail.cxx_wrapper import (
    CxxWrapper,
)


def ToddCoxeter(*args, **kwargs):
    """TODO(0) doc"""
    if len(args) != 0 and len(kwargs) != 0:
        raise TypeError(
            f'expected positional arguments or 1 keyword arguments ("Word") but found {len(args)} and {len(kwargs)}'
        )
    if len(args) == 0:
        if "Word" not in kwargs:
            if len(kwargs) == 0:
                msg = ""
            else:
                msg = 'but found "{next(iter(kwargs.keys()))}"'
            raise TypeError(f'expected the keyword argument "Word" {msg}')
        if kwargs["Word"] is str:
            return _ToddCoxeterString()
        if kwargs["Word"] is List[int]:
            return _ToddCoxeterWord()
        raise ValueError(
            f'expected the keyword argument "Word" to be str or List[int] but found {kwargs["Word"]}'
        )

    if len(args) == 2:
        if not isinstance(args[0], _congruence_kind):
            raise TypeError(
                f"expected the 1st argument to be congruence_kind but found {type(args[0])}"
            )

        if type(args[1]) in (_PresentationStrings, _ToddCoxeterString):
            return _ToddCoxeterString(*args)
        elif type(args[1]) in (
            _PresentationWords,
            _ToddCoxeterWord,
            _WordGraph,
        ):
            return _ToddCoxeterWord(*args)
        else:
            raise TypeError(
                f"expected the 2nd argument to be Presentation, ToddCoxeter or WordGraph but found {type(args[1])}"
            )
    else:
        raise TypeError(f"expected 0 or 2 positional arguments, found {len(args)}")


for _ToddCoxeter in [_ToddCoxeterWord, _ToddCoxeterString]:
    _ToddCoxeter.number_of_classes = _may_return_positive_infinity(
        _ToddCoxeter._number_of_classes
    )
    _ToddCoxeter.number_of_classes.__doc__ = "\n".join(
        _ToddCoxeter._current_index_of.__doc__.split("\n")[1:]
    )

    _ToddCoxeter.current_index_of = _may_return_undefined(
        _ToddCoxeter._current_index_of
    )
    _ToddCoxeter.current_index_of.__doc__ = "\n".join(
        _ToddCoxeter._current_index_of.__doc__.split("\n")[1:]
    )

########################################################################
# Helper functions
########################################################################

# def fancy_dot(tc: ToddCoxeter) -> _Dot:
#    dot = word_graph.dot(tc.word_graph())
#    offset = 0 if tc.presentation().contains_empty_word() else 1
#    dot.node("0").add_attr("label", "ε")
#    tree = tc.spanning_tree()
#    for i in range(1, tc.number_of_classes() + offset):
#        w = tc.word_of(i - offset)
#        dot.node(str(i)).add_attr("label", "".join([chr(x) for x in w]))
#        if len(w) == 1:
#            dot.node(str(i)).add_attr(
#                "color", dot.edge("0", str(i)).attrs["color"]
#            ).add_attr("style", "filled")
#        if tree.parent(i) != 18446744073709551615:
#            dot.edge(str(tree.parent(i)), str(i)).add_attr(
#                "style", "dashed,bold"
#            )
#
#    return dot
