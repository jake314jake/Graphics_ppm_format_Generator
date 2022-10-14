#include "JacobGraphicLib.h"

 Point::Point() {
	this->x = 0; this->y = 0; this->z = 0;
}

 Point::Point(type x, type y) {
	this->x = x; this->y = y; this->z = 0;
}

 Point::Point(type x, type y, type z) {
	Point(x, y);
	this->z = z;
}

 void Point::setX(type x)
{
	this->x = x;
}

 void Point::setY(type y)
{
	this->y = y;
}

 type Point::getX()
{
	return this->x;
}

 type Point::getY()
{
	return this->y;
}

 type Point::getZ() {
	return this->z;
}

 void Point::swap(Point& point) {
	Point tmp = Point(this->getX(), this->getY());
	this->setX(point.getX()); this->setY(point.getY());
	point.setX(tmp.getX()); point.setY(tmp.getY());
}

 RGBval::RGBval(int R, int G, int B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

 void RGBval::setR(int R)
{
	this->R = R;
}

 void RGBval::setG(int G) {
	this->G = G;
}

 void RGBval::setB(int B) {
	this->B = B;
}

 int RGBval::getR() {
	return this->R;
}

 int RGBval::getG() {
	return this->G;
}

 int RGBval::getB() {
	return this->B;
}

 PPMgenerator::PPMgenerator(int width, int height, string url, string type) {
	this->width = width;
	this->height = height;
	this->type = type;
	this->url = url;
	image_data = new byte[getSize()];
}

 void PPMgenerator::setBackGround(int backGroundVal) {
	if (OpenImg()) {
		setImgHeader();
		setByte(backGroundVal);
	}
}

/*
* set the image array with a Value
*/

 void PPMgenerator::setByte(int Value)
{
	if (Value > MaxVal || image_data == 0)
		return;
	memset(image_data, Value, getSize());
}

// the image array size

 int PPMgenerator::getSize()
{
	return width * height * RGB;
}

// open the image at spsfc url and return TRUE if done
//&
//close the image

 bool PPMgenerator::OpenImg()
{
	myImage.open(url);
	if (myImage.fail()) {
		cout << ErrMsg << " " << url << endl;
		return false;
	}
	return true;
}

 void PPMgenerator::closeImg() {
	writeImg();
	myImage.close();
}

/*
* set the Image Header
* >>type
* >>width height
* >>MaxVal
*/

 void PPMgenerator::setImgHeader() {

	myImage << type << " " << endl;
	myImage << width << " " << height << " " << endl;
	myImage << MaxVal << " " << endl;

}

/*
* write in the image file from the byte array
*/

 bool PPMgenerator::writeImg() {

	for (int i = 0; i < getSize(); i++) {
		int value = image_data[i];
		myImage << value << " " << endl;
	}

	return true;

}

/*
* set  byte Array with a RGB val
*/

 void PPMgenerator::setPixel(Point point, RGBval rgb)
{
	{

		Point tmp = Point((height - 1) - point.getY(), point.getX());
		int pixel = ((width * tmp.getX()) + tmp.getY()) * RGB;
		image_data[pixel] = rgb.getR();
		image_data[pixel + 1] = rgb.getG();
		image_data[pixel + 2] = rgb.getB();
	}
}


/*
* Check if invalid val &(width*height)||RGb
*/

 bool PPMgenerator::OverFlow(Point point, RGBval rgb) {
	if (
		point.getX() >= width ||
		point.getX() >= height ||
		rgb.getR() > MaxVal ||
		rgb.getG() > MaxVal ||
		rgb.getB() > MaxVal) return true;

	return false;
}

 bool PPMgenerator::DrawPixel(Point point, RGBval rgb) {

	if (OverFlow(point, rgb)) return false;
	setPixel(point, rgb);
	return true;


}

 bool PPMgenerator::DrawLine(Point pointStart, Point pointEnd, RGBval rgb) {
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
	int Dy = pointStart.getY() - pointEnd.getY();
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
			x += (float)1 / tangAlp;
		}
		return true;
	}
	else {
		DrawPixel(pointStart, rgb);
		return true;
	};
	return false;
}

 bool PPMgenerator::DrawTriangle(Point pointA, Point pointB, Point pointC, RGBval rgb) {
	return(
		DrawLine(pointA, pointB, rgb) &&
		DrawLine(pointB, pointC, rgb) &&
		DrawLine(pointA, pointC, rgb)
		);
}

 bool PPMgenerator::DrawfShape(Shape shape, RGBval rgb) {
	vector<Point> tmp = shape.getPtsList();
	return DrawPath(tmp, rgb, true);
}

// Draw a open and close path from a list of Points

 bool PPMgenerator::DrawPath(vector<Point> pts, RGBval rgb, bool isClose) {
	if (pts.size() == 0) return false;

	Point tmp = pts[0]; //1-2-3-4-5
	for (int i = 1; i < pts.size(); i++) {
		DrawLine(tmp, pts[i], rgb);
		tmp = pts[i];
	}
	if (isClose)
		DrawLine(pts[0], pts[pts.size() - 1], rgb);

	return true;
}

// generate a random img

 bool PPMgenerator::randImg() {
	srand(time(0));
	for (int i = 0; i<width; i++)
		for (int j = 0; j < height; j++)
		{

			setPixel(Point(i, j), RGBval(rand() % 255, rand() % 255, rand() % 255));
		}
	return true;
}

 bool PPMgenerator::isInTriangel(Point pts, Point a, Point b, Point c) {
	return (
		abs(Vector(a, b).Orientation(Vector(a, pts)) +
			Vector(b, c).Orientation(Vector(b, pts)) +
			Vector(c, a).Orientation(Vector(c, pts))) == 3
		);

}

 bool PPMgenerator::fillTriangel(Point pointA, Point pointB, Point pointC, RGBval rgb) {
	for (int i = 0; i<width; i++)
		for (int j = 0; j < height; j++) {

			Point tmp = Point(i, j);
			if (isInTriangel(tmp, pointA, pointB, pointC)) {
				DrawPixel(tmp, rgb);
			}
		}
	return true;
}

 Vector::Vector(type x, type y, type z) {
	this->x = x; this->y = y; this->z = z;
}

 Vector::Vector(Point startP, Point endP) {
	this->x = endP.getX() - startP.getX();
	this->y = endP.getY() - startP.getY();
	this->z = endP.getZ() - startP.getZ();
}

 type Vector::getX() {
	return this->x;
}

 type Vector::getY() {
	return this->y;
}

 type Vector::getZ() {
	return this->z;
}

// this.vectProduct(v) --->  this*v ---->( x,y,z )*(x',y',z')=()

 Vector Vector::vectProduct(Vector vector) {
	return Vector(this->getY() * vector.getZ() - this->getZ() * vector.getY(),
		-this->getX() * vector.getZ() + this->getZ() * vector.getX(),
		this->getX() * vector.getY() - this->getY() * vector.getX());
}

//GET THE z OF THIS VECTORIAL vector   

 type Vector::vectProductZ(Vector vector) {
	return (this->getX() * vector.getY() - this->getY() * vector.getX());
}

// Z UP OR DOWN

 int Vector::Orientation(Vector vector) {
	int tmp = vectProductZ(vector);
	if (!tmp) return tmp;
	return (vectProductZ(vector)) > 0 ? 1 : -1;
}

 Shape::Shape(vector<Point> PtsList) {
	if (!PtsList.empty()) {
		for (Point pts : PtsList) {
			this->PtsList.push_back(pts);
		}
	}
}

 int Shape::getShapePtsSize() {
	return PtsList.size();
}

 Point Shape::getPointAt(int Index) {
	return PtsList.at(Index % getShapePtsSize());
}

 vector<Point> Shape::getPtsList() {
	vector<Point> tmp;
	for (Point pts : this->PtsList) {
		tmp.push_back(pts);
	}
	return tmp;
}
