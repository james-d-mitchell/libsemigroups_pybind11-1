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

#include "cong-intf.hpp"  // for doc

#include <string_view>

// libsemigroups headers
#include <libsemigroups/cong-intf.hpp>
#include <libsemigroups/cong.hpp>
#include <libsemigroups/kambites.hpp>
#include <libsemigroups/knuth-bendix.hpp>
#include <libsemigroups/todd-coxeter.hpp>

// pybind11....
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// libsemigroups_pybind11....
#include "cong-intf-class.hpp"
#include "main.hpp"  // for init_cong_intf
#include "todd-coxeter-base.hpp"

namespace py = pybind11;
using namespace fmt::literals;

namespace libsemigroups {

  ////////////////////////////////////////////////////////////////////////
  // Implementation helpers
  ////////////////////////////////////////////////////////////////////////

  namespace {

    std::string add_prefix(std::string_view name, std::string_view suffix) {
      std::string func_name(name);
      std::transform(func_name.begin(),
                     func_name.end(),
                     func_name.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      func_name += suffix;
      return func_name;
    }

    // 100% thread unsafe!!
    char const* make_doc(char const*      fmt_string,
                         std::string_view name,
                         doc              extra_doc) {
      static std::string result;
      result.clear();

      fmt::format_to(std::back_inserter(result),
                     fmt_string,
                     "detail"_a             = extra_doc.detail,
                     "example"_a            = extra_doc.example,
                     "name"_a               = name,
                     "only_document_once"_a = extra_doc.only_document_once,
                     "raises"_a             = extra_doc.raises,
                     "var"_a                = extra_doc.var);
      return result.c_str();
    }
  }  // namespace

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_construct_default(py::class_<Thing, ThingBase>& thing,
                             std::string_view              name,
                             doc                           extra_doc) {
    thing.def(py::init<>(),
              make_doc(R"pbdoc(
:sig=() -> None:
{only_document_once}

Default constructor. This function default constructs an
uninitialised :any:`{name}` instance.

{detail}
)pbdoc",
                       name,
                       extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_construct_default<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_construct_default<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void
  def_construct_default<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_init_default(py::class_<Thing, ThingBase>& thing,
                        std::string_view              name,
                        doc                           extra_doc) {
    thing.def(
        "init",
        [](Thing& self) -> Thing& { return self.init(); },
        make_doc(R"pbdoc(
:sig=(self: {name}) -> {name}:
{only_document_once}

Re-initialize a :any:`{name}` instance.

This function puts a :any:`{name}` instance back into the state that it would
have been in if it had just been newly default constructed.

{detail}

:returns:
  ``self``.
:rtype:
    {name})pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_init_default<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_init_default<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void def_init_default<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_construct_kind_presentation(py::class_<Thing, ThingBase>& thing,
                                       std::string_view              name,
                                       doc extra_doc) {
    using Word = typename Thing::native_word_type;
    thing.def(py::init<congruence_kind, Presentation<Word> const&>(),
              py::arg("knd"),
              py::arg("p"),
              make_doc(R"pbdoc(
:sig=(self: {name}, knd: congruence_kind, p: PresentationStrings) -> None:
{only_document_once}

Construct from :any:`congruence_kind` and :any:`PresentationStrings`.

This function constructs a :any:`{name}` instance representing a congruence
of kind *knd* over the semigroup or monoid defined by the presentation *p*.

{detail}

:param knd: the kind (onesided or twosided) of the congruence.
:type knd: congruence_kind

:param p: the presentation.
:type p: PresentationStrings

:raises LibsemigroupsError: if *p* is not valid.

{raises}
)pbdoc",
                       name,
                       extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void
  def_construct_kind_presentation<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void
  def_construct_kind_presentation<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void
  def_construct_kind_presentation<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_init_kind_presentation(py::class_<Thing, ThingBase>& thing,
                                  std::string_view              name,
                                  doc                           extra_doc) {
    using Word = typename Thing::native_word_type;
    thing.def(
        "init",
        [](Thing&                    self,
           congruence_kind           knd,
           Presentation<Word> const& p) -> Thing& { return self.init(knd, p); },
        py::arg("knd"),
        py::arg("p"),
        // TODO(0) adding only-document-once here means that the other
        // overloads of init are suppressed also :(
        make_doc(R"pbdoc(
:sig=(self: {name}, knd: congruence_kind, p: PresentationStrings) -> {name}:
{only_document_once}

Re-initialize a :any:`{name}` instance.

This function re-initializes a :any:`{name}` instance as if it
had been newly constructed from *knd* and *p*.

{detail}

:param knd: the kind (onesided or twosided) of the congruence.
:type knd: :any:`congruence_kind`

:param p: the presentation.
:type p: PresentationStrings

:returns:  ``self``.
:rtype: {name}

:raises LibsemigroupsError: if *p* is not valid.

{raises}
)pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void
  def_init_kind_presentation<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void
  def_init_kind_presentation<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void
  def_init_kind_presentation<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_copy(py::class_<Thing, ThingBase>& thing,
                std::string_view              name,
                doc                           extra_doc) {
    thing.def(
        "copy",
        [](Thing const& self) { return Thing(self); },
        make_doc(R"pbdoc(
:sig=(self: {name}) -> {name}:
{only_document_once}

Copy a :any:`{name}` object.

{detail}

:returns: A copy.
:rtype: {name})pbdoc",
                 name,
                 extra_doc));

    thing.def("__copy__", [](Thing const& self) { return Thing(self); });
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_copy<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_copy<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void def_copy<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_number_of_classes(py::class_<Thing, ThingBase>& thing,
                             std::string_view              name,
                             doc                           extra_doc) {
    thing.def(
        "_number_of_classes",
        [](Thing& self) { return self.number_of_classes(); },
        make_doc(R"pbdoc(
:sig=(self: {name}) -> int | PositiveInfinity:
{only_document_once}

Compute the number of classes in the congruence. This function computes the
number of classes in the congruence represented by a :any:`{name}` instance.

{detail}

:returns:
   The number of congruence classes of a :any:`{name}` instance if this number
   is finite, or :any:`POSITIVE_INFINITY` in some cases if this number is not
   finite.
:rtype:
   int | PositiveInfinity

{raises}
)pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_number_of_classes<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  // Not required for ToddCoxeter<>

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_add_generating_pair(py::class_<Thing, ThingBase>& thing,
                               std::string_view              name,
                               doc                           extra_doc) {
    using Word = typename Thing::native_word_type;
    thing.def(
        "add_generating_pair",
        [](Thing& self, Word const& u, Word const& v) -> Thing& {
          return congruence_interface::add_generating_pair(self, u, v);
        },
        py::arg("u"),
        py::arg("v"),
        make_doc(
            R"pbdoc(
:sig=(self: {name}, u: List[int] | str, v: List[int] | str) -> {name}:
{only_document_once}

Add a generating pair.

This function adds a generating pair to the congruence represented by a
:any:`{name}` instance.

{detail}

:param u: the first item in the pair.
:type u: List[int] | str

:param v: the second item in the pair.
:type v: List[int] | str

:returns: ``self``.
:rtype: {name}

:raises LibsemigroupsError:
  if any of the values in *u* or *v* is out of range, i.e. they do not belong
  to ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

:raises LibsemigroupsError:  if :any:`Runner.started` returns ``True``.

{raises}
)pbdoc",
            name,
            extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_add_generating_pair<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void
  def_add_generating_pair<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void
  def_add_generating_pair<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_currently_contains(py::class_<Thing, ThingBase>& thing,
                              std::string_view              name,
                              doc                           extra_doc) {
    using Word = typename Thing::native_word_type;
    thing.def(
        "currently_contains",
        [](Thing const& self, Word const& u, Word const& v) {
          return congruence_interface::currently_contains(self, u, v);
        },
        py::arg("u"),
        py::arg("v"),
        make_doc(R"pbdoc(
:sig=(self: {name}, u: List[int] | str, v: List[int] | str) -> tril:
{only_document_once}

Check whether a pair of words is already known to belong to the congruence.

This function checks whether or not the words *u* and *v* are already known to
be contained in the congruence represented by a :py:class:`{name}` instance.
This function performs no enumeration, so it is possible for the words to be
contained in the congruence, but that this is not currently known.

:param u: the first word.
:type u: List[int] | str

:param v: the second word.
:type v: List[int] | str

:returns:
    *  :any:`tril.true` if the words are known to belong to the congruence;
    *  :any:`tril.false` if the words are known to not belong to the
       congruence;
    *  :any:`tril.unknown` otherwise.
:rtype: tril

:raises LibsemigroupsError:
  if any of the values in *u* or *v* is out of range, i.e. they do not belong
  to ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{raises}
)pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_currently_contains<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_currently_contains<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void
  def_currently_contains<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_contains(py::class_<Thing, ThingBase>& thing,
                    std::string_view              name,
                    doc                           extra_doc) {
    using Word = typename Thing::native_word_type;

    thing.def(
        "contains",
        [](Thing& self, Word const& u, Word const& v) {
          return congruence_interface::contains(self, u, v);
        },
        py::arg("u"),
        py::arg("v"),
        make_doc(R"pbdoc(
:sig=(self: {name}, u: List[int] | str, v: List[int] | str) -> bool:
{only_document_once}

Check containment of a pair of words.

This function checks whether or not the words *u* and *v* are contained in the
congruence represented by a :py:class:`{name}` instance.

:param u: the first word.
:type u: List[int] | str

:param v: the second word.
:type v: List[int] | str

:returns: Whether or not the pair belongs to the congruence.
:rtype: bool

:raises LibsemigroupsError:
  if any of the values in *u* or *v* is out of range, i.e. they do not belong
  to ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{raises}
)pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_contains<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_contains<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void def_contains<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_reduce_no_run(py::class_<Thing, ThingBase>& thing,
                         std::string_view              name,
                         doc                           extra_doc) {
    using Word = typename Thing::native_word_type;
    thing.def(
        "reduce_no_run",
        [](Thing& self, Word const& w) {
          return congruence_interface::reduce_no_run(self, w);
        },
        py::arg("w"),
        make_doc(R"pbdoc(
:sig=(self: {name}, w: List[int] | str) -> List[int] | str:
{only_document_once}

Reduce a word.

If :any:`Runner.finished` returns ``True``, then this function returns a
normal form for the input word *w*.

{detail}

:param w: the input word.
:type w: List[int] | str

:returns: A word equivalent to the input word.
:rtype: List[int] | str

:raises LibsemigroupsError:
  if any of the values in *w* is out of range, i.e. they do not belong to
  ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{raises})pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_reduce_no_run<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_reduce_no_run<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void def_reduce_no_run<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_reduce(py::class_<Thing, ThingBase>& thing,
                  std::string_view              name,
                  doc                           extra_doc) {
    using Word = typename Thing::native_word_type;
    thing.def(
        "reduce",
        [](Thing& self, Word const& w) {
          return congruence_interface::reduce(self, w);
        },
        py::arg("w"),
        make_doc(R"pbdoc(
:sig=(self: {name}, w: List[int] | str) -> List[int] | str:
{only_document_once}

Reduce a word.

This function triggers a full enumeration of an :py:class:`{name}` object and
then reduces the word *w*. As such the returned word is a normal form for the
input word.

{detail}

:param w: the input word.
:type w: List[int] | str

:returns: A normal form for the input word.
:rtype: List[int] | str

:raises LibsemigroupsError:
  if any of the values in *w* is out of range, i.e. they do not belong to
  ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{raises}
)pbdoc",
                 name,
                 extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void def_reduce<ToddCoxeterBase, CongruenceInterface>(
      py::class_<ToddCoxeterBase, CongruenceInterface>&,
      std::string_view,
      doc);

  template void def_reduce<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void def_reduce<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing, typename ThingBase>
  void def_generating_pairs(py::class_<Thing, ThingBase>& thing,
                            std::string_view              name,
                            doc                           extra_doc) {
    thing.def("generating_pairs",
              &Thing::generating_pairs,
              make_doc(
                  R"pbdoc(
:sig=(self : {name}) -> List[List[int] | str]:
{only_document_once}

Get the generating pairs of the congruence.

This function returns the generating pairs of the congruence. The words
comprising the generating pairs are converted to the internally used type
(called the *native word type* and usually either :any:`str` or
``List[int]``) as they are added via :any:`{name}.add_generating_pair`. This
function returns the :any:`list` of these native word types.

:returns:
   The list of generating pairs.
:rtype:
   List[List[int] | str]
  )pbdoc",
                  name,
                  extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  // Not required for ToddCoxeterBase, it's called internal_generating_pairs

  template void def_generating_pairs<ToddCoxeter<word_type>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<word_type>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  template void def_generating_pairs<ToddCoxeter<std::string>, ToddCoxeterBase>(
      py::class_<ToddCoxeter<std::string>, ToddCoxeterBase>&,
      std::string_view,
      doc);

  ////////////////////////////////////////////////////////////////////////
  // Helpers
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing>
  void def_non_trivial_classes(py::module&      m,
                               std::string_view name,
                               doc              extra_doc) {
    using Word            = typename Thing::native_word_type;
    std::string func_name = add_prefix(name, "_non_trivial_classes");
    m.def(
        func_name.c_str(),
        [](Thing& ci, std::vector<Word> const& words) {
          return congruence_interface::non_trivial_classes(
              ci, rx::iterator_range(words.begin(), words.end()));
        },
        py::arg("ci"),
        py::arg("words"),
        // TODO(1) use doc.var instead of using ci here
        make_doc(
            R"pbdoc(
:sig=(ci: {name}, words: List[List[int] | str]) -> List[List[List[int]] | List[str]]:
{only_document_once}

Find the non-trivial classes in the partition of a list of words.

This function returns the classes with size at least :math:`2` in the
partition of the words in the list *words* induced by the :any:`{name}`
instance *ci*.

{detail}

:param ci: the :any:`{name}` instance.
:type ci: {name}

:param words: the input list of words.
:type words: List[List[int] | str]

:returns: The partition of the input list.
:rtype: List[List[List[int]] | List[str]]

{raises})pbdoc",
            name,
            extra_doc));
  }

  ////////////////////////////////////////////////////////////////////////

  template void
  def_non_trivial_classes<ToddCoxeter<word_type>>(py::module&,
                                                  std::string_view,
                                                  doc);

  template void
  def_non_trivial_classes<ToddCoxeter<std::string>>(py::module&,
                                                    std::string_view,
                                                    doc);

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  template <typename Thing>
  void def_partition(py::module&      m,
                     std::string_view class_name,
                     std::string_view func_prefix,
                     doc              extra_doc) {
    using Word = typename Thing::native_word_type;

    std::string func_name = fmt::format("{}_partition", func_prefix);
    m.def(
        func_name.c_str(),
        [](Thing& ci, std::vector<Word> const& words) {
          return congruence_interface::partition(
              ci, rx::iterator_range(words.begin(), words.end()));
        },
        py::arg(extra_doc.var.data()),
        py::arg("words"),
        make_doc(R"pbdoc(
:sig=({var}: {name}, words: List[List[int] | str]) -> List[List[List[int]] | List[str]]:
{only_document_once}

Partition a list of words.

This function returns the classes in the partition of the words in the input
list *words* induced by the :any:`{name}` instance *{var}*. This function
triggers a full enumeration of *{var}*.

{detail}

:param {var}: the :any:`{name}` instance.
:type {var}: {name}

:param words: the input list of words.
:type words: List[List[int] | str]

:returns: The partitioned list of words.
:rtype: List[List[List[int]] | List[str]]

{raises}
)pbdoc",
                 class_name,
                 extra_doc));
  }

  template void def_partition<ToddCoxeter<word_type>>(py::module&,
                                                      std::string_view,
                                                      std::string_view,
                                                      doc);

  template void def_partition<ToddCoxeter<std::string>>(py::module&,
                                                        std::string_view,
                                                        std::string_view,
                                                        doc);

  ////////////////////////////////////////////////////////////////////////
  // The init function for CongruenceInterface
  ////////////////////////////////////////////////////////////////////////

  void init_cong_intf(py::module& m) {
    py::class_<CongruenceInterface, Runner> thing(m,
                                                  "Congruence"
                                                  "Interface",
                                                  R"pbdoc(
Class collecting common aspects of classes representing congruences.

Every class for representing a congruence in ``libsemigroups_pybind11`` is
derived from :any:`CongruenceInterface`, which holds the member functions and
data that are common to all its derived classes. These classes are:

*  :any:`Congruence`
*  :any:`Kambites`
*  :py:class:`KnuthBendixRewriteTrie`
*  :any:`ToddCoxeterWord`
)pbdoc");

    thing.def(
        "kind",
        [](CongruenceInterface const& self) { return self.kind(); },
        R"pbdoc(
:sig=(self: CongruenceInterface) -> congruence_kind:

The kind of the congruence (1- or 2-sided).

This function returns the kind of the congruence represented by a derived
class of :any:`CongruenceInterface`. See :any:`congruence_kind` for details.

:complexity:
   Constant.

:returns:
   The kind of the congruence (1- or 2-sided).
:rtype:
   congruence_kind
)pbdoc");

    thing.def("internal_generating_pairs",
              &CongruenceInterface::internal_generating_pairs,
              R"pbdoc(
:sig=(self: CongruenceInterface) -> List[List[int]]:

Returns the generating pairs of the congruence.

This function returns the generating pairs of the congruence represented by
any derived class of a :any:`CongruenceInterface`. This is always a
``List[List[int]]``, regardless of the type of presentation used to construct
the derived class.

:complexity:
   Constant.

:returns:
   The generating pairs.

:rtype:
   List[List[int]]
)pbdoc");

    thing.def("number_of_generating_pairs",
              &CongruenceInterface::number_of_generating_pairs,
              R"pbdoc(
Returns the number of generating pairs.

This function returns the number of generating pairs of the congruence.

:complexity:
   Constant.

:returns:
   The number of generating pairs.
:rtype:
   int
)pbdoc");
  }  // init_cong_intf
}  // namespace libsemigroups
