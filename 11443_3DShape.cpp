#include <iostream>
#include <string>
namespace oj
{
	class Shape3D
	{	
		double volume;

	public:
		double getVolume();
	
	protected:
		void setVolume(double volume);
	};

	class Sphere : public Shape3D
	{
		double radius;
		double pi;
	
	public:
		Sphere(double, double);
	};

	class Cone : public Shape3D
	{
		double radius;
		double height;
		double pi;

	public:
		Cone(double, double, double);
	};

	class Cuboid : public Shape3D
	{
		double length;
		double width;
		double height;
	
	public:
		Cuboid(double, double, double);
	};

	class Cube : public Cuboid
	{
	public:
		Cube(double);
	};
}
//#include "function.h"
using namespace oj;
Sphere::Sphere(double r, double p) {
    if (r < 0 || p < 0) setVolume(0);
    else {
        radius = r;
        pi = p;
        setVolume(4.0 / 3.0 * pi * radius * radius * radius);
    }
}
Cone::Cone(double r, double h, double p) {
    if (r < 0 || h < 0 || p < 0) setVolume(0);
    else {
        radius = r;
        height = h;
        pi = p;
        setVolume(1.0 / 3.0 * pi * radius * radius * height);
    }
}
Cuboid::Cuboid(double l, double w, double h) {
    if (l < 0 || w < 0 || h < 0) setVolume(0);
    else {
        length = l;
        width = w;
        height = h;
        setVolume(length * width * height);
    }
}
Cube::Cube(double l) : Cuboid(l, l, l){}
//
using namespace std;

namespace oj
{   
    void Shape3D::setVolume(double v)
    {
        volume = v;
    }

    double Shape3D::getVolume()
    {
        return volume;
    }
}


int main(void)
{   
    //using namespace oj;

    string s;
    double a, b, c;
    double totalVolume = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Sphere") {
            cin >> a >> b;
            Sphere sphere(a, b);
            totalVolume += sphere.getVolume();
            //cout << "Ball: " << sphere.getVolume() << endl;
        }
        if(s == "Cone") {
            cin >> a >> b >> c;
            Cone cone(a, b, c);
            totalVolume += cone.getVolume();
            //cout << "Cone: " << cone.getVolume() << endl;
        }
        if(s == "Cuboid") {
            cin >> a >> b >> c;
            Cuboid cuboid(a, b, c);
            totalVolume += cuboid.getVolume();
            //cout << "Cuboid: " << cuboid.getVolume() << endl;
        }
        if(s == "Cube") {
            cin >> a;
            Cube cube(a);
            totalVolume += cube.getVolume();
            //cout << "Cube: " << cube.getVolume() << endl;
        }
    }

    cout << totalVolume << endl;

    return 0;
}