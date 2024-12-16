.. Copyright (c) 2021-2024 J. D. Mitchell

   Distributed under the terms of the GPL license version 3.

   The full license is in the file LICENSE, distributed with this software.

.. currentmodule:: _libsemigroups_pybind11

Knuth-Bendix helpers
====================

This page contains the documentation for various helper functions for
manipulating :any:`KnuthBendixRewriteTrie` objects. All such functions are
contained in the submodule ``libsemigroups_pybind11.knuth_bendix``.

.. seealso::
   :py:class:`overlap`


Contents
--------

.. currentmodule:: libsemigroups_pybind11.knuth_bendix

.. autosummary::
   :nosignatures:

   by_overlap_length
   is_reduced
   non_trivial_classes
   normal_forms
   redundant_rule

Full API
--------

.. automodule:: libsemigroups_pybind11.knuth_bendix
   :members:
   :imported-members:
   :exclude-members: KnuthBendix, non_trivial_classes

.. The next two functions are documented here because there are two overloads
   and JDM couldn't figure out a better way of doing this.

.. function:: non_trivial_classes(ci: KnuthBendixRewriteTrie, words: List[Union[str, List[int]]]) -> List[List[Union[str, List[int]]]]:

    Find the non-trivial classes in the partition of a list of words.

    This function returns the classes with size at least :math:`2` in the
    partition of the words in the list *words* induced by the
    :any:`KnuthBendixRewriteTrie` instance *ci*.

    :param ci: the :any:`KnuthBendixRewriteTrie` instance.
    :type ci: KnuthBendixRewriteTrie

    :param words: the input list of words.
    :type words: List[List[int] | str]

    :returns: The partition of the input list.
    :rtype: List[List[List[int]] | List[str]]


.. function:: non_trivial_classes(kb1: KnuthBendixRewriteTrie, kb2: KnuthBendixRewriteTrie, **kwargs) -> List[List[Union[str, List[int]]]]:
   :no-index:

    Find the non-trivial classes of the quotient of one :any:`KnuthBendixRewriteTrie` instance in
    another.

    This function returns the classes with size at least :math:`2` in the
    normal forms of *kb1* in *kb2* (the greater congruence, with fewer
    classes). This function triggers a full enumeration of both *kb1* and
    *kb2*. Note that this function does **not** compute the normal forms of
    *kb1* and try to compute the partition of these induced by *kb2*, before
    filtering out the classes of size :math:`1`. In particular, it is possible
    to compute the non-trivial classes of *kb2* in *kb1* if there are only
    finitely many finite such classes, regardless of whether or not *kb1* or
    *kb2* has infinitely many classes. The type of the output words is
    specified by the keyword argument *Word*.

   :param kb1: the first :any:`KnuthBendixRewriteTrie` instance.
   :type kb1: KnuthBendixRewriteTrie

   :param kb2: the second :any:`KnuthBendixRewriteTrie` instance.
   :type kb2: KnuthBendixRewriteTrie | List[str | List[int]]

   :Keyword Arguments:
       * *Word* (``type``) -- type of the output words (must be not present or ``str`` or ``List[int]``).

   :returns: The non-trivial classes of *kb1* in *kb2*.
   :rtype: List[List[str | List[int]]]

   :raises LibsemigroupsError:
       if *kb2* has infinitely many classes and *kb1* has finitely many
       classes (so that there is at least one infinite non-trivial class).

   :raises LibsemigroupsError:
       if the alphabets of the presentations of *kb1* and *kb2* are not equal.

   :raises LibsemigroupsError:
       if the :any:`KnuthBendixRewriteTrie.gilman_graph` of *kb2* has fewer nodes
       than that of *kb1*.

   :raises TypeError:
       if the keyword argument *Word* is not present, any other keyword
       argument is present, or is present but has value other than ``str`` or
       ``List[int]``.

   .. doctest::

       >>> from libsemigroups_pybind11 import (knuth_bendix, presentation,
       ... Presentation, congruence_kind, KnuthBendix)
       >>> from typing import List
       >>> p = Presentation("abc")
       >>> p.rules = ["ab", "ba", "ac", "ca", "aa", "a", "ac", "a", "ca",
       ... "a", "bc", "cb", "bbb", "b", "bc", "b", "cb", "b"]
       >>> kb1 = KnuthBendix(congruence_kind.twosided, p)
       >>> presentation.add_rule(p, "a", "b")
       >>> kb2 = KnuthBendix(congruence_kind.twosided, p)
       >>> knuth_bendix.non_trivial_classes(kb1, kb2, Word=str)
       [['b', 'ab', 'bb', 'abb', 'a']]
       >>> knuth_bendix.non_trivial_classes(kb1, kb2, Word=List[int])
       [[[98], [97, 98], [98, 98], [97, 98, 98], [97]]]
       >>> p = Presentation([0, 1, 2])
       >>> p.rules = [[0, 1], [1, 0], [0, 2], [2, 0], [0, 0], [0], [0, 2], [0], [2, 0],
       ... [0], [1, 2], [2, 1], [1, 1, 1], [1], [1, 2], [1], [2, 1], [1]]
       >>> kb1 = KnuthBendix(congruence_kind.twosided, p)
       >>> presentation.add_rule(p, [0], [1])
       >>> kb2 = KnuthBendix(congruence_kind.twosided, p)
       >>> knuth_bendix.non_trivial_classes(kb1, kb2, Word=List[int])
       [[[1], [0, 1], [1, 1], [0, 1, 1], [0]]]
