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
#include <libsemigroups/adapters.hpp>
#include <libsemigroups/bmat8.hpp>

// pybind11....
#include <pybind11/pybind11.h>

// libsemigroups_pybind11....
#include "main.hpp"  // for init_TODO

namespace py = pybind11;

namespace libsemigroups {

  namespace {
    template <typename Element, typename Point>
    void bind_imagerightaction(py::module& m, std::string const& name) {
      using ImageRightAction_ = ImageRightAction<Element, Point>;

      py::class_<ImageRightAction_>(m, name.c_str())
          .def("__call__", [](BMat8& res, BMat8 const& pt, BMat8 const& x) {
            res = (pt * x).row_space_basis();
          });

    }  // bind_imagerightaction
  }    // namespace
       //
  void init_imagerightaction(py::module& m) {
    // One call to bind is required per list of types
    bind_imagerightaction<BMat8, BMat8>(m, "ImageRightActionBMat8BMat8");
  }

}  // namespace libsemigroups
