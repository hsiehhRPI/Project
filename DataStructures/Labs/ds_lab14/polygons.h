#ifndef __polygons_h_
#define __polygons_h_

#include<iostream>
#include <string>
#include <vector>

#include "utilities.h"

//We will be making these few classes: 
//polygon, triangle, quadrilateral, isosceles triangle, equilateral triangle, rectangle, and square

class Polygon {
public:
	Polygon (const std::string &name, const std::vector<Point> &points) : shapeN(name), pointInShape(points){
		//Unless the points given is less than 3, we should be able to construct a polygon
		if (points.size() < 3) {
			throw 8;
		}
	}
	std::string getName() const {return shapeN;}
	virtual bool HasAllEqualSides() {
		double x = DistanceBetween(pointInShape[0], pointInShape[pointInShape.size()-1]);
		for (int i = 0; i < pointInShape.size()-1; i++) {
			double y = DistanceBetween (pointInShape[i], pointInShape[i+1]);
			if (EqualSides(x,y)==false){
				return false;
			}
		}
		return true;
	}

protected:
	std::string shapeN;
	std::vector<Point> pointInShape;
	bool sameSides;
};
class Triangle : public Polygon {
public:
	Triangle(const std::string &name, const std::vector<Point> &points) : Polygon(name, points){
		if (points.size()!=3) {
			throw 8;
		}
	}
};
class IsoscelesTriangle : public virtual Triangle {
public: 
	IsoscelesTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name,points) {
		if (points.size()!=3) {
			throw 8;
		}
		double d1 = DistanceBetween(points[0], points[1]);
		double d2 = DistanceBetween(points[1], points[2]);
		double d3 = DistanceBetween(points[2], points[0]);
		if (d1 == d2 || d2 == d3 || d1 == d3) {
		}
		else {
			throw 9;
		}
	}	
};
class RightTriangle : public virtual Triangle {
public:
	RightTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name, points) {
		if (points.size()!=3) {
			throw 8;
		}
		std::vector<double> angles;
		double ang1 = Angle(points[0], points[1], points[2]);
		double ang2 = Angle(points[1], points[2], points[0]);
		double ang3 = Angle(points[2], points[1], points[0]);
		angles.push_back(ang1);
		angles.push_back(ang2);
		angles.push_back(ang3);
		int rightAngle = 0;
		for (int n = 0; n < angle.size(); n++) {
			if (RightAngle(angles[n])==true) {
				rightAngle++;
			}
		}
		if (rightAngle == 0) {
			throw 3;
		}
	}
};

class IsoscelesRightTriangle : public RightTriangle, public IsoscelesTriangle {
public:
	IsoscelesRightTriangle(const std::string &name, const std::vector<Point> &points) {
	}
}

class EquilateralTriangle : public IsoscelesTriangle {
public: 
	EquilateralTriangle(const std::string &name, const std::vector<Point> &points) : IsoscelesTriangle(name, points){
		if (points.size()!=3) {
			throw 8;
		}
		if (HasAllEqualSides()==false) {
			throw 9;
		}
	}
};	
class Quadrilateral : public Polygon {
public:
	Quadrilateral(const std::string &name, const std::vector<Point> &points) : Polygon(name,points) {
		if (points.size()!=4) {
			throw 8;
		}
	}
};

class Rectangle : public Quadrilateral {
public:
	Rectangle(const std::string &name, const std::vector<Point> &points):Quadrilateral(name,points) {
		if (points.size()!=4) {
			throw 8;
		}
		std::vector<std::vector<double>> lenInfo;
		std::vector<int> pointHold;
		double maxDiff = 0;
		for (int n = 1; n < points.size(); n++) {
			double dis = DistanceBetween(points[0], points[n]);
			if (dis > maxDiff) {
				maxDiff = dis;
				pointHold.push_back(0);
				pointHold.push_back(n);
			}
		}
		int countDiag = 1;

		//If we can find the same diagonal from two different points, it is a rectangle
		for (int x = 1; x < points.size(); x++) {
			for (int y = 0; y < points.size(); y++) {
				double t = DistanceBetween(points[x], points[y]);
				if (t == maxDiff) {
					countDiag++;
				}
			}
		}
		if (countDiag!=4) {
			throw 8;
		}
	}

protected:
};
class Square : public Rectangle {
public:
	Square(const std::string &name, const std::vector<Point> &points):Rectangle(name, points) {
		if (points.size()!=4) {
			throw 8;
		}
		if (HasAllEqualSides()==false) {
			throw 9;
		}
	}
};


#endif