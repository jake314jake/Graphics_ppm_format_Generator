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
	type getX();;
	type getY();;
	type getZ();
	void swap(Point& point);
};
class RGBval {
	int R;
	int G;
	int B;
public:
	RGBval(int R, int G, int B);
	void setR(int R);;
	void setG(int G);;
	void setB(int B);;
	int getR();;
	int getG();;
	int getB();;
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
public:
	Shape(vector<Point> PtsList);
	int getShapePtsSize();
	Point getPointAt(int Index);
	vector<Point> getPtsList();
};
class PPMgenerator {
	int width;
	int height;
	string type;
	string url;
	byte* image_data;
	ofstream myImage;
public:
	PPMgenerator(int width, int height, string url, string type = "P3");
	void setBackGround(int backGroundVal);
	
	/* 
	* set the image array with a Value
	*/
	void  setByte(int Value);;
	// the image array size
	int getSize();;
	// open the image at spsfc url and return TRUE if done
	//&
	//close the image
	bool OpenImg();;
	void closeImg();;;
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
	/*
	* Check if invalid val &(width*height)||RGb
	*/
	bool OverFlow(Point point, RGBval rgb = RGBval(0, 0, 0));
	bool DrawPixel(Point point, RGBval rgb = RGBval(0, 0, 0));
	bool DrawLine(Point pointStart, Point pointEnd, RGBval rgb = RGBval(0, 0, 0));
	bool DrawTriangle(Point pointA, Point pointB, Point pointC, RGBval rgb = RGBval(0, 0, 0));
	bool DrawfShape(Shape shape, RGBval rgb = RGBval(255, 255, 0));
	// Draw a open and close path from a list of Points
	bool DrawPath(vector<Point> pts, RGBval rgb, bool isClose);
	// generate a random img
	bool randImg();
	bool isInTriangel(Point pts, Point a, Point b, Point c);
	bool fillTriangel(Point pointA, Point pointB, Point pointC, RGBval rgb = RGBval(0, 0, 0));

};

