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
#include <libsemigroups/cong-intf.hpp>
#include <libsemigroups/cong.hpp>
#include <libsemigroups/kambites.hpp>
#include <libsemigroups/knuth-bendix.hpp>
#include <libsemigroups/todd-coxeter.hpp>

// pybind11....
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// libsemigroups_pybind11....
#include "cong-intf.hpp"  // for doc
#include "main.hpp"       // for init_cong_intf

namespace py = pybind11;

namespace libsemigroups {

#define EXPLICIT_INSTANTIATION1(FUNC, TYPE1) \
  template void FUNC<TYPE1>(                 \
      py::class_<TYPE1, CongruenceInterface>&, std::string_view, doc);

#define EXPLICIT_INSTANTIATION2(FUNC, TYPE1, TYPE2) \
  template void FUNC<TYPE1, TYPE2>(                 \
      py::class_<TYPE2, CongruenceInterface>&, std::string_view, doc);

  template <typename Thing>
  void def_construct_default(py::class_<Thing, CongruenceInterface>& thing,
                             std::string_view                        name,
                             doc extra_doc) {
    thing.def(py::init<>(),
              fmt::format(R"pbdoc(
Default def_construct_kind_presentation. This function default constructs an uninitialised
:any:`{}` instance.

{}
)pbdoc",
                          name,
                          extra_doc.detail)
                  .c_str());
  }

  EXPLICIT_INSTANTIATION1(def_construct_default, Congruence)
  EXPLICIT_INSTANTIATION1(def_construct_default, Kambites<>)
  EXPLICIT_INSTANTIATION1(def_construct_default,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION1(def_construct_default,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION1(def_construct_default, ToddCoxeter)

  template <typename Word, typename Thing>
  void
  def_construct_kind_presentation(py::class_<Thing, CongruenceInterface>& thing,
                                  std::string_view                        name,
                                  doc extra_doc) {
    thing.def(py::init<congruence_kind, Presentation<Word> const&>(),
              py::arg("knd"),
              py::arg("p"),
              fmt::format(R"pbdoc(
:sig=(self: {0}, knd: congruence_kind, p: PresentationStrings) -> None:
:only-document-once:

Construct from :any:`congruence_kind` and :any:`PresentationStrings`.

This function constructs a :any:`{0}` instance representing a congruence
of kind *knd* over the semigroup or monoid defined by the presentation *p*.

{1}

:param knd: the kind (onesided or twosided) of the congruence.
:type knd: congruence_kind

:param p: the presentation.
:type p: PresentationStrings

:raises LibsemigroupsError: if *p* is not valid.

{2}
  )pbdoc",
                          name,
                          extra_doc.detail,
                          extra_doc.raises)
                  .c_str());
  }

  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          word_type,
                          Congruence)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          word_type,
                          Kambites<>)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          word_type,
                          ToddCoxeter)

  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          std::string,
                          Congruence)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          std::string,
                          Kambites<>)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_construct_kind_presentation,
                          std::string,
                          ToddCoxeter)

  template <typename Thing>
  void def_init_default(py::class_<Thing, CongruenceInterface>& thing,
                        std::string_view                        name,
                        doc                                     extra_doc) {
    thing.def(
        "init",
        [](Thing& self) -> Thing& { return self.init(); },
        fmt::format(R"pbdoc(
Re-initialize a :any:`{0}` instance.

This function puts a :any:`{0}` instance back into the state that it would
have been in if it had just been newly default constructed.

{1}

:returns:
  ``self``.
:rtype:
    {0})pbdoc",
                    name,
                    extra_doc.detail)
            .c_str());
  }

  EXPLICIT_INSTANTIATION1(def_init_default, Congruence)
  EXPLICIT_INSTANTIATION1(def_init_default, Kambites<>)
  EXPLICIT_INSTANTIATION1(def_init_default, KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION1(def_init_default,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION1(def_init_default, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_init_kind_presentation(py::class_<Thing, CongruenceInterface>& thing,
                                  std::string_view                        name,
                                  doc extra_doc) {
    thing.def(
        "init",
        [](Thing&                    self,
           congruence_kind           knd,
           Presentation<Word> const& p) -> Thing& { return self.init(knd, p); },
        py::arg("knd"),
        py::arg("p"),
        // TODO(0) adding only-document-once here means that the other
        // overloads of init are suppressed also :(
        // :only-document-once:
        fmt::format(R"pbdoc(
:sig=(self: {0}, knd: congruence_kind, p: PresentationStrings) -> {0}:
:only-document-once:

Re-initialize a :any:`{0}` instance.

This function re-initializes a :any:`{0}` instance as if it
had been newly constructed from *knd* and *p*.

{1}

:param knd: the kind (onesided or twosided) of the congruence.
:type knd: :any:`congruence_kind`

:param p: the presentation.
:type p: PresentationStrings

:returns:  ``self``.
:rtype: {0}

:raises LibsemigroupsError: if *p* is not valid.

{2}
)pbdoc",
                    name,
                    extra_doc.detail,
                    extra_doc.raises)
            .c_str());
  }

  EXPLICIT_INSTANTIATION2(def_init_kind_presentation, word_type, Congruence)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation, word_type, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation, word_type, ToddCoxeter)

  EXPLICIT_INSTANTIATION2(def_init_kind_presentation, std::string, Congruence)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation, std::string, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_init_kind_presentation, std::string, ToddCoxeter)

  template <typename Thing>
  void def_copy(py::class_<Thing, CongruenceInterface>& thing,
                std::string_view                        name,
                doc                                     extra_doc) {
    thing.def(
        "copy",
        [](Thing const& self) { return Thing(self); },
        fmt::format(R"pbdoc(
Copy a :any:`{0}` object.

{1}

:returns: A copy.
:rtype: {0})pbdoc",
                    name,
                    extra_doc.detail)
            .c_str());

    thing.def(
        "__copy__",
        [](Thing const& self) { return Thing(self); },
        fmt::format(R"pbdoc(
Copy a :any:`{0}` object.

{1}

:returns: A copy.
:rtype: {0})pbdoc",
                    name,
                    extra_doc.detail)
            .c_str());
  }

  EXPLICIT_INSTANTIATION1(def_copy, Congruence)
  EXPLICIT_INSTANTIATION1(def_copy, Kambites<>)
  EXPLICIT_INSTANTIATION1(def_copy, KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION1(def_copy, KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION1(def_copy, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_add_generating_pair(py::class_<Thing, CongruenceInterface>& thing,
                               std::string_view                        name,
                               doc extra_doc) {
    thing.def(
        "add_generating_pair",
        [](Thing& self, Word const& u, Word const& v) -> Thing& {
          return congruence_interface::add_generating_pair(self, u, v);
        },
        py::arg("u"),
        py::arg("v"),
        fmt::format(
            R"pbdoc(
:sig=(self: {0}, u: List[int] | str, v: List[int] | str) -> {0}:
:only-document-once:

Add a generating pair.

This function adds a generating pair to the congruence represented by a
:any:`{0}` instance.

{1}

:param u: the first item in the pair.
:type u: List[int] | str

:param v: the second item in the pair.
:type v: List[int] | str

:returns: ``self``.
:rtype: {0}

:raises LibsemigroupsError:
  if any of the values in *u* or *v* is out of range, i.e. they do not belong
  to ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

:raises LibsemigroupsError:  if :any:`Runner.started` returns ``True``.

{2}
)pbdoc",
            name,
            extra_doc.detail,
            extra_doc.raises)
            .c_str());
  }

  EXPLICIT_INSTANTIATION2(def_add_generating_pair, word_type, Congruence)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair, word_type, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair, word_type, ToddCoxeter)

  EXPLICIT_INSTANTIATION2(def_add_generating_pair, std::string, Congruence)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair, std::string, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_add_generating_pair, std::string, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_currently_contains(py::class_<Thing, CongruenceInterface>& thing,
                              std::string_view                        name,
                              doc extra_doc) {
    thing.def(
        "currently_contains",
        [](Thing const& self, Word const& u, Word const& v) {
          return congruence_interface::currently_contains(self, u, v);
        },
        py::arg("u"),
        py::arg("v"),
        fmt::format(R"pbdoc(
:sig=(self: {0}, u: List[int] | str, v: List[int] | str) -> bool:
:only-document-once:

Check whether a pair of words is already known to belong to the congruence.

This function checks whether or not the words *u* and *v* are already known to
be contained in the congruence represented by a :py:class:`{0}` instance.
This function performs no enumeration, so it is possible for the words to be
contained in the congruence, but that this is not currently known.

:param u: the first word.
:type u: List[int] | str

:param v: the second word.
:type v: List[int] | str

:returns:
    *  :any:`tril.true` if the words are known to belong to the congruence;
    *  :any:`tril.false` if the words are known to not belong to the congruence;
    *  :any:`tril.unknown` otherwise.
:rtype: tril

:raises LibsemigroupsError:
  if any of the values in *u* or *v* is out of range, i.e. they do not belong
  to ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{1}
)pbdoc",
                    name,
                    extra_doc.raises)
            .c_str());
  }

  EXPLICIT_INSTANTIATION2(def_currently_contains, word_type, Congruence)
  EXPLICIT_INSTANTIATION2(def_currently_contains, word_type, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_currently_contains,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_currently_contains,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_currently_contains, word_type, ToddCoxeter)

  EXPLICIT_INSTANTIATION2(def_currently_contains, std::string, Congruence)
  EXPLICIT_INSTANTIATION2(def_currently_contains, std::string, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_currently_contains,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_currently_contains,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_currently_contains, std::string, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_contains(py::class_<Thing, CongruenceInterface>& thing,
                    std::string_view                        name,
                    doc                                     extra_doc) {
    thing.def(
        "contains",
        [](Thing& self, Word const& u, Word const& v) {
          return congruence_interface::contains(self, u, v);
        },
        py::arg("u"),
        py::arg("v"),
        fmt::format(R"pbdoc(
:sig=(self: {0}, u: List[int] | str, v: List[int] | str) -> bool:
:only-document-once:

Check containment of a pair of words.

This function checks whether or not the words *u* and *v* are contained in the
congruence represented by a :py:class:`{0}` instance.

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

{1}
)pbdoc",
                    name,
                    extra_doc.raises)
            .c_str());
  }

  EXPLICIT_INSTANTIATION2(def_contains, word_type, Congruence)
  EXPLICIT_INSTANTIATION2(def_contains, word_type, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_contains,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_contains,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_contains, word_type, ToddCoxeter)

  EXPLICIT_INSTANTIATION2(def_contains, std::string, Congruence)
  EXPLICIT_INSTANTIATION2(def_contains, std::string, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_contains,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_contains,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_contains, std::string, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_reduce_no_run(py::class_<Thing, CongruenceInterface>& thing,
                         std::string_view                        name,
                         doc                                     extra_doc) {
    thing.def(
        "reduce_no_run",
        [](Thing& self, Word const& w) {
          return congruence_interface::reduce_no_run(self, w);
        },
        py::arg("w"),
        fmt::format(R"pbdoc(
:sig=(self: {0}, w: List[int] | str) -> List[int] | str:
:only-document-once:

Reduce a word.

If :any:`Runner.finished` returns ``True``, then this function returns a normal
form for the input word *w*.

{1}

:param w: the input word.
:type w: List[int] | str

:returns: A word equivalent to the input word.
:rtype: List[int] | str

:raises LibsemigroupsError:
  if any of the values in *w* is out of range, i.e. they do not belong to
  ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{2})pbdoc",
                    name,
                    extra_doc.detail,
                    extra_doc.raises)
            .c_str());
  }

  // EXPLICIT_INSTANTIATION2(def_reduce_no_run, word_type, Congruence)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run, word_type, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run, word_type, ToddCoxeter)

  // EXPLICIT_INSTANTIATION2(def_reduce_no_run, std::string, Congruence)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run, std::string, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_reduce_no_run, std::string, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_reduce(py::class_<Thing, CongruenceInterface>& thing,
                  std::string_view                        name,
                  doc                                     extra_doc) {
    thing.def(
        "reduce",
        [](Thing& self, Word const& w) {
          return congruence_interface::reduce(self, w);
        },
        py::arg("w"),
        fmt::format(R"pbdoc(
:sig=(self: {0}, w: List[int] | str) -> List[int] | str:
:only-document-once:

Reduce a word.

This function triggers a full enumeration of an :py:class:`{0}` object and then
reduces the word *w*. As such the returned word is a normal form for the input
word.

{1}

:param w: the input word.
:type w: List[int] | str

:returns: A normal form for the input word.
:rtype: List[int] | str

:raises LibsemigroupsError:
  if any of the values in *w* is out of range, i.e. they do not belong to
  ``presentation().alphabet()`` and :any:`PresentationStrings.validate_word`
  raises.

{2}
)pbdoc",
                    name,
                    extra_doc.detail,
                    extra_doc.raises)
            .c_str());
  }

  // EXPLICIT_INSTANTIATION2(def_reduce, word_type, Congruence)
  EXPLICIT_INSTANTIATION2(def_reduce, word_type, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_reduce,
                          word_type,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_reduce,
                          word_type,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_reduce, word_type, ToddCoxeter)

  // EXPLICIT_INSTANTIATION2(def_reduce, std::string, Congruence)
  EXPLICIT_INSTANTIATION2(def_reduce, std::string, Kambites<>)
  EXPLICIT_INSTANTIATION2(def_reduce,
                          std::string,
                          KnuthBendix<detail::RewriteTrie>)
  EXPLICIT_INSTANTIATION2(def_reduce,
                          std::string,
                          KnuthBendix<detail::RewriteFromLeft>)
  EXPLICIT_INSTANTIATION2(def_reduce, std::string, ToddCoxeter)

  template <typename Word, typename Thing>
  void def_non_trivial_classes(py::module&      m,
                               std::string_view name,
                               doc              extra_doc) {
    std::string func_name(name);
    std::transform(func_name.begin(),
                   func_name.end(),
                   func_name.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    func_name += "_non_trivial_classes";
    m.def(
        func_name.c_str(),
        [](Thing& ci, std::vector<Word> const& words) {
          return congruence_interface::non_trivial_classes(
              ci, rx::iterator_range(words.begin(), words.end()));
        },
        py::arg("ci"),
        py::arg("words"),
        fmt::format(
            R"pbdoc(
:sig=(ci: {0}, words: List[List[int] | str]) -> List[List[List[int]] | List[str]]:
:only-document-once:

Find the non-trivial classes in the partition of a list of words.

This function returns the classes with size at least :math:`2` in the partition
of the words in the list *words* induced by the :any:`{0}` instance *ci*.

{1}

:param ci: the :any:`{0}` instance.
:type ci: {0}

:param words: the input list of words.
:type words: List[List[int] | str]

:returns: The partition of the input list.
:rtype: List[List[List[int]] | List[str]]

{2})pbdoc",
            name,
            extra_doc.detail,
            extra_doc.raises)
            .c_str());
  }

  // TODO(0) uncomment
  // template void def_non_trivial_classes<word_type, Congruence>(py::module&,
  //                                                              std::string_view,
  //                                                              doc);
  template void
  def_non_trivial_classes<word_type, KnuthBendix<detail::RewriteTrie>>(
      py::module&,
      std::string_view,
      doc);

  template void
  def_non_trivial_classes<word_type, KnuthBendix<detail::RewriteFromLeft>>(
      py::module&,
      std::string_view,
      doc);

  template void
  def_non_trivial_classes<word_type, Kambites<word_type>>(py::module&,
                                                          std::string_view,
                                                          doc);

  template void def_non_trivial_classes<word_type, Kambites<>>(py::module&,
                                                               std::string_view,
                                                               doc);

  // TODO(0) uncomment
  // template void def_non_trivial_classes<std::string, Congruence>(py::module&,
  //                                                              std::string_view,
  //                                                              doc);
  template void
  def_non_trivial_classes<std::string, KnuthBendix<detail::RewriteTrie>>(
      py::module&,
      std::string_view,
      doc);

  template void
  def_non_trivial_classes<std::string, KnuthBendix<detail::RewriteFromLeft>>(
      py::module&,
      std::string_view,
      doc);

  template void
  def_non_trivial_classes<std::string, Kambites<word_type>>(py::module&,
                                                            std::string_view,
                                                            doc);
  template void
  def_non_trivial_classes<std::string, Kambites<>>(py::module&,
                                                   std::string_view,
                                                   doc);

  ////////////////////////////////////////////////////////////////////////
  // The init function for CongruenceInterface
  ////////////////////////////////////////////////////////////////////////

  void init_cong_intf(py::module& m) {
    py::class_<CongruenceInterface, Runner> thing(m,
                                                  "CongruenceInterface",
                                                  R"pbdoc(
Class collecting common aspects of classes representing congruences.

Every class for representing a congruence in ``libsemigroups_pybind11`` is
derived from :any:`CongruenceInterface`, which holds the member functions and
data that are common to all its derived classes. These classes are:

*  :any:`Congruence`
*  :any:`Kambites`
*  :py:class:`KnuthBendixRewriteTrie`
*  :any:`ToddCoxeter`
)pbdoc");

    thing.def(
        "kind",
        [](CongruenceInterface const& self) { return self.kind(); },
        R"pbdoc(
:sig=(self: CongruenceInterface) -> congruence_kind:
The kind of the congruence (1- or 2-sided).

This function returns the kind of the congruence represented by a derived class
of :any:`CongruenceInterface`. See :any:`congruence_kind` for details.

:complexity:
   Constant.

:returns:
   The kind of the congruence (1- or 2-sided).
:rtype:
   congruence_kind
)pbdoc");

    thing.def("generating_pairs",
              &CongruenceInterface::generating_pairs,
              R"pbdoc(
:sig=(self: CongruenceInterface) -> List[List[int]]:

Returns the generating pairs of the congruence.

This function returns the generating pairs of the congruence represented by any
derived class of a :any:`CongruenceInterface`. This is always a
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

This function returns the number of generating pairs, which is the size of
:any:`generating_pairs` divided by :math:`2`.

:complexity:
   Constant.

:returns:
   The number of generating pairs.
:rtype:
   int
)pbdoc");
  }  // init_cong_intf

}  // namespace libsemigroups
