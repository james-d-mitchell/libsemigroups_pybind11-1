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

// libsemigroups headers
#include <libsemigroups/cong.hpp>

// pybind11....
// #include <pybind11/chrono.h>
// #include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// libsemigroups_pybind11....
#include "cong-intf.hpp"  // for contains etc
#include "cong.hpp"       // for non_trivial_classes etc
#include "main.hpp"       // for init_congruence

namespace py = pybind11;

namespace libsemigroups {
  namespace {

    template <typename Word>
    void def_non_trivial_classes_present(py::module& m) {
      m.def("congruence_non_trivial_classes",
            [](Congruence& thing, Presentation<Word> const& p) {
              return congruence::non_trivial_classes(thing, p);
            });
    }

  }  // namespace

  ////////////////////////////////////////////////////////////////////////
  // init_congruence
  ////////////////////////////////////////////////////////////////////////

  void init_cong(py::module& m) {
    py::class_<Congruence, CongruenceInterface> thing(m,
                                                      "Congruence",
                                                      R"pbdoc(
Class for running :any:`Kambites`, :any:`KnuthBendixRewriteTrie`, and
:any:`ToddCoxeter` in parallel.

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

    TODO(0)
 )pbdoc");

    ////////////////////////////////////////////////////////////////////////
    // Methods from cong-intf.hpp . . .
    ////////////////////////////////////////////////////////////////////////

    def_construct_default(thing, "Congruence");

    def_init_default(thing, "Congruence");

    def_construct_kind_presentation<word_type>(thing, "Congruence");
    def_construct_kind_presentation<std::string>(thing, "Congruence");

    def_init_kind_presentation<word_type>(thing, "Congruence");
    def_init_kind_presentation<std::string>(thing, "Congruence");

    def_copy(thing, "Congruence");

    def_add_generating_pair<word_type>(thing, "Congruence");
    def_add_generating_pair<std::string>(thing, "Congruence");

    def_currently_contains<word_type>(thing, "Congruence");
    def_currently_contains<std::string>(thing, "Congruence");

    def_contains<word_type>(thing, "Congruence");
    def_contains<std::string>(thing, "Congruence");

    def_reduce_no_run<word_type>(thing, "Congruence");
    def_reduce_no_run<std::string>(thing, "Congruence");

    def_reduce<word_type>(thing, "Congruence");
    def_reduce<std::string>(thing, "Congruence");

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

:returns:  ``self``.
:rtype: Congruence
)pbdoc");

    thing.def(
        "init",
        [](Congruence&                self,
           congruence_kind            knd,
           FroidurePinBase&           S,
           WordGraph<uint32_t> const& wg) -> Congruence& {
          return self.init(knd, S, wg);
        },
        py::arg("knd"),
        py::arg("S"),
        py::arg("wg"),
        R"pbdoc(
Re-initialize from :any:`congruence_kind`, :any:`FroidurePin`, and
:any:`WordGraph`.

This function re-initializes a :any:`Congruence` instance as if it had been
newly constructed over the :any:`FroidurePin` instance *S* representing a 1-
or 2-sided congruence according to *knd*.

:param knd: the kind (onesided or twosided) of the congruence.
:type knd: congruence_kind

:param S:
  a reference to the FroidurePin over which the congruence is being
  defined.
:type S: FroidurePinBase

:param wg: the left or right Cayley graph of S.
:type wg: WordGraph

:returns:  ``self``.
:rtype: Congruence
)pbdoc");

    thing.def(
        "max_threads",
        [](Congruence& self, size_t val) -> Congruence& {
          return self.max_threads(val);
        },
        py::arg("val"),
        R"pbdoc(
Set the maximum number of threads.

:param val: the number of threads.
:type val: int

:returns: ``self``.
:rtype: Congruence
)pbdoc");

    thing.def(
        "_max_threads",
        [](Congruence const& self) { return self.max_threads(); },
        R"pbdoc(
Get the current maximum number of threads.

:returns: The current maximum number of threads.
:rtype: int
    )pbdoc");

    // TODO(0) move to cong-intf.hpp
    thing.def("_number_of_classes",
              &Congruence::number_of_classes,
              R"pbdoc(
:sig=(self: Congruence) -> int | PositiveInfinity:

Compute the number of classes in the congruence. This function computes
the number of classes in the congruence represented by a
:any:`Congruence` instance.

:returns:
   The number of congruences classes of a :any:`Congruence` instance if
   this number is finite, or :any:`POSITIVE_INFINITY` in some cases if
   this number is not finite.
:rtype:
   int | PositiveInfinity
)pbdoc");

    thing.def("number_of_runners",
              &Congruence::number_of_runners,
              R"pbdoc(
Get the number of runners. This function returns the number of distinct
:any:`CongruenceInterface` instances that are contained in a
:any:`Congruence` object.

:returns:
   The number of runners.
:rtype:
   int
)pbdoc");

    thing.def("presentation",
              &Congruence::presentation,
              R"pbdoc(
:sig=(self: Congruence) -> PresentationStrings:

Get the presentation defining the parent semigroup of the congruence.
This function returns the presentation used to construct a
:any:`Congruence` object. This is not always possible.

:returns:
   The presentation.
:rtype:
   PresentationStrings

:raises LibsemigroupsError:
   if :any:`Runner.finished` returns ``True`` and ``has(KnuthBendix)`` returns
   ``True``.

:raises LibsemigroupsError:
   if no :any:`PresentationStrings` was used to construct or initialise ``self``.
)pbdoc");

    // Return by value on purpose, to avoid complications with "get" being
    // called before "run" and the obtained object being deleted.
    // Might be better to return a shared_ptr but then KnuthBendix must be
    // stored as shared_ptr, and then everything above KnuthBendix in the class
    // hierarchy, and then possibly everything below Reporter too which is then
    // basically everything.
    thing.def("_get_knuth_bendix", [](Congruence const& self) {
      return *self.get<KnuthBendix<>>();
    });

    // Return by value on purpose, to avoid complications with "get" being
    // called before "run" and the obtained object being deleted.
    // Might be better to return a shared_ptr but then KnuthBendix must be
    // stored as shared_ptr, and then everything above KnuthBendix in the class
    // hierarchy, and then possibly everything below Reporter too which is then
    // basically everything.
    thing.def("_get_todd_coxeter",
              [](Congruence const& self) { return *self.get<ToddCoxeter>(); });

    // Return by value on purpose, to avoid complications with "get" being
    // called before "run" and the obtained object being deleted.
    // Might be better to return a shared_ptr but then KnuthBendix must be
    // stored as shared_ptr, and then everything above KnuthBendix in the class
    // hierarchy, and then possibly everything below Reporter too which is then
    // basically everything.
    // TODO(0) this won't currently work as we don't wrap Kambites<word_type>
    // ATM
    thing.def("_get_kambites", [](Congruence const& self) {
      return *self.get<Kambites<word_type>>();
    });

    thing.def("_has_knuth_bendix", [](Congruence const& self) {
      return self.has<KnuthBendix<detail::RewriteTrie>>();
    });

    thing.def("_has_todd_coxeter",
              [](Congruence const& self) { return self.has<ToddCoxeter>(); });

    thing.def("_has_kambites", [](Congruence const& self) {
      return self.has<Kambites<word_type>>();
    });

    // TODO(0) add the doc from these
    /*
      thing.def("has",
                &Congruence::has,
                R"pbdoc(
      )pbdoc");
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
      */

    ////////////////////////////////////////////////////////////////////////
    // Helpers from cong-intf.hpp . . .
    ////////////////////////////////////////////////////////////////////////

    def_non_trivial_classes<word_type, Congruence>(m, "Congruence");
    def_non_trivial_classes<std::string, Congruence>(m, "Congruence");

    ////////////////////////////////////////////////////////////////////////
    // Helpers specific to Congruence . . .
    ////////////////////////////////////////////////////////////////////////

    def_non_trivial_classes_present<word_type>(m);
    def_non_trivial_classes_present<std::string>(m);

  }  // init_cong

}  // namespace libsemigroups
