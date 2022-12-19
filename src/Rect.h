/*
    Rectangle Packer

    Copyright (C) 2022, Novichkov Gleb, PhD

    Rectangle Packer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    Rectangle Packer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rectangle Packer.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef INCLUDED_RECT
#define INCLUDED_RECT

struct Rect {

    //  CTORS
    Rect () = default;
    Rect (double w_, double h_);
    Rect (double x_, double y_, double w_, double h_);

    //  ACCESSORS
    double area() const;
    void  print() const;

    //  DATA
    double x = 0;
    double y = 0;
    double w = 0;
    double h = 0;
};

#endif // INCLUDED_RECTT
