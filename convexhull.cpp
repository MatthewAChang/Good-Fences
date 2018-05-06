#include "convexhull.h"

// uses a sorting algorithm of your choice (must be fully implemented by you)
// to sort the points in v to satisfy the following criteria:
// 1. v[0] must contain the point with the smallest y-coordinate.
//      If multiple points have the same smallest y-coordinate, v[0]
//      must contain the one among those with the smallest x-coordinate.
// 2. The remaining indices i contain the points, sorted in increasing order
//      by the angle that the point forms with v[0] and the x-axis. That is,
// 	one of the legs of the angle is represened by the line through v[0] and
//	v[i], and the other is the x-axis.
void sortByAngle(vector<Point>& v) {
	for(int i = 1; i < v.size(); i++) {
		if(v[0].y > v[i].y || (v[0].y == v[i].y && v[0].x > v[i].x)) {
			swap(v, 0, i);
		}
	}
	insertionSort(v);
}

// determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
bool ccw(Point p1, Point p2, Point p3) {
	double crossProduct = ((p2.x - p1.x) * (p3.y - p1.y)) - ((p2.y - p1.y) * (p3.x - p1.x));
	if(crossProduct >= 0) return true;
	return false;
}

// returns a vector of points representing the convex hull of v
// if c is the vector representing the convex hull, then c[k], c[k+1]
// is an edge in the convex hull, for all k in 0 to n-1, where n is the
// number of points in the hull. c[n-1],c[0] is also an edge in the hull.
// The returned vector should be a subset of v
// Input: v - a vector of points in arbitrary order
vector<Point> getConvexHull(vector<Point>& v) {
	sortByAngle(v);

	Stack s;
	vector<Point> ret;
	s.push(v[0]);
	for(int i = v.size() - 1; i > 0; i--)
		s.push(v[i]);
	
	while(!s.isEmpty()) {
		if(ret.empty())
			ret.push_back(s.pop());
		
		Point p = s.pop();
		
		if(s.isEmpty()) {
			ret.push_back(p);
		} else if(ccw(ret.back(), p, s.peek())) {
			ret.push_back(p);
		} else {
			if(!ret.empty()) {
				s.push(ret.back());
				ret.pop_back();
			}
		}
	}
	return ret;
}

// sorts the vector from index 1 to size - 1 by its slope
// using insertion sort
void insertionSort(vector<Point>& v) {
	int i = 2;
	while(i < v.size()) {
		int j = i;
		double slope_curr = (v[j].y - v[0].y) / (v[j].x - v[0].x);
		double slope_prev = (v[j - 1].y - v[0].y) / (v[j - 1].x - v[0].x);
		while(j > 1 && compare(slope_curr, slope_prev)) {
			swap(v, j, j - 1);
			j--;
			slope_curr = (v[j].y - v[0].y) / (v[j].x - v[0].x);
			slope_prev = (v[j - 1].y - v[0].y) / (v[j - 1].x - v[0].x);
		}
		i++;
	}
}

// compares two slopes
bool compare(double slope_curr, double slope_prev) {
	if(slope_curr >= 0 && slope_prev < 0)
		return true;
	else if(slope_curr < 0 && slope_prev >= 0)
		return false;
	else return slope_prev > slope_curr;
}

// swaps two elements of v at index i and j
void swap(vector<Point>& v, int i, int j) {
	Point t = v[i];
	v[i] = v[j];
	v[j] = t;
}