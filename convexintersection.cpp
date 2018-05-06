#include "convexintersection.h"

// determines whether a point p1 is inside or outside
// of a line segment defined by sp1 and sp2
// sp1 and sp2 should be consistently provided
// from the convex hull algorithm such that the edges
// are listed in a CCW direction
// p1 belongs to the subject polygon
// sp1 and sp2 belong to the clipping polygon
bool inside(Point p1, Point sp1, Point sp2) {
	if(ccw(sp1, sp2, p1)) return true;
	return false;
}

// computes the point of intersection between the line segment
// defined by s1 and s2, and the infinite line defined by
// i1 and i2.
// Assume that this will only be called when the intersection exists.
Point computeIntersection(Point s1, Point s2, Point i1, Point i2) {
	double a = (s1.x * s2.y) - (s1.y * s2.x);
	double b_x = i1.x - i2.x;
	double b_y = i1.y - i2.y;
	double c_x = s1.x - s2.x;
	double c_y = s1.y - s2.y;
	double d = (i1.x * i2.y) - (i1.y * i2.x);
	double e = (s1.x - s2.x) * (i1.y - i2.y);
	double f = (s1.y - s2.y) * (i1.x - i2.x);
	double ef = e - f;
	
	Point p;
	p.x = ((a * b_x) - (c_x * d)) / ef;
	p.y = ((a * b_y) - (c_y * d)) / ef;
	
	return p;
}

// returns a vector containing a sequence of points defining
// the intersection of two convex polygons poly1 and poly2
// Inputs: poly1 and poly2 - sequences of points defining the
//                           borders of convex polygons
vector<Point> getConvexIntersection(vector<Point>& poly1, vector<Point>& poly2) {
	vector<Point> ret = poly1;
	
	Point p1 = poly2.back();
	for(int i = 0; i < poly2.size(); i++) {
		Point p2 = poly2[i];
		vector<Point> temp = ret;
		ret.clear();
		Point p3;
		if(!temp.empty())
			p3 = temp.back();
		for(int j = 0; j < temp.size(); j++) {
			Point p4 = temp[j];
			if(inside(p4, p1, p2)) {
				if(!inside(p3, p1, p2))
					ret.push_back(computeIntersection(p3, p4, p1, p2));
				ret.push_back(p4);
			} else if (inside(p3, p1, p2)) {
				ret.push_back(computeIntersection(p3, p4, p1, p2));
			}
			p3 = p4;
		}
		p1 = p2;
	}
	return ret;
}