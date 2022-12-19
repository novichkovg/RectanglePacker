#include <Rect.h>
#include <cstdio>

Rect::Rect (double w_, double h_)
: Rect(0, 0, w_, h_)
{}

Rect::Rect (double x_, double y_, double w_, double h_)
: x(x_), y(y_), w(w_), h(h_)
{}

double Rect::area() const {
    return w*h;
}

void Rect::print() const {
    printf("x: %lf,\ty: %lf,\tw: %lf,\th: %lf,\tarea: %lf\n", x, y, w, h, area());
}
