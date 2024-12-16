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
  class CongruenceInterface;

  // A little helper struct to simulate keyword arguments for the functions
  // declared below.
  struct doc {
    std::string_view detail = "";
    std::string_view raises = "";
  };

  template <typename Thing>
  void def_construct_default(py::class_<Thing, CongruenceInterface>& thing,
                             std::string_view                        name,
                             doc extra_doc = {});

  template <typename Word, typename Thing>
  void
  def_construct_kind_presentation(py::class_<Thing, CongruenceInterface>& thing,
                                  std::string_view                        name,
                                  doc extra_doc = {});

  template <typename Thing>
  void def_init_default(py::class_<Thing, CongruenceInterface>& thing,
                        std::string_view                        name,
                        doc                                     extra_doc = {});

  template <typename Word, typename Thing>
  void def_init_kind_presentation(py::class_<Thing, CongruenceInterface>& thing,
                                  std::string_view                        name,
                                  doc extra_doc = {});

  template <typename Thing>
  void def_copy(py::class_<Thing, CongruenceInterface>& thing,
                std::string_view                        name,
                doc                                     extra_doc = {});

  template <typename Word, typename Thing>
  void def_add_generating_pair(py::class_<Thing, CongruenceInterface>& thing,
                               std::string_view                        name,
                               doc extra_doc = {});

  template <typename Word, typename Thing>
  void def_currently_contains(py::class_<Thing, CongruenceInterface>& thing,
                              std::string_view                        name,
                              doc extra_doc = {});

  template <typename Word, typename Thing>
  void def_contains(py::class_<Thing, CongruenceInterface>& thing,
                    std::string_view                        name,
                    doc                                     extra_doc = {});

  template <typename Word, typename Thing>
  void def_reduce_no_run(py::class_<Thing, CongruenceInterface>& thing,
                         std::string_view                        name,
                         doc extra_doc = {});

  template <typename Word, typename Thing>
  void def_reduce(py::class_<Thing, CongruenceInterface>& thing,
                  std::string_view                        name,
                  doc                                     extra_doc = {});

  template <typename Word, typename Thing>
  void def_non_trivial_classes(py::module&      m,
                               std::string_view name,
                               doc              extra_doc = {});

}  // namespace libsemigroups
#endif  // SRC_CONG_INTF_HPP_
