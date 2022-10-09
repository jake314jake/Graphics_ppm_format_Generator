#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef unsigned char byte;
#define RGB 3;
#define ErrMsg "Unable to create "
#define MaxVal 255
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
	int x;
	int y;
public:
	Point(int x, int y) {
		this->x = x; this->y = y;
	}
	void setX(int x)
	{
		this->x = x;
	};
	void setY(int y)
	{
		this->y = y;
	};
	int getX()
	{
		return this->x;
	};
	int getY()
	{
		return this->y;
	};
	void swap(Point &point) {
		Point tmp = Point(this->getX(), this->getY());
		this->setX(point.getX()); this->setY(point.getY());
		point.setX(tmp.getX()); point.setY(tmp.getY());
	}
};
class RGBval {
	int R;
	int G;
	int B;
public:
	RGBval(int R, int G, int B) {
		this->R = R;
		this->G = G;
		this->B = B;
	}
	void setR(int R)
	{
		this->R = R;
	};
	void setG(int G) {
		this->G = G;
	};
	void setB(int B) {
		this->B = B;
	};
	int getR() {
		return this->R;
	};
	int getG() {
		return this->G;
	};
	int getB() {
		return this->B;
	};
};
class PPMgenerator {
	int width;
	int height;
	string type;
	string url;
	byte* image_data;
	ofstream myImage;
public:
	PPMgenerator(int width, int height, string url,string type = "P3") {
		this->width = width;
		this->height = height;
		this->type = type;
		this->url = url;
		image_data = new byte[ getSize()];
	}
	void setBackGround(int backGroundVal) {
		if (OpenImg()) {
		setImgHeader();
		setByte(backGroundVal);
	}
	}
	
	/* 
	* set the image array with a Value
	*/
	void  setByte(int Value)
	{
		if (Value > MaxVal || image_data == 0)
			return;
		memset(image_data, Value, getSize());
	};
	// the image array size
	int getSize()
	{
		return width * height * RGB;
	};
	// open the image at spsfc url and return TRUE if done
	//&
	//close the image
	bool OpenImg()
	{
		myImage.open(url);
		if (myImage.fail()) {
			cout << ErrMsg << " " << url << endl;
			return false;
		}
		return true;
	};
	void closeImg() {
		writeImg();
		myImage.close();
	};;
	/*
	* set the Image Header 
	* >>type
	* >>width height
	* >>MaxVal
	*/
	void setImgHeader() {
		
		myImage << type <<" "<< endl;
		myImage << width << " " << height <<" " <<endl;
		myImage << MaxVal << " "<<endl;
		
	}
	/*
	* write in the image file from the byte array
	*/
	bool writeImg() {
		
			for (int i = 0; i < getSize(); i++) {
				int value = image_data[i];
				myImage << value << " " << endl;
			}
			
			return true;
		
	};
	/*
	* test if the parm greater than MaxVal
	*/
	
	/*
	* set  byte Array with a RGB val 
	*/
	void setPixel(Point point, RGBval rgb)
	{
		{
			
			Point tmp = Point((height - 1) - point.getY(),point.getX());
			int pixel = ((width * tmp.getX() )+ tmp.getY()) * RGB;
			image_data[pixel] = rgb.getR();
			image_data[pixel + 1] = rgb.getG(); 
			image_data[pixel + 2] = rgb.getB();
		}
	};
	/*
	* Check if invalid val &(width*height)||RGb
	*/
	bool OverFlow(Point point, RGBval rgb = RGBval(0, 0, 0)) {
		if (
			point.getX() >= width ||
			point.getX() >= height ||
			rgb.getR() > MaxVal ||
			rgb.getG() > MaxVal ||
			rgb.getB() > MaxVal) return true;

		return false;
	}
	bool DrawPixel(Point point, RGBval rgb= RGBval(0, 0, 0)) {
		
		if (OverFlow(point, rgb)) return false;
			setPixel(point, rgb);
			return true;
		
		
	}
	bool DrawLine(Point pointStart, Point pointEnd, RGBval rgb=RGBval(0,0,0)) {
		if (OverFlow(pointStart, rgb) || OverFlow(pointEnd)) return false;
		
		/* Possible Lines after swap && overrflow control
		* case 1: if (Y_Start - Y_End) == 0 >> tangAlpha==0
		*    Start*************End   
		*case 2: if (X_Start - X_End) == 0 >> tangAlpha== INFN
		*        End*
		*           *
		*           *
		*           *
		*           *
		*     Start *
		* case 3: tangAlpha > 0
		*                   *End          yi - y_Start
		*                 *            a=-----------   
		*              *                  xi - x_Start            
		*           *                  yi=(xi - x_Start)*a + y_Start   
		*    Start*                    yi=i*a + y_Start
		* case 3: tangAlpha < 0        also:
		*                               xi=(yi - y_Start)/a + x_Start   
		*                               xi=i/a +x_Start 
		*      Start*
		*             *                
		*               * 
		*                 *
		*                   *End
		* 
		*/
		int Dx = pointStart.getX() - pointEnd.getX();
		int Dy = pointStart.getY() - pointEnd.getY() ;
		if (!Dx) {
			if (pointStart.getY() > pointEnd.getY()) pointStart.swap(pointEnd);
			for (int i = pointStart.getY(); i <= pointEnd.getY(); i++) {
				DrawPixel(Point(pointStart.getX(), i), rgb);
			}
			return true;
		}
		if (!Dy) {
			if (pointStart.getX() > pointEnd.getX()) pointStart.swap(pointEnd);
			for (int i = pointStart.getX(); i <= pointEnd.getX(); i++) {
				DrawPixel(Point(i, pointStart.getY()), rgb);
			}
			return true;
		}
		
		
		
		float tangAlp = float(Dy) / (Dx);
		Dx = abs(Dx);
		Dy = abs(Dy);
		//this give us a wide range in Dx
		if (Dx >= Dy) {
			
			if (pointStart.getX() > pointEnd.getX()) pointStart.swap(pointEnd);
			float y = (float)pointStart.getY();
			for (int i = pointStart.getX(); i <= pointEnd.getX(); i++) {
				DrawPixel(Point(i, y), rgb);
				y += tangAlp;

			}
			return true;
		}
		//this give us a wide range in Dy
		else if (Dx < Dy) {
			
			if (pointStart.getY() > pointEnd.getY())  pointStart.swap(pointEnd);
			float x = (float)pointStart.getX();
			for (int i = pointStart.getY(); i <= pointEnd.getY(); i++) {
				DrawPixel(Point(x, i), rgb);
				x += (float) 1 / tangAlp;
			}
			return true;
		}
		else {
			DrawPixel(pointStart, rgb);
			return true;
		};
		return false;
	}
	bool DrawTriangle(Point pointA, Point pointB, Point pointC, RGBval rgb = RGBval(0, 0, 0)) {
		return(
			DrawLine(pointA, pointB, rgb) &&
			DrawLine(pointB, pointC, rgb) &&
			DrawLine(pointA, pointC, rgb)
			);
	}
	// generate a random img
	bool randImg() {
		srand(time(0));
		for(int i=0;i<width;i++)
			for (int j = 0; j < height; j++)
			{
				
				setPixel(Point(i, j), RGBval(rand() % 255, rand() % 255, rand() % 255));
			}
		return true;
	}
	
	
};
