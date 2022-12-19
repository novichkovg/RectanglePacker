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

#include <Node.h>

//  CTORS, DTORS
Node::Node (double x, double y, double w, double h)
: left_(nullptr)
, right_(nullptr)
, rect_(x,y,w,h)
{
}

Node::~Node () {
    delete left_;
    delete right_;
}

//  ACCESSORS
bool Node::fit_check(const Rect & r) const {
    return r.w <= rect_.w && r.h <= rect_.h;
}

bool Node::is_leaf() const {
    return left_ == nullptr && right_ == nullptr;
}

//  MANIPULATORS
bool Node::insert (const Rect& r)
{
    if (is_leaf()) {
        if (fit_check(r) == false) {
            return false;
        }

        double dw = rect_.w - r.w;
        double dh = rect_.h - r.h;

        if (dw < dh) {
            left_  = new Node(rect_.x,       rect_.y + r.h, rect_.w, dh);
            right_ = new Node(rect_.x + r.w, rect_.y,       dw,      r.h);
        }
        else {
            left_  = new Node(rect_.x,        rect_.y + r.h, r.w, dh);
            right_ = new Node(rect_.x + r.w, rect_.y,       dw,  rect_.h);
        }
        rect_.w = r.w;
        rect_.h = r.h;
    }
    else {
        if (left_->insert(r) == false) {
            return right_->insert(r);
        }
    }
    return true;
}

void Node::visit_nodes_collect_rectangles(std::vector <Rect> & rects) const {
    if (is_leaf()) {
        return;
    }

    rects.push_back(rect_);
    left_->visit_nodes_collect_rectangles(rects);
    right_->visit_nodes_collect_rectangles(rects);
}
