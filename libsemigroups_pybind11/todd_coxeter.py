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
    ToddCoxeterString as _ToddCoxeterString,
    ToddCoxeterWord as _ToddCoxeterWord,
    # _str_class_by_index,
    # _word_class_by_index,
    # class_of,
    # todd_coxeter_is_non_trivial as is_non_trivial,
    # todd_coxeter_redundant_rule as redundant_rule,
    # todd_coxeter_str_normal_forms as _str_normal_forms,
    # todd_coxeter_word_normal_forms as _word_normal_forms,
    # toddcoxeter_non_trivial_classes as non_trivial_classes,
    # toddcoxeter_partition as partition,
)

from .detail.decorators import (
    may_return_positive_infinity as _may_return_positive_infinity,
    may_return_undefined as _may_return_undefined,
    template_params_as_kwargs as _template_params_as_kwargs,
)

from .detail.cxx_wrapper import (
    CxxWrapper,
)


class ToddCoxeter(CxxWrapper):
    _py_to_cxx_type_dict = {
        (List[int],): _ToddCoxeterWord,
        (str,): _ToddCoxeterString,
    }

    def __init__(self: Self, *args, **kwargs):
        # TODO handle wrong args, and Word = kwargs for default construction
        if len(args) == 2:
            if type(args[1]) is _PresentationStrings:
                self._cxx_obj = _ToddCoxeterString(*args)
            elif type(args[1]) is _PresentationWords:
                self._cxx_obj = _ToddCoxeterWord(*args)

    @_may_return_positive_infinity
    def number_of_classes(self: Self) -> PositiveInfinity | int:
        return self._cxx_obj._number_of_classes()


# def noop():
#     pass
#
#
# ToddCoxeter.number_of_classes = _may_return_positive_infinity(
#     ToddCoxeter._number_of_classes
# )
# ToddCoxeter.number_of_classes.__doc__ = "\n".join(
#     ToddCoxeter._number_of_classes.__doc__.split("\n")[1:]
# )
#
# ToddCoxeter.current_index_of = _may_return_undefined(ToddCoxeter._current_index_of)
# ToddCoxeter.current_index_of.__doc__ = "\n".join(
#     ToddCoxeter._current_index_of.__doc__.split("\n")[1:]
# )
#
#
# ToddCoxeter.current_word_of = _template_params_as_kwargs(
#     Word={
#         str: ToddCoxeter._current_str_of,
#         List[int]: ToddCoxeter._current_word_of,
#     }
# )(noop)
#
#
# ToddCoxeter.current_word_of.__doc__ = """
# :sig=(i: int, **kwargs) -> List[int] | str:
# Returns a current word representing a class with given index.
#
# This function returns the current word representing the class with index *i*.
# No enumeration is triggered by calls to this function, but
# :any:`current_word_graph` is standardized (using :any:`Order.shortlex`) if it
# is not already standardized. The output word is obtained by following a path in
# :any:`current_spanning_tree` from the node corresponding to index *i* back to
# the root of that tree.
#
# :param i: the index of the class.
# :type i: int
#
# :Keyword Arguments:
#    * *Word* (``type``) -- type of the output words (must be ``str`` or ``List[int]``).
#
# :returns: The word representing the *i*-th class.
# :rtype: List[int] | str
#
# :raises LibsemigroupsError:  if *i* is out of bounds.
#
# :raises TypeError:
#     if the keyword argument *Word* is not present, any other keyword
#     argument is present, or is present but has value other than ``str`` or
#     ``List[int]``.
# """
#
# ToddCoxeter.word_of = _template_params_as_kwargs(
#     Word={
#         str: ToddCoxeter._str_of,
#         List[int]: ToddCoxeter._word_of,
#     }
# )(noop)
#
# ToddCoxeter.word_of.__doc__ = """
# :sig=(i: int, **kwargs) -> List[int] | str:
# Returns a word representing a class with given index.
#
# This function returns the word representing the class with index *i*. A full
# enumeration is triggered by calls to this function. The output word is obtained
# by following a path in :any:`current_spanning_tree` from the node corresponding
# to index *i* back to the root of that tree.
#
# :param i: the index of the class.
# :type i: int
#
# :Keyword Arguments:
#    * *Word* (``type``) -- type of the output words (must be ``str`` or ``List[int]``).
#
# :returns: The word representing the *i*-th class.
# :rtype: List[int]
#
# :raises LibsemigroupsError:  if *i* is out of bounds.
#
# :raises TypeError:
#     if the keyword argument *Word* is not present, any other keyword
#     argument is present, or is present but has value other than ``str`` or
#     ``List[int]``.
# """
#
#
# # The next function (normal_forms) is documented here not in the cpp
# # file because we add the additional kwarg Word.
# @_template_params_as_kwargs(
#     Word={str: _str_normal_forms, List[int]: _word_normal_forms}
# )
# def normal_forms(  # pylint: disable=unused-argument
#     tc: ToddCoxeter,
#     **kwargs,
# ) -> Iterator[Union[str, List[int]]]:
#     r"""
#     Returns an iterator yielding normal forms.
#
#     This function returns an iterator yielding normal forms of the classes of
#     the congruence represented by an instance of :any:`ToddCoxeter`. The order of
#     the classes, and the normal forms, that are returned are controlled by
#     :any:`ToddCoxeter.standardize`. This function triggers a full enumeration of
#     ``tc``.
#
#     :param tc: the ToddCoxeter instance.
#     :type tc: ToddCoxeter
#
#     :Keyword Arguments:
#         * *Word* (``type``) -- type of the output words (must be ``str`` or ``List[int]``).
#
#     :returns: An iterator yielding normal forms.
#     :rtype: Iterator[str | List[int]]
#
#     :raises TypeError:
#         if the keyword argument *Word* is not present, any other keyword
#         argument is present, or is present but has value other than ``str`` or
#         ``List[int]``.
#     """
#
#
# # The next function (class_by_index) is documented here not in the cpp
# # file because we add the additional kwarg Word.
# @_template_params_as_kwargs(
#     Word={str: _str_class_by_index, List[int]: _word_class_by_index}
# )
# def class_by_index(kb: ToddCoxeter, **kwargs) -> Iterator[Union[str, List[int]]]:  # pylint: disable=unused-argument
#     """
#     Returns an iterator yielding every word ``List[int]`` or ``str`` in the
#     congruence class with given index.
#
#     This function returns an iterator yielding every word belonging to the
#     class with index *n* in the congruence represented by the :any:`ToddCoxeter`
#     instance *tc*. Calls to this function trigger a full enumeration of *tc*.
#
#     :param tc: the ToddCoxeter instance.
#     :type tc: ToddCoxeter
#
#     :param n: the index of the class.
#     :type n: int
#
#     :Keyword Arguments:
#         * *Word* (``type``) -- type of the output words (must be ``str`` or ``List[int]``).
#
#     :returns: A iterator yielding the class with index *n*.
#     :rtype: Iterator[List[int]]
#
#     :raises LibsemigroupsError:
#         if *n* is greater than or equal to ``tc.number_of_classes()``.
#
#     :raises TypeError:
#         if the keyword argument *Word* is not present, any other keyword
#         argument is present, or is present but has value other than ``str`` or
#         ``List[int]``.
#     """
#
#
# # def fancy_dot(tc: ToddCoxeter) -> _Dot:
# #    dot = word_graph.dot(tc.word_graph())
# #    offset = 0 if tc.presentation().contains_empty_word() else 1
# #    dot.node("0").add_attr("label", "ε")
# #    tree = tc.spanning_tree()
# #    for i in range(1, tc.number_of_classes() + offset):
# #        w = tc.word_of(i - offset)
# #        dot.node(str(i)).add_attr("label", "".join([chr(x) for x in w]))
# #        if len(w) == 1:
# #            dot.node(str(i)).add_attr(
# #                "color", dot.edge("0", str(i)).attrs["color"]
# #            ).add_attr("style", "filled")
# #        if tree.parent(i) != 18446744073709551615:
# #            dot.edge(str(tree.parent(i)), str(i)).add_attr(
# #                "style", "dashed,bold"
# #            )
# #
# #    return dot
