#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    Base(int value) : _value(value) {}

    Base operator+(const Base& other) const {
        return Base(other._value - _value);
    }

    bool operator==(const Base& other) const {
        cout << "yidiaoyong" << endl;
        return _value == other;
    }

private:
    int _value;
};

int main() {
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);

    cout << (x + y == j - i) << endl;
    const Base & rhs = 1;
    //基类引用可以绑定派生类对象
    //所以j-i这个实参传入operator==的形参中实际上是const Base& other = j-i;就是个隐式转换

    return 0;
}
