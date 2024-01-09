#include <bits/stdc++.h>
#include <stdexcept> /// for exceptions

using namespace std;

#define Point pair<double, double>
#define x first
#define y second
#define EPS 1e-10

struct Circle
{
    Point center;
    double radius;
};

struct Line
{
    double a, b, c;

    explicit Line() : a(0), b(0), c(0) {
    }

    Line(const Point& A, const Point& B)
    {
        this->a = +(B.y - A.y);
        this->b = -(B.x - A.x);
        this->c = -A.x * B.y + B.x * A.y;
    }
};

Line perpendicularBisector(const Point A, const Point B)
{
    if (A == B)
        throw invalid_argument("A == B");

    Point middle((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
    double slope = -(A.x - B.x) / (A.y - B.y);

    Line L;
    L.a = -slope;
    L.b = 1.0;
    L.c = -middle.y + slope * middle.x;

    return L;
}

Point lineToLineIntersection(const Line A, const Line B)
{
    double det = A.a * B.b - A.b * B.a;

    if (abs(det) < EPS) /// det == 0
        throw invalid_argument("lines do not intersect");

    double x = -(A.c * B.b - A.b * B.c) / det;
    double y = -(A.a * B.c - A.c * B.a) / det;

    return Point(x, y);
}

double dist(const Point A, const Point B)
{
    return ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

/// A,B,C are given in either counter-clockwise or clockwise order
/// A,B,C are not collinear (if they are the circle is not unique)
Circle circleFrom3Points(const Point A, const Point B, const Point C)
{
    Line AB = perpendicularBisector(A, B);
    Line BC = perpendicularBisector(B, C);

    Point center = lineToLineIntersection(AB, BC);
    double radius = dist(center, B);

    return {center, radius};
}

int main()
{
    Point A(4, 1);
    Point B(5, 2);
    Point C(2, 5);

    Circle c = circleFrom3Points(A, B, C);

    cout << c.center.x << " " << c.center.y << " " << c.radius << endl;
    cout << dist(A, c.center) << " " << c.radius << endl;
    cout << dist(c.center, B) << " " << c.radius << endl;
    cout << dist(c.center, C) << " " << c.radius << endl;

    return 0;
}
