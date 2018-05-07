# Good-Fences

Good Fences is a program that I created for CPSC 221: Basic Algorithms and Data Structures at UBC. The program creates a convex hull around a set of points that is taken from a text file and draws the convex hull and points on a PNG. The program implements Graham's Scan to create the convex hull and also implements the Sutherland-Hodgman algorithm to create another convex hull around the area where two sets of points intersect. The program implements the two algorithms using vectors and a stack class made of vectors.

Currently in main.cpp, the set of points are stored in the "points" folder and the output images are stored in the "images" folder but a user must update the main.cpp file to use different locations for receiving points and where the output image is stored.
