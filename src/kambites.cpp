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
#include <libsemigroups/kambites.hpp>
#include <libsemigroups/to-froidure-pin.hpp>

// pybind11....
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// libsemigroups_pybind11....
#include "cong-intf.hpp"  // for contains etc
#include "main.hpp"       // for init_kambites

namespace py = pybind11;
using std::literals::operator""sv;

namespace libsemigroups {
  namespace {
    ////////////////////////////////////////////////////////////////////////
    // bind_kambites
    ////////////////////////////////////////////////////////////////////////

    template <typename Word>
    void bind_kambites(py::module& m, std::string const& name) {
      using Kambites_        = Kambites<Word>;
      using native_word_type = typename Kambites_::native_word_type;

      py::class_<Kambites_, CongruenceInterface> thing(m,
                                                       name.c_str(),
                                                       R"pbdoc(
Class template implementing small overlap class, equality, and normal forms for
small overlap monoids.

This page describes the class :any:`Kambites` for determining the
small overlap class of a presentation, and, for small overlap monoids (those
with small overlap class 4 or higher) checking equality of words and for
computing normal forms. Note that a :any:`Kambites` instance represents a
congruence on the free monoid or semigroup containing the rules of a
presentation used to construct the instance, and the :any:`generating_pairs`.
As such generating pairs or rules are interchangeable in the context of
:any:`Kambites` objects.)pbdoc");

      ////////////////////////////////////////////////////////////////////////
      // Things from cong-intf.hpp . . .
      ////////////////////////////////////////////////////////////////////////

      def_construct_default(thing, "Kambites");

      def_init_default(thing, "Kambites");

      auto extra_detail
          = R"pbdoc(:any:`Kambites` instances can only be used to compute
two-sided congruences, and so the first parameter *knd* must always
be ``congruence_kind.twosided``. The parameter *knd* is included for
uniformity of interface between with :any:`KnuthBendixRewriteTrie`,
:any:`Kambites`, and :any:`Congruence`.)pbdoc"sv;

      auto extra_raises = R"pbdoc(
:raises LibsemigroupsError:
    if :any:`small_overlap_class` is not at least :math:`4`.
)pbdoc"sv;

      def_construct_kind_presentation<word_type>(
          thing,
          "Kambites",
          doc{.detail = extra_detail, .raises = extra_raises});
      def_construct_kind_presentation<native_word_type>(
          thing,
          "Kambites",
          doc{.detail = extra_detail, .raises = extra_raises});

      extra_raises = R"pbdoc(
:raises LibsemigroupsError: if *knd* is ``congruence_kind.onesided``.
)pbdoc"sv;

      def_init_kind_presentation<word_type>(
          thing, "Kambites", doc{.raises = extra_raises});
      def_init_kind_presentation<std::string>(
          thing, "Kambites", doc{.raises = extra_raises});

      def_copy(thing, "Kambites");

      def_add_generating_pair<word_type>(thing, "Kambites");
      def_add_generating_pair<std::string>(thing, "Kambites");

      extra_raises = R"pbdoc(
:raises LibsemigroupsError:
    if :any:`small_overlap_class` is known and not at least :math:`4`.
)pbdoc"sv;
      def_currently_contains<word_type>(
          thing, "Kambites", doc{.raises = extra_raises});
      def_currently_contains<std::string>(
          thing, "Kambites", doc{.raises = extra_raises});

      extra_raises = R"pbdoc(
:raises LibsemigroupsError:
    if :any:`small_overlap_class` is not at least :math:`4`.
)pbdoc"sv;

      def_contains<word_type>(thing, "Kambites", doc{.raises = extra_raises});
      def_contains<std::string>(thing, "Kambites", doc{.raises = extra_raises});

      extra_detail
          = R"pbdoc(If the :any:`Kambites.small_overlap_class` is not at least
:math:`4`, then an exception is thrown.)pbdoc"sv;

      def_reduce_no_run<word_type>(
          thing, "Kambites", doc{.detail = extra_detail});
      def_reduce_no_run<std::string>(
          thing, "Kambites", doc{.detail = extra_detail});

      def_reduce<word_type>(
          thing,
          "Kambites",
          doc{.detail = extra_detail, .raises = extra_raises});
      def_reduce<std::string>(
          thing,
          "Kambites",
          doc{.detail = extra_detail, .raises = extra_raises});

      extra_detail = R"pbdoc(This function computes the number of classes in
      the congruence represented by a :any:`Kambites` instance if the
      :any:`small_overlap_class` is at least :math:`4`. :any:`Kambites`
      instances can only compute the number of classes if the condition of the
      previous sentence is fulfilled, and in this case the number of classes is
      always :any:`POSITIVE_INFINITY`. Otherwise an exception is
      raised.)pbdoc"sv;

      def_number_of_classes(
          thing,
          "Kambites",
          doc{.detail = extra_detail, .raises = extra_raises});

      ////////////////////////////////////////////////////////////////////////
      // Kambites specific stuff
      ////////////////////////////////////////////////////////////////////////

      thing.def("__repr__",
                [](Kambites_& thing) { return to_human_readable_repr(thing); });

      thing.def("presentation",
                &Kambites_::presentation,
                R"pbdoc(
Get the presentation used to define a :any:`Kambites` instance (if any). If a
any:`Kambites` instance is constructed or initialised using a presentation,
then the version of this presentation used by the :any:`Kambites` object is
returned by this function.

:returns:
    The presentation.
:rtype:
    PresentationStrings
      )pbdoc");

      thing.def("_small_overlap_class",
                py::overload_cast<>(&Kambites_::small_overlap_class),
                R"pbdoc(
:sig=(self: Kambites) -> int | PositiveInfinity:

Get the small overlap class.

If :math:`S` is a finitely presented semigroup or monoid with generating set
:math:`A`, then a word :math:`w` over :math:`A` is a *piece* if
:math:`w` occurs as a factor in at least two of the relations defining
:math:`S` or if it occurs as a factor of one relation in two different
positions (possibly overlapping). A finitely presented semigroup
:math:`S` satisfies the condition :math:`C(n)`, for a positive integer
:math:`n` if the minimum number of pieces in any factorisation of a word
occurring as the left or right hand side of a relation of :math:`S` is
at least :math:`n`.

:complexity:
  The current implementation has complexity no worse than :math:`O(m ^ 3)`
  where :math:`m` is the sum of the lengths of the words occurring in the
  relations of the semigroup.

:returns:
  The greatest positive integer :math:`n` such that the finitely
  semigroup or monoid represented by ``self`` satisfies the condition
  :math:`C(n)` ; or :any:`POSITIVE_INFINITY` if no word occurring in a
  relation can be written as a product of pieces.
:rtype: int | PositiveInfinity
      )pbdoc");

      thing.def("ukkonen",
                &Kambites_::ukkonen,
                R"pbdoc(
Returns the generalised suffix tree used to compute pieces.

This function returns the generalised suffix tree :any:`Ukkonen` object
containing the relation words of a :any:`Kambites` object, that is used to
determine the pieces, and decompositions of the relation words.

:returns:
    The generalised suffix tree containing the relation words.
:rtype:
    Ukkonen
)pbdoc");

      ////////////////////////////////////////////////////////////////////////
      // Helpers from cong-intf.hpp . . .
      ////////////////////////////////////////////////////////////////////////

      extra_raises = R"pbdoc(
:raises LibsemigroupsError:
    if ``k.small_overlap_class()`` is not at least :math:`4`.
)pbdoc"sv;

      def_partition<word_type, Kambites_>(
          m, "Kambites", doc{.raises = extra_raises, .var = "k"});
      def_partition<std::string, Kambites_>(
          m, "Kambites", doc{.raises = extra_raises, .var = "k"});

      def_non_trivial_classes<word_type, Kambites_>(
          m, "Kambites", doc{.raises = extra_raises});
      def_non_trivial_classes<std::string, Kambites_>(
          m, "Kambites", doc{.raises = extra_raises});

      ////////////////////////////////////////////////////////////////////////
      // Kambites specific helpers . . .
      ////////////////////////////////////////////////////////////////////////
      // TODO(1) it is currently only possible to have the return type of the
      // next function to be List[int]
      m.def(
          "kambites_normal_forms",
          [](Kambites_& k) {
            auto nf = kambites::normal_forms(k);
            return py::make_iterator(rx::begin(nf), rx::end(nf));
          },
          py::arg("k"),
          R"pbdoc(
:sig=(k: Kambites) -> Iterator[List[int]]:

Returns an iterator yielding normal forms.

This function returns an iterator yielding short-lex normal forms of the
classes of the congruence represented by an instance of :any:`Kambites`.

:param k: the :any:`Kambites` instance.
:type k: Kambites

:returns: An iterator yielding normal forms.
:rtype: Iterator[List[int]]
)pbdoc");

    }  // bind_kambites
  }  // namespace

  void init_kambites(py::module& m) {
    // One call to bind is required per list of types
    bind_kambites<detail::MultiStringView>(m, "Kambites");
    bind_kambites<word_type>(m, "KambitesWordType");
  }

}  // namespace libsemigroups
