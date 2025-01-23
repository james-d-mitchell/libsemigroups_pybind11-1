//
// libsemigroups_pybind11
// Copyright (C) 2025 James Mitchell
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
#include <libsemigroups/todd-coxeter.hpp>

// pybind11....
#include <pybind11/chrono.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// libsemigroups_pybind11....
#include "cong-intf.hpp"  // for def_construct_default
#include "main.hpp"       // for init_todd_coxeter

namespace libsemigroups {
  namespace py = pybind11;
  using std::literals::operator""sv;

  namespace {
    template <typename Word>
    void bind_todd_coxeter(py::module& m, std::string const& name) {
      using ToddCoxeter_ = ToddCoxeter<Word>;

      py::class_<ToddCoxeter_, ToddCoxeterBase> thing(m,
                                                      name.c_str(),
                                                      R"pbdoc(
TODO(0)
)pbdoc");

      // __repr__ is implemented in ToddCoxeterBase

      ////////////////////////////////////////////////////////////////////////

      def_construct_default(thing, name);
      def_init_default(thing, name);
      def_construct_kind_presentation(thing, name);
      def_init_kind_presentation(thing, name);
      def_copy(thing, name);
      // number_of_classes is implemented in ToddCoxeterBase
      def_add_generating_pair(thing, name);
      def_currently_contains(thing, name);
      def_contains(thing, name);
      def_reduce_no_run(thing,
                        name,
                        doc{.detail = fmt::format(R"pbdoc(
If the :any:`{}` instance is not :any:`Runner.finished`,
then it might be that equivalent input words produce different output
words. This function triggers no congruence enumeration.)pbdoc",
                                                  name)
                                          .c_str()});
      def_reduce(thing, name);
      def_generating_pairs(thing, name);
      // TODO(0) make the next function a def_presentation function
      thing.def("presentation",
                &ToddCoxeter_::presentation,
                R"pbdoc(
Get the presentation used to define a ToddCoxeter instance (if any). If
a :any:`ToddCoxeter` instance is constructed or initialised using a
presentation, then a const reference to the
:any:`native_presentation_type` version of this presentation is returned
by this function.If the :any:`ToddCoxeter` instance was constructed
or initialised from a :any:`WordGraph` , then this presentation will be
empty.

:exceptions:
   This function is ``noexcept`` and is guaranteed never to throw.

:returns:
   A const reference to the presentation.

:rtype:
   Presentation
)pbdoc");

      ////////////////////////////////////////////////////////////////////////

      thing.def(py::init<congruence_kind, ToddCoxeter_ const&>(), R"pbdoc(
)pbdoc");

      thing.def(py::init<congruence_kind, WordGraph<uint32_t> const&>(),
                R"pbdoc(
)pbdoc");

      thing.def(
          "init",
          [](ToddCoxeter_&              self,
             congruence_kind            knd,
             WordGraph<uint32_t> const& wg) { return self.init(knd, wg); },
          py::arg("knd"),
          py::arg("wg"),
          R"pbdoc(
)pbdoc");

      thing.def(
          "_current_index_of",
          [](ToddCoxeter_ const& self, Word const& w) {
            return todd_coxeter::current_index_of(self, w);
          },
          py::arg("w"),
          R"pbdoc(
:sig=(self: ToddCoxeterWord, w: List[int] | str) -> int:

Returns the current index of the class containing a word.

This function returns the current index of the class containing the word
*w* No enumeration is triggered by calls to this function. Unless
:any:`Runner.finished` returns ``True``, the index returned by this
function is essentially arbitrary, and can only really be used to check
whether or not two words are currently known to belong to the congruence.
The returned index is obtained by following the path in
:any:`current_word_graph` from node ``0`` labelled by the word *w*. If
there is no such path, then :any:`UNDEFINED` is returned.

:param w: the word.
:type w: List[int] | str

:returns: The current index of the class containing the word.
:rtype: int | Undefined

:raises LibsemigroupsError:
  if any of the values in *w* is out of range, i.e. they do not belong to
  ``presentation().alphabet()`` and ``PresentationStrings.validate_word``
  raises.
    )pbdoc");

      thing.def(
          "index_of",
          [](ToddCoxeter_& self, Word const& w) {
            return todd_coxeter::index_of(self, w);
          },
          py::arg("w"),
          R"pbdoc(
:sig=(self: ToddCoxeter, w: List[int] | str) -> int:
:only-document-once:

Returns the index of the class containing a word.

This function returns the index of the class containing the word *w* A
full enumeration is triggered by calls to this function. If the
:any:`current_word_graph` has not already been standardized, then this
function first standardizes it with respect to :any:`Order.shortlex`;
otherwise the existing standardization order is used. The returned index
is obtained by following the path in :any:`current_word_graph` from node
``0`` labelled by the word *w* Since a full enumeration is triggered by
calls to this function, the word graph is complete, and so the return
value is never :any:`UNDEFINED`.

:param w: the word.
:type w: List[int] | str

:returns: The index of the class containing the word.
:rtype: int

:raises LibsemigroupsError:
    if any of the values in *w*, i.e. they do not belong to
    ``presentation().alphabet()`` and
    ``PresentationStrings.validate_word`` raises.
)pbdoc");

      thing.def(
          "current_word_of",
          [](ToddCoxeter_& self, size_t i) {
            return todd_coxeter::current_word_of(self, i);
          },
          R"pbdoc(
:sig=(i: int) -> List[int] | str:
Returns a current word representing a class with given index.

This function returns the current word representing the class with index *i*.
No enumeration is triggered by calls to this function, but
:any:`current_word_graph` is standardized (using :any:`Order.shortlex`) if it
is not already standardized. The output word is obtained by following a path in
:any:`current_spanning_tree` from the node corresponding to index *i* back to
the root of that tree.

:param i: the index of the class.
:type i: int

:returns: The word representing the *i*-th class.
:rtype: List[int] | str

:raises LibsemigroupsError:  if *i* is out of bounds.

:raises TypeError:
    if the keyword argument *Word* is not present, any other keyword
    argument is present, or is present but has value other than ``str`` or
    ``List[int]``.
)pbdoc");

      thing.def(
          "word_of",
          [](ToddCoxeter_& self, size_t i) {
            return todd_coxeter::word_of(self, i);
          },
          py::arg("i"),
          R"pbdoc(
Returns a word representing a class with given index.

This function returns the word representing the class with index *i*. A
full enumeration is triggered by calls to this function. The output word
is obtained by following a path in :any:`current_spanning_tree` from the
node corresponding to index *i* back to the root of that tree.

:returns: The word representing the *i*-th class.
:rtype: List[int]

:param i: the index of the class.
:type i: int

:raises LibsemigroupsError:  if *i* is out of bounds.
)pbdoc");

      ////////////////////////////////////////////////////////////////////////
      // Helper functions - available for all CongruenceInterface types
      ////////////////////////////////////////////////////////////////////////

      auto raises = R"pbdoc(
    :raises LibsemigroupsError:
      if the number of classes in *tc* is infinite. In this case, the
      enumeration of *tc* will not terminate successfully.)pbdoc"sv;

      def_partition<ToddCoxeter<Word>>(
          m, "todd_coxeter", doc{.raises = raises, .var = "tc"});
      def_non_trivial_classes<ToddCoxeter<Word>>(
          m, "todd_coxeter", doc{.raises = raises, .var = "tc"});

      // TODO(0) move this to cong-intf.*pp
      m.def("todd_coxeter_normal_forms", [](ToddCoxeter_& tc) {
        auto nf = todd_coxeter::normal_forms(tc);
        return py::make_iterator(rx::begin(nf), rx::end(nf));
      });

      ////////////////////////////////////////////////////////////////////////
      // Helper functions - specific to ToddCoxeter
      ////////////////////////////////////////////////////////////////////////

      m.def(
          "todd_coxeter_redundant_rule",
          [](Presentation<word_type> const& p, std::chrono::milliseconds t)
              -> std::optional<std::pair<word_type, word_type>> {
            auto it = todd_coxeter::redundant_rule(p, t);
            if (it != p.rules.cend()) {
              return std::make_pair(*it, *(it + 1));
            }
            return {};
          },
          py::arg("p"),
          py::arg("t"),
          R"pbdoc(
:sig=(p: PresentationStrings, t: timedelta) -> Tuple[List[int], List[int]] | Tuple[str, str] | None:
:only-document-once:

Return a redundant rule or ``None``.

Starting with the last rule in the presentation, this function attempts to
run the Todd-Coxeter algorithm on the rules of the presentation except for a
given omitted rule. For every such omitted rule, Todd-Coxeter is run for the
length of time indicated by the second parameter *t*, and then it is checked
if the omitted rule can be shown to be redundant. If the omitted rule can be
shown to be redundant in this way, then this rule is returned If no rule can
be shown to be redundant in this way, then ``None`` is returned.

:param p: the presentation.
:type p: PresentationStrings

:param t: time to run Todd-Coxeter for every omitted rule.
:type t: timedelta

:returns: A redundant rule or ``None``.
:rtype: Tuple[List[int], List[int]] | Tuple[str, str] | None
)pbdoc");

      m.def(
          "todd_coxeter_redundant_rule",
          [](Presentation<std::string> const& p, std::chrono::milliseconds t)
              -> std::optional<std::pair<std::string, std::string>> {
            auto it = todd_coxeter::redundant_rule(p, t);
            if (it != p.rules.cend()) {
              return std::make_pair(*it, *(it + 1));
            }
            return {};
          },
          R"pbdoc(
:sig=(p: PresentationStrings, t: timedelta) -> Tuple[List[int], List[int]] | Tuple[str, str] | None:
:only-document-once:
)pbdoc");

      m.def(
          "class_by_index",
          [](ToddCoxeter<Word>& tc, size_t n) {
            auto c = todd_coxeter::class_by_index(tc, n);
            // is this ok, does c somehow get copied into the iterator?
            return py::make_iterator(rx::begin(c), rx::end(c));
          },
          py::arg("tc"),
          py::arg("n"),
          R"pbdoc(
Returns an iterator yielding every word ``List[int]`` or ``str`` in the
congruence class with given index.

This function returns an iterator yielding every word belonging to the
class with index *n* in the congruence represented by the :any:`ToddCoxeter`
instance *tc*. Calls to this function trigger a full enumeration of *tc*.

:param tc: the ToddCoxeter instance.
:type tc: ToddCoxeter

:param n: the index of the class.
:type n: int

:Keyword Arguments:
    * *Word* (``type``) -- type of the output words (must be ``str`` or ``List[int]``).

:returns: A iterator yielding the class with index *n*.
:rtype: Iterator[List[int]]

:raises LibsemigroupsError:
    if *n* is greater than or equal to ``tc.number_of_classes()``.

:raises TypeError:
    if the keyword argument *Word* is not present, any other keyword
    argument is present, or is present but has value other than ``str`` or
    ``List[int]``.
)pbdoc");

      m.def(
          "class_of",
          [](ToddCoxeter<Word>& tc, Word const& w) {
            auto c = todd_coxeter::class_of(tc, w);
            // is this ok, does c somehow get copied into the iterator?
            return py::make_iterator(rx::begin(c), rx::end(c));
          },
          py::arg("tc"),
          py::arg("w"),
          R"pbdoc(
:sig=(tc: ToddCoxeter, w: List[int] | str) -> Iterator[List[int] | str]:
:only-document-once:

Returns an iterator yielding every word (of the same type as *w*) in
the congruence class of the given word *w*.

This function returns an iterator yielding every word in belonging to
the same class as the input word *w* in the congruence represented by the
:any:`ToddCoxeter` instance *tc*. Calls to this function trigger a
full enumeration of *tc*.

:param tc: the ToddCoxeter instance.
:type tc: ToddCoxeter

:param w: the input word.
:type w: List[int] | str

:returns: An iterator yielding words in the class of the input word.
:rtype: Iterator[List[int] | str]

:raises LibsemigroupsError:
  if any of the values in *w* is out of range, i.e. they do not belong to
  ``presentation().alphabet()`` and ``PresentationStrings.validate_word``
  raises.)pbdoc");

      m.def("todd_coxeter_is_non_trivial",
            &todd_coxeter::is_non_trivial,
            py::arg("tc"),
            py::arg("tries")     = 10,
            py::arg("try_for")   = std::chrono::milliseconds(100),
            py::arg("threshold") = 0.99,
            R"pbdoc(
:sig=(tc: ToddCoxeterBase, tries: int, try_for: timedelta, threshold: float) -> tril:

Check if the congruence has more than one class.

Returns :any:`tril.true` if it is possible to show that the congruence
is non-trivial; :any:`tril.false` if the congruence is already known to
be trivial; and :any:`tril.unknown` if it is not possible to show that
the congruence is non-trivial. This function attempts to find a
non-trivial congruence containing the congruence represented by a
:any:`ToddCoxeterBase` instance.

:param tc: the ToddCoxeterBase instance.
:type tc: ToddCoxeterBase

:param tries:
   the number of attempts to find a non-trivial super-congruence
   (default: ``10``).
:type tries: int

:param try_for:
   the amount of time to enumerate the congruence after choosing a random pair
   of representatives and identifying them (default: 100 milliseconds).

:type try_for: datetime.timedelta

:param threshold: the threshold (default: ``0.99``).
:type threshold: float

:returns: Whether or not a non-trivial quotient was found.
:rtype: tril
 )pbdoc");

    }  // bind_todd_coxeter
  }  // namespace

  void init_todd_coxeter(py::module& m) {
    bind_todd_coxeter<word_type>(m, "ToddCoxeterWord");
    bind_todd_coxeter<std::string>(m, "ToddCoxeterString");
  }

}  // namespace libsemigroups
