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

  template <typename Word, typename Thing>
  void contains(py::class_<Thing, CongruenceInterface>& thing,
                std::string_view                        name,
                std::string_view                        extra_doc = "") {
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
                    extra_doc)
            .c_str());
  }
}  // namespace libsemigroups
#endif  // SRC_CONG_INTF_HPP_
