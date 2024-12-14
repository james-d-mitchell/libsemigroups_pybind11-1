//
// libsemigroups_pybind11
// Copyright (C) 2024 James D. Mitchell
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

// C std headers....
// TODO complete or delete

// C++ stl headers....
// TODO complete or delete

// libsemigroups headers
#include <libsemigroups/cong.hpp>

// pybind11....
// #include <pybind11/chrono.h>
// #include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// TODO uncomment/delete

// libsemigroups_pybind11....
#include "cong-intf.hpp"  // for contains etc
#include "main.hpp"       // for init_congruence

namespace py = pybind11;

namespace libsemigroups {

  ////////////////////////////////////////////////////////////////////////
  // init_congruence
  ////////////////////////////////////////////////////////////////////////

  void init_cong(py::module& m) {
    py::class_<Congruence, CongruenceInterface> thing(m,
                                                      "Congruence",
                                                      R"pbdoc(
Class for running :any:`Kambites`, :any:`KnuthBendix`, and :any:`ToddCoxeter`
in parallel.

On this page we describe the functionality relating to the class
:any:`Congruence` in ``libsemigroups``. This class can be used for computing a
congruence over a semigroup or monoid by running every applicable algorithm
from ``libsemigroups`` (and some variants of the same algorithm) in parallel.
This class is provided for convenience, at present it is not very customisable,
and lacks some of the fine grained control offered by the classes implementing
individual algorithms, such as :any:`Kambites`, :any:`KnuthBendixRewriteTrie`,
and :any:`ToddCoxeter`.

.. seealso::  :any:`congruence_kind` and :any:`tril`.

.. doctest::

 )pbdoc");

    ////////////////////////////////////////////////////////////////////////
    // Things from cong-intf.hpp . . .
    ////////////////////////////////////////////////////////////////////////

    constructor<word_type>(thing, "Congruence");
    constructor<std::string>(thing, "Congruence");

    init_from_kind_presentation<word_type>(thing, "Congruence");
    init_from_kind_presentation<std::string>(thing, "Congruence");

    currently_contains<std::string>(thing, "Congruence");
    currently_contains<word_type>(thing, "Congruence");

    contains<std::string>(thing, "Congruence");
    contains<word_type>(thing, "Congruence");

    // TODO(0) uncomment (not yet impled in Congruence)
    // reduce_no_run<std::string>(thing, "Congruence");
    // reduce_no_run<word_type>(thing, "Congruence");

    // TODO(0) uncomment (not yet impled in Congruence)
    // reduce<std::string>(thing, "Congruence");
    // reduce<word_type>(thing, "Congruence");

    ////////////////////////////////////////////////////////////////////////
    // TODO
    ////////////////////////////////////////////////////////////////////////

    thing.def(py::init<>(), R"pbdoc(
Default constructor. This function default constructs an uninitialised
:any:`Congruence` instance.
)pbdoc");
    // TODO(0) copy
    //     thing.def(py::init<Congruence const&>(), R"pbdoc(
    // Copy constructor.
    // )pbdoc");
    //

    ////////////////////////////////////////////////////////////////////////
    // Congruence specific stuff
    ////////////////////////////////////////////////////////////////////////

    thing.def("__repr__", [](Congruence const& thing) {
      return to_human_readable_repr(thing);
    });

    thing.def(py::init<congruence_kind,
                       FroidurePinBase&,
                       WordGraph<uint32_t> const&>(),
              R"pbdoc(
Construct from congruence_kind, FroidurePin, and WordGraph.

Constructs a :any:`Congruence` over the :any:`FroidurePin` instance *S*
representing a 1- or 2-sided congruence according to *knd*.

:param knd: the kind (onesided or twosided) of the congruence.
:type knd: congruence_kind

:param S: a reference to the FroidurePin over which the congruence is being defined.
:type S: FroidurePinBase

:param wg: the left or right Cayley graph of S.
:type wg: WordGraph
)pbdoc");

    /*
          thing.def("get",
                    &Congruence::get,
                    R"pbdoc(
    )pbdoc");
          thing.def("has",
                    &Congruence::has,
                    R"pbdoc(
    )pbdoc");
          thing.def(
              "init",
              [](Congruence& self) { return self.init(); },
              R"pbdoc(
    Re-initialize a Congruence instance. This function puts a
    :any:`Congruence` instance back into the state that it would have been
    in if it had just been newly default constructed.

    :exceptions:
       This function guarantees not to throw a :any:`LibsemigroupsError`.

    :returns:
       A reference to ``self``.

    :rtype:
       Congruence
    )pbdoc");
          thing.def(
              "init",
              [](Congruence&            self,
                 congruence_kind        knd,
                 FroidurePinBase&       S,
                 WordGraph<Node> const& wg) { return self.init(knd, S, wg); },
              py::arg("knd"),
              py::arg("S"),
              py::arg("wg"),
              R"pbdoc(
    )pbdoc");
          thing.def(
              "init",
              [](Congruence&               self,
                 congruence_kind           knd,
                 Presentation<Word> const& p) { return self.init(knd, p); },
              py::arg("knd"),
              py::arg("p"),
              R"pbdoc(
    )pbdoc");
          thing.def(
              "init",
              [](Congruence&                    self,
                 congruence_kind                knd,
                 Presentation<word_type> const& p) { return self.init(knd, p);
    }, py::arg("knd"), py::arg("p"), R"pbdoc( Re-initialize a Congruence
    instance.

    :param knd: the kind (onesided or twosided) of the congruence.
    :type knd: congruence_kind

    :param p: the presentation.
    :type p: Presentation
    This function puts a :any:`Congruence` instance back into the state that
    it would have been in if it had just been newly constructed from ``knd``
    and ``p``.

    :raises LibsemigroupsError:  if ``p`` is not valid.


    :returns: A reference to ``self``.

    :rtype: Congruence
    )pbdoc");
          thing.def(
              "max_threads",
              [](Congruence const& self) { return self.max_threads(); },
              R"pbdoc(
    Returns the :any:`KnuthBendix` instance used to compute the congruence (if
    any).

    :exceptions: This function guarantees not to throw a
    :any:`LibsemigroupsError`.

    :complexity: Constant.

    .. seealso::  has<KnuthBendix>. Checks if a :any:`KnuthBendix` instance is
    being used to compute the congruence.

    :exceptions: This function guarantees not to throw a
    :any:`LibsemigroupsError`.

    :complexity: Constant.

    .. seealso::  get<KnuthBendix>. Get the current maximum number of threads.

    :exceptions: This function is ``noexcept`` and is guaranteed never to
    throw.

    :complexity: Constant.

    :returns: A :any:`std::shared_ptr` to a :any:`KnuthBendix` or ``nullptr``.

    :rtype: int
    )pbdoc");
          thing.def(
              "max_threads",
              [](Congruence& self, size_t val) { return self.max_threads(val);
    }, py::arg("val"), R"pbdoc(

    :param val: the number of threads.
    :type val: int
    Set the maximum number of threads.

    :exceptions: This function is ``noexcept`` and is guaranteed never to
    throw.

    :complexity: Constant.


    :returns: A reference to ``self``.

    :rtype: Congruence
    )pbdoc");
          thing.def("number_of_classes",
                    &Congruence::number_of_classes,
                    R"pbdoc(
    )pbdoc");
          thing.def("number_of_runners",
                    &Congruence::number_of_runners,
                    R"pbdoc(
    )pbdoc");
          thing.def("throw_if_letter_out_of_bounds",
                    &Congruence::throw_if_letter_out_of_bounds,
                    py::arg("first"),
                    py::arg("last"),
                    R"pbdoc(
    )pbdoc");
    */

  }  // init_cong

}  // namespace libsemigroups
