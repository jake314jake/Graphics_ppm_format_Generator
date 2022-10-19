#include"JacobGraphicLib.h"

void test();
vector<Point> pts = { Point(10,10),Point(10,50),Point(30,90) };
int main(int argc,char** argv) {
	test();
	cout <<endl<< argv[0];
}
void test() {
	//creat PPMgenerator instance
	PPMgenerator ppmgen = PPMgenerator(100, 100, "test.ppm", ASCII );
	//set the back ground color to white (255)
	ppmgen.setBackGround(MaxVal);
	
	
	Shape Tri = Shape({ Point(10, 10), Point(10, 50), Point(30, 90) });
	cout << ppmgen.DrawShape(Tri);
	
	Translation translation = Translation(10, 10);
	Rotation rotation = Rotation(45);
	Scale scale = Scale(2, 2);
	Shape TriTrans = Shape(translation.TransShape(Tri.getPtsList()));
	Shape TriRot =Shape(scale.ScaleShape(Tri.getPtsList()));
	//ppmgen.EraseShape(Tri);
	cout << ppmgen.DrawShape(TriRot);
	
	ppmgen.closeImg();
	
}