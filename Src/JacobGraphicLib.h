#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;
typedef unsigned char byte;
typedef int type;
#define RGB 3;
#define ErrMsg "Unable to create "
#define MaxVal 255
#define MinVal 0
#define ASCII "P3"
#define PI 	3.14159265358979323846
#define _NoOverFlow 0
#define _OverFloxXpos 1
#define _OverFloxXneg -1
#define _OverFloxYpos  2 
#define _OverFloxYneg -2
/*
* @2022
* this Lib WAS created for genrating  PPM files 
* PPM FILE STRUCT {
     type     // ex: ASCII ->>P3
	 WIDTH HEIGHT
	 MAX VAL
	 PIXEL0RED_VAL
	 PIXEL0GREEN_VAL
	 PIXEL0BLUE_VAL
	 PIXEL1RED_VAL
	 PIXEL1GREEN_VAL
	 PIXEL1BLUE_VAL
	 (...)
	 ---------------
	 |W|W|W|
	 |R|G|B|   // W:WHITE -- R:RED --G:GREEN -- B:BLUE
	 |W|W|W|
  PPM FILE WOULD BE LIKE:
  >>TEST.ppm
	   ************************************************
	  * P3     // HEADER FILE BGN                     *
	  * 3 3                                           *
	  * 255   // HEADER FILE END
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 0
	  * 0
	  * 255
	  * 0
	  * 255
	  * 0
	  * 255
	  * 0
	  * 0
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  * 255
	  ************************************************

  }
*/
class Point {
	type x;
	type y;
	type z;
public:
	Point();
	Point(type x, type y);
	Point(type x, type y, type z);
	void setX(type x);;
	void setY(type y);;
	void setZ(type z);
	type getX();
	type getY();
	type getZ();
	void swap(Point& point);
};
class RGBval {
	int R;
	int G;
	int B;
public:
	RGBval(int R, int G, int B);
	void setR(int R);
	void setG(int G);
	void setB(int B);
	int getR();
	int getG();
	int getB();
	bool isEqual(RGBval rgb) {
		
		return (
			   R == rgb.getR()
			&& G == rgb.getG()
			&& B == rgb.getB()
			);
	}
};
class Vector {
	type x, y, z;
public:
	Vector(type x, type y, type z);
	Vector(Point startP, Point endP);
	type getX();
	type getY();
	type getZ();
	// this.vectProduct(v) --->  this*v ---->( x,y,z )*(x',y',z')=()
	Vector vectProduct(Vector vector);
	//GET THE z OF THIS VECTORIAL vector   
	type vectProductZ(Vector vector);
	// Z UP OR DOWN
	int Orientation(Vector vector);
};
class Shape {
protected:
	vector<Point> PtsList;
	RGBval Boundary_color = RGBval(100, 100, 100);
public:
	Shape(vector<Point> PtsList);
	int getShapePtsSize();
	Point getPointAt(int Index);
	vector<Point> getPtsList();
	void setBoundary_color(RGBval Boundary_color = RGBval(255, 255, 0)) {
		this->Boundary_color = Boundary_color;
	}
	RGBval getBoundary_color() {
		return this->Boundary_color;
	}
	type minX() {
		type minX = PtsList.at(0).getX();
		for (Point pts : PtsList) {
			if (pts.getX() < minX){
			minX = pts.getX();
          }
		}
		return minX;
	}
	type maxX() {
		type maxX = PtsList.at(0).getX();
		for (Point pts : PtsList) {
			if (pts.getX() > maxX) {
				maxX = pts.getX();
			}
		}
		return maxX;
	}
	type minY() {
		type minY = PtsList.at(0).getY();
		for (Point pts : PtsList) {
			if (pts.getY() < minY) {
				minY = pts.getY();
			}
		}
		return minY;
	}
	type maxY() {
		type maxY = PtsList.at(0).getY();
		for (Point pts : PtsList) {
			if (pts.getY() > maxY) {
				maxY = pts.getY();
			}
		}
		return maxY;
	}
	Point pointIn() {
		return Point((minX() + maxX()) / 2, (minY() + maxY()) / 2);
	}
};
class Transformation {
protected:
	 int Base = 3;
	vector < vector<float>> _Matrix;
	Transformation();
	void loadIden();
public:
	virtual Shape set(Shape shape) = 0;
	
};
class Translation :Transformation {
private:
	type xMove, yMove;
	Shape TransShape(Shape shape);
	Point TransPoint(Point pts);
public:
	Translation(int xMove, int yMove);
	type getxMove();
	type getyMove();
	Shape set(Shape shape);
};
class Rotation :Transformation {
/// <summary>
///  pi ----> 180
///  alpHa -----> n
/// </summary>
private:
	float aLpha;
	Point RotPoint(Point pts);
	Shape RotShape(Shape shape);
public:
	Rotation(type aLpha);
	float getaLpha();
	float getRADaLpha();
	

	Shape set(Shape shape);

};
class Scale : Transformation{
private:

	float xScale, yScale;
	Point ScalePoint(Point pts);
	Shape ScaleShape(Shape shape) {
		vector <Point> newShapePts;
		vector <Point> ShapePts = shape.getPtsList();
		for (Point pts : ShapePts) {

			newShapePts.push_back(ScalePoint(pts));
		}
		return Shape(newShapePts);
	};
public:
	Scale(float xScale, float yScale):Transformation() {
		this->xScale = xScale; this->yScale = yScale;
		_Matrix.at(0).at(0) = xScale;
		_Matrix.at(1).at(1) = yScale;
	}
	float getxScale() {
		return this->xScale;
	};
	float getyScale() {
		return this->yScale;
	};
	
	Shape set(Shape shape) {
		return ScaleShape(shape);
	}

};
class PPMgenerator {
	int width;
	int height;
	string type;
	string url;
	byte* image_data;
	ofstream myImage;
	int backGroundVal;
public:
	PPMgenerator(int width, int height, string url, string type = "P3");
	void setBackGround(int backGroundVal);
	void setLocation(string url);
	/* 
	* set the image array with a Value
	*/
	void  setByte(int Value);
	// the image array size
	int getSize();;
	// open the image at spsfc url and return TRUE if done
	//&
	//close the image
	bool OpenImg();;
	void closeImg();
	/*
	* set the Image Header 
	* >>type
	* >>width height
	* >>MaxVal
	*/
	void setImgHeader();
	/*
	* write in the image file from the byte array
	*/
	bool writeImg();;
	/*
	* test if the parm greater than MaxVal
	*/
	
	/*
	* set  byte Array with a RGB val 
	*/
	void setPixel(Point point, RGBval rgb);;
	RGBval getPixel(Point point);
	/*
	* Check if invalid val &(width*height)||RGb
	*/
	int OverFlow(Point point);
	
	bool DrawPixel(Point point, RGBval rgb = RGBval(0, 0, 0));
	bool DrawLine(Point pointStart, Point pointEnd, RGBval rgb = RGBval(0, 0, 0));
	bool DrawTriangle(Point pointA, Point pointB, Point pointC, RGBval rgb = RGBval(0, 0, 0));
	bool DrawPath(vector<Point> pts, RGBval rgb, bool isClose);
	bool DrawShape(Shape shape);
	bool DrawShape(Shape shape, RGBval rgb );
	bool EraseShape(Shape shape,bool isEmpty = true);
	
	// Draw a open and close path from a list of Points
	
	// generate a random img
	bool randImg();
	bool isInTriangel(Point pts, Point a, Point b, Point c);
	bool fillTriangel(Point pointA, Point pointB, Point pointC, RGBval rgb = RGBval(0, 0, 0));
	void fillShape(Shape shape, Point pts, RGBval fill_color) {
		if(!shape.getBoundary_color().isEqual(getPixel(pts)) &&
			! fill_color.isEqual(getPixel(pts)) ) {
			setPixel(pts, fill_color);
			fillShape(shape, Point(pts.getX()+1,pts.getY()), fill_color);
			fillShape(shape, Point(pts.getX()-1, pts.getY()), fill_color);
			fillShape(shape, Point(pts.getX(), pts.getY()+1), fill_color);
			fillShape(shape, Point(pts.getX(), pts.getY()-1), fill_color);
		}
		return;
	}
	};


