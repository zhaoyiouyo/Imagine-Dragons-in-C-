#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base(int x): _x(x){}
    friend int operator+(const Base &x, const Base &y);
private:
    int _x;
};

int operator+(const Base &x, const Base &y){
    return (y._x - x._x);
}

int main(){
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x + y == j - i) << endl;

    return 0;
}
