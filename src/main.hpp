//
// libsemigroups - C++ library for semigroups and monoids
// Copyright (C) 2020 James D. Mitchell
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

#ifndef SRC_MAIN_HPP_
#define SRC_MAIN_HPP_

#include <pybind11/chrono.h>
#include <pybind11/functional.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace libsemigroups {
  namespace py = pybind11;

  void init_action_digraph(py::module&);
  void init_bipart(py::module&);
  void init_bmat8(py::module&);
  void init_cong(py::module&);
  void init_forest(py::module&);
  void init_fpsemi(py::module&);
  void init_froidure_pin(py::module&);
  void init_knuth_bendix(py::module&);
  void init_matrix(py::module&);
  void init_pbr(py::module&);
  void init_todd_coxeter(py::module&);
  void init_transf(py::module&);
  void init_words(py::module&);

}  // namespace libsemigroups

#endif  // SRC_MAIN_HPP_
