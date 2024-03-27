#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class Circle{
public:
    Circle():_r(0){}

    Circle(double r):_r(r){}

    double getArea(){
        return M_PI * _r *_r;
    }

    double getPerimeter(){
        return 2 * M_PI * _r;
    }

    void show(){
        cout << "r = " << _r << endl;
        cout << "perimeter = " << getPerimeter() << endl;
        cout << "area = " << getArea() << endl;
    }
private:
    double _r;
};

class Cylinder
:public Circle
{
public:
    Cylinder(double r, double h)
    : Circle(r)
    , _h(h)
    {}
    
    double getVolume(){
        return getArea() * _h;
    }

    void showVolume(){
        cout << "volume : " << getVolume() << endl;
    }

private:
    double _h;
};

int main(){
    Circle c(5);
    c.show();

    Cylinder cl(5, 1);
    cl.showVolume();

    return 0;
}
