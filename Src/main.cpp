#include"JacobGraphicLib.h"

void test();
void test2();
vector<Point> pts = { Point(10,10),Point(10,50),Point(30,90) };
int main(int argc,char** argv) {
	test2();
	
	return 0;
}
void test() {
	//creat PPMgenerator instance
	PPMgenerator ppmgen = PPMgenerator(100, 100, "test.ppm", ASCII );
	//set the back ground color to white (255)
	ppmgen.setBackGround(MaxVal);
	Shape Tri = Shape({ Point(10, 10),Point(20, 10), Point(20, 20), Point(10, 20) });
	cout << ppmgen.DrawShape(Tri);
	Translation translation = Translation(20, 20);
	Rotation rotation = Rotation(45);
	//ppmgen.EraseShape(Tri);
	cout << ppmgen.DrawShape(translation.set(Tri));
	ppmgen.closeImg();
	
}
void test2() {
	PPMgenerator ppmgen = PPMgenerator(100, 100, "test.ppm", ASCII);
	ppmgen.setBackGround(MaxVal);
	Shape s = Shape({ Point(10, 10),Point(20, 10), Point(20, 20), Point(10, 20) });
	cout << ppmgen.DrawShape(s);
	ppmgen.fillShape(s, s.pointIn(), RGBval(255, 0, 0));
	Translation translation = Translation(20, 50);
	Rotation rotation = Rotation(90);
	//Scale scale = Scale(2, 2);
	//ppmgen.EraseShape(s,false);
	Shape s2 = translation.set(rotation.set(s));
	cout << ppmgen.DrawShape(s2);
	ppmgen.fillShape(s2, s2.pointIn(), RGBval(255, 0, 0));
	ppmgen.closeImg();
}