.. Copyright (c) 2022, J. D. Mitchell

   Distributed under the terms of the GPL license version 3.

   The full license is in the file LICENSE, distributed with this software.

Presentation helpers
====================

This page contains the documentation for various helper functions for
manipulating ``Presentation`` objects. All such functions are contained in the
submodule ``libsemigroups_pybind11.presentation``.

Contents
--------

.. list-table::
   :widths: 50 50
   :header-rows: 0

   * - :py:func:`redundant_rule`
     - Returns the index of the left hand side of a redundant rule.

   * - :py:func:`add_rule`
     - Add a rule to the presentation

Full API
--------

.. py:function:: redundant_rule(p: Presentation, t: datetime.timedelta) -> int

  Return the index of the the left hand side of a redundant rule.

  Starting with the last rule in the presentation, this function attempts to
  run the Knuth-Bendix algorithm on the rules of the presentation except for
  the given omitted rule. For every such omitted rule, Knuth-Bendix is run for
  the length of time indicated by the second parameter ``t`` and then it is
  checked if the omitted rule can be shown to be redundant (rewriting both
  sides of the omitted rule using the other rules using the output of the, not
  necessarily finished, Knuth-Bendix algorithm).

  If the omitted rule can be shown to be redundant in this way, then the index
  of its left hand side is returned.

  If no rule can be shown to be redundant in this way, then ``len(p.rules)``
  is returned.

  :warning:
    The progress of the Knuth-Bendix algorithm may differ between different
    calls to this function even if the parameters are identical. As such this
    is non-deterministic, and may produce different results with the same
    input.

  :param p: the presentation.
  :type p: Presentation
  :param t: time to run KnuthBendix for every omitted rule
  :type t: datetime.timedelta

  :return: The index of a redundant rule (if any).
 

.. py:function:: add_rule(p: Presentation, lhop: Union[str, List[int]], rhop: Union[str, List[int]]) -> None

   Add a rule to the presentation.
   
   Adds the rule with left hand side ``lhop`` and right hand side ``rhop``
   to the rules.
   
   :param p: the presentation
   :type p: Presentation
   :param lhop: the left hand side of the rule
   :type lhop: str or List[int]
   :param rhop: the right hand side of the rule
   :type rhop: str or List[int]
   
   :returns: None
   
   :warning:
     No checks that the arguments describe words over the alphabet of the
     presentation are performed.
