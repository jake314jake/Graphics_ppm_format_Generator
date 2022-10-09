#include"JacobGraphicLib.h"

void test();
int main() {
	test();
}
void test() {
	//creat PPMgenerator instance
	PPMgenerator ppmgen = PPMgenerator(10, 10, "Line.ppm", ASCII );
	//set the back ground color to white (255)
	ppmgen.setBackGround(MaxVal);
	//draw a line
	cout << ppmgen.DrawLine(Point(0, 0), Point(9, 9), RGBval(255, 0, 0));
	ppmgen.closeImg();
	
}