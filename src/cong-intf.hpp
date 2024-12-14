//
// libsemigroups_pybind11 - python bindings for the C++ library libsemigroups
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

#ifndef SRC_CONG_INTF_HPP_
#define SRC_CONG_INTF_HPP_

#include <string_view>

#include <pybind11/pybind11.h>  // for class_, make_iterator, enum_, init

namespace py = pybind11;

namespace libsemigroups {

  struct doc {
    std::string_view detail = "";
    std::string_view raises = "";
  };

  // TODO(0) move the definitions in to cong-intf.cpp since the types are fixed.
  // TODO(0) add prefix def_

  template <typename Thing>
  void def_construct_default(py::class_<Thing, CongruenceInterface>& thing,
                             std::string_view                        name,
                             doc extra_doc = {}) {
    thing.def(py::init<>(),
              fmt::format(R"pbdoc(
Default constructor. This function default constructs an uninitialised
:any:`{}` instance.

{}
)pbdoc",
                          name,
                          extra_doc.detail)
                  .c_str());
  }

  template <typename Word, typename Thing>
  void constructor(py::class_<Thing, CongruenceInterface>& thing,
                   std::string_view                        name,
                   doc                                     extra_doc = {}) {
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

  template <typename Word, typename Thing>
  void
  init_from_kind_presentation(py::class_<Thing, CongruenceInterface>& thing,
                              std::string_view                        name,
                              doc extra_doc = {}) {
    thing.def(
        "init",
        [](Thing& self, congruence_kind knd, Presentation<Word> const& p) {
          return self.init(knd, p);
        },
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

  template <typename Word, typename Thing>
  void currently_contains(py::class_<Thing, CongruenceInterface>& thing,
                          std::string_view                        name,
                          doc extra_doc = {}) {
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

  template <typename Word, typename Thing>
  void contains(py::class_<Thing, CongruenceInterface>& thing,
                std::string_view                        name,
                doc                                     extra_doc = {}) {
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

  template <typename Word, typename Thing>
  void reduce_no_run(py::class_<Thing, CongruenceInterface>& thing,
                     std::string_view                        name,
                     doc                                     extra_doc = {}) {
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

  template <typename Word, typename Thing>
  void reduce(py::class_<Thing, CongruenceInterface>& thing,
              std::string_view                        name,
              doc                                     extra_doc = {}) {
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

  template <typename Thing>
  void def_copy(py::class_<Thing, CongruenceInterface>& thing,
                std::string_view                        name,
                doc                                     extra_doc = {}) {
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

}  // namespace libsemigroups
#endif  // SRC_CONG_INTF_HPP_
