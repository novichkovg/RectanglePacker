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

#ifndef INCLUDED_NODE
#define INCLUDED_NODE

#include <Rect.h>
#include <vector>

class Node {

public:
    //  CTORS, DTORS
    Node () = default;
    Node (double x, double y, double w, double h);
    ~Node ();

    //  not needed stuff
    Node (const Node &) = delete;
    Node & operator=(const Node&) = delete;

    //  MANIPULATORS
    bool insert (const Rect& r);

    //  ACCESSORS
    void visit_nodes_collect_rectangles(std::vector <Rect> & rects) const;

private:
    Node   *left_ = nullptr;
    Node   *right_ = nullptr;
    Rect    rect_;

    //  PRIVATE ACCESSORS
    bool    fit_check(const Rect & rect) const;
    bool    is_leaf() const;
};

#endif // INCLUDED_NODE
