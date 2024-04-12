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

// C std headers....
// TODO complete or delete

// C++ stl headers....
// TODO complete or delete

// libsemigroups headers
#include <libsemigroups/bmat8.hpp>

// pybind11....
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// libsemigroups_pybind11....
#include "main.hpp"  // for init_bmat8

namespace py = pybind11;

namespace libsemigroups {

  void init_bmat8(py::module& m) {
    py::class_<BMat8>(m, "BMat8")
        .def(py::init<>())
        .def(py::init<uint64_t>())
        .def(py::init<std::vector<std::vector<bool>> const&>())
        .def(py::init<BMat8 const&>())
        .def("get",
             &BMat8::get,
             py::arg("i"),
             py::arg("j"),
             R"pbdoc(
:param i:
   the row of the entry sought.

:type i:
   int

:param j:
   the column of the entry sought.

:type j:
   intReturns the entry in the ( ``i`` , ``j`` )th position.This member
   function returns the entry in the ( ``i`` , ``j`` )th position.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:returns:
   A ``bool``.

:rtype:
   bool

)pbdoc")
        .def("set",
             &BMat8::set,
             py::arg("i"),
             py::arg("j"),
             py::arg("val"),
             R"pbdoc(
:param i:
   the row

:type i:
   int

:param j:
   the column

:type j:
   int

:param val:
   the value to set in position (i, j)th

:type val:
   boolSets the ( ``i`` , ``j`` )th position to ``val``.This member
   function sets the ( ``i`` , ``j`` )th entry of ``self`` to ``val`` .
   Uses the bit twiddle for setting bits found`here
   <http://graphics.stanford.edu/~seander/bithacks>`_.

:raises:
   :any:`LibsemigroupsError` if ``i`` or ``j`` is out of bounds.

:complexity:
   Constant.

:returns:
   (None)

:rtype:
   void

)pbdoc")
        .def("to_int",
             &BMat8::to_int,
             R"pbdoc(
Returns the integer representation of ``self``.Returns an unsigned
integer obtained by interpreting an 8 x 8 :any:`BMat8` as a sequence of
64 bits (reading rows left to right, from top to bottom) and then
realising this sequence as an unsigned int.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:parameters:
   (None)

:returns:
   A ``uint64_t``.

:rtype:
   uint64_t

)pbdoc")
        .def("transpose",
             &BMat8::transpose,
             R"pbdoc(
Returns the transpose of ``self``.Uses the technique found in`Knu09
<../biblio.html#knuth2009aa>`_.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:parameters:
   (None)

:returns:
   A :any:`BMat8`.

:rtype:
   BMat8

)pbdoc")
        .def("swap",
             &BMat8::swap,
             py::arg("that"),
             R"pbdoc(
:param that:
   the BMat8 to swap this with.

:type that:
   BMat8 Swaps ``self`` with ``that``.This member function swaps the
   values of ``self`` and ``that``.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:returns:
   (None)

:rtype:
   void

)pbdoc")
        .def("row_space_basis",
             &BMat8::row_space_basis,
             R"pbdoc(
Find a basis for the row space of ``self``.This member function returns
a :any:`BMat8` whose non-zero rows form a basis for the row space of
``self``.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:parameters:
   (None)

:returns:
   A :any:`BMat8`.

:rtype:
   BMat8

)pbdoc")
        .def("col_space_basis",
             &BMat8::col_space_basis,
             R"pbdoc(
Find a basis for the column space of ``self``.This member function
returns a :any:`BMat8` whose non-zero columns form a basis for the
column space of ``self``.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:parameters:
   (None)

:returns:
   A :any:`BMat8`.

:rtype:
   BMat8

)pbdoc")
        .def("rows",
             &BMat8::rows,
             R"pbdoc(
Returns a vector containing the rows of ``self``This member function
returns a :any:`std::vector` of uint8_ts representing the rows of
``self`` . The vector will always be of length 8, even if ``self`` was
constructed with fewer rows.

:raises:
   This function guarantees not to throw a ``LibsemigroupsError``.

:complexity:
   Constant.

:parameters:
   (None)

:returns:
   A std::vector<uint8_t>.

:rtype:
   std::vector

)pbdoc")
        .def("row_space_size",
             &BMat8::row_space_size,
             R"pbdoc(

Find the size of the row space of ``self``.

:raises:    This function guarantees not to throw a ``LibsemigroupsError``.

:complexity:  :math:`O(n)` where :math:`n` is the return value of this function.

:parameters:  (None)

.. seealso::  :any:`bmat8::col_space_size`.

:returns: A ``int``.

:rtype: int
)pbdoc")
        .def("number_of_rows",
             &BMat8::number_of_rows,
             R"pbdoc(

Returns the number of non-zero rows in ``self``.BMat8s do not know their "dimension" - in effect they are all of dimension 8. However, this member function can be used to obtain the number of non-zero rows of ``self``.

:raises:    This function is ``noexcept`` and is guaranteed never to throw.

:complexity: Constant.

:parameters:  (None)

.. seealso::  :any:`bmat8::number_of_cols` and :any:`bmat8::minimum_dim`.

:returns: A ``int``.

:rtype: int
)pbdoc")
        .def("is_regular_element",
             &BMat8::is_regular_element,
             R"pbdoc(
Check whether ``self`` is a regular element of the full boolean matrix
monoid of appropriate dimension.

:raises:
   This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
   Constant.

:parameters:
   (None)

:returns:
   A ``True`` if there exists a boolean matrix ``y`` such that ``x * y *
   x = x`` where ``x`` is ``self``.

:rtype:
   bool

)pbdoc")
        .def(
            "random",
            [](BMat8& self) { return self.random(); },
            R"pbdoc(
Construct a random :any:`BMat8`.This static member function returns a
:any:`BMat8` chosen at random.

:raises:
   This function guarantees not to throw a ``LibsemigroupsError``.

:parameters:
   (None)

:returns:
   A :any:`BMat8`.

:rtype:
   BMat8

)pbdoc")
        .def(
            "random",
            [](BMat8& self, size_t dim) { return self.random(dim); },
            py::arg("dim"),
            R"pbdoc(
Construct a random :any:`BMat8` of dimension at most ``dim``.This static
member function returns a :any:`BMat8` chosen at random, where only the
top-left ``dim`` x ``dim`` entries can be non-zero.

:raises:
   This function guarantees not to throw a ``LibsemigroupsError``.

:parameters:
   (None)

:returns:
   A :any:`BMat8`.

:rtype:
   BMat8

)pbdoc");
    /*  .def("one",
           &BMat8::one,
           py::arg("dim"),
           R"pbdoc(
:param dim:
the dimension of the identity (default: 8)

:type dim:
intReturns the identity :any:`BMat8`.This member function returns the
:any:`BMat8` with the first ``dim`` entries in the main diagonal
equal to ``1`` and every other value equal to ``0``.

:raises:
This function is ``noexcept`` and is guaranteed never to throw.

:complexity:
Constant.

:returns:
A :any:`BMat8`.

:rtype:
BMat8

)pbdoc");*/
  }  // init_bmat8

}  // namespace libsemigroups
