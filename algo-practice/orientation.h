#pragma once

#include <iostream>

using namespace std;

typedef enum {
	COLINEAR = 0,
	CLOCKWISE = 1,
	ANTICLOCKWISE = 2
} Orientation;

struct Point {
	int x;
	int y;
	Point() :x(0), y(0) {};
	Point(int xx, int yy) :x(xx), y(yy) {};
	void print() { cout << "(" << x << "," << y << ")"; }
	friend ostream& operator<<(ostream& os, const Point& p);

	bool operator == (Point& o) {
		return x == o.x and y == o.y;
	}
};

ostream& operator<<(ostream& os, const Point& p) {
	os << "(" << p.x << "," << p.y << ") ";
	return os;
}

ostream& operator<<(ostream& os, Orientation o) {
	switch (o) {
	case COLINEAR:
		os << " COLINEAR ";
		break;
	case CLOCKWISE:
		os << " CLOCKWISE ";
		break;
	case ANTICLOCKWISE:
		os << " ANTICLOCKWISE ";
		break;
	}
	return os;
}

// https://www.geeksforgeeks.org/orientation-3-ordered-points/
// points p, q, r
// slop (y2-y1)/(x2-x1)
// COLINEAR => slop1 == slop2 => (qy-py)(rx-qx) == (ry-qy)(qx-px)
// CLOCKWISE => slop1 < slop2
// ANTICLOCKWISE => slop1 > slop2

Orientation orientation(Point p, Point q, Point r) {
	int val = (q.y - p.y) * (r.x - q.x) - (r.y - q.y) * (q.x - p.x);
	return (val == 0) ? COLINEAR : ((val > 0) ? CLOCKWISE : ANTICLOCKWISE);
}


void testOrientation() {
	Point p(0, 0), q(1, 1);
	Point r1(2, 2), r2(2, 3), r3(3, 2);

	cout << p << q << r1 << orientation(p, q, r1) << endl;
	cout << p << q << r2 << orientation(p, q, r2) << endl;
	cout << p << q << r3 << orientation(p, q, r3) << endl;

	cout << q << p << r2 << orientation(q, p, r2) << endl;
	cout << q << p << r3 << orientation(q, p, r3) << endl;
}


// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

bool segmentsIntersect(Point p, Point q, Point r, Point s) {

	// swap p, q if p.x> q.x for easy visualization, and coding
	if (p.x > q.x) {
		auto t = p;
		p = q;
		q = t;
	}

	// swap r, s if r.x> s.x for easy visualization, and coding
	if (r.x > s.x) {
		auto t = r;
		r = s;
		s = t;
	}

	// Generic case
	auto o1 = orientation(p, q, r);
	auto o2 = orientation(p, q, s);
	auto o3 = orientation(r, s, p);
	auto o4 = orientation(r, s, q);

	if (o1 == COLINEAR && o2 == COLINEAR && o3 == COLINEAR && o4 == COLINEAR) { // special case
		// p,q and r,s are sorted with x already
		if (r.x > q.x || s.x < p.x) {
			return false;
		}
		return true;
	}
	// generic case
	return o1 != o2 && o3 != o4;
}

void testIntersectingSegments()
{
	struct Point p1 = { 1, 1 }, q1 = { 10, 1 };
	struct Point p2 = { 1, 2 }, q2 = { 10, 2 };

	segmentsIntersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

	p1 = { 10, 0 }, q1 = { 0, 10 };
	p2 = { 0, 0 }, q2 = { 10, 10 };
	segmentsIntersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

	p1 = { -5, -5 }, q1 = { 0, 0 };
	p2 = { 1, 1 }, q2 = { 10, 10 };
	segmentsIntersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";
}