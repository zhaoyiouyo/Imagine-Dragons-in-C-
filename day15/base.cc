#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    Base(long base)
        : _base(base)
    { 
        /* cout << "Base()" << endl; */ 
    }

    void display() const{
        cout << "_base:" << _base << endl;
    }

    ~Base(){ 
        /* cout << "~Base()" << endl; */ 
    }

    long _base = 10;
};


class Derived
: public Base 
{
public:
    Derived(long base,long derived)
        : Base(base)//显式调用基类的构造函数
          , _derived(derived)
    { 
        /* cout << "Derived(long)" << endl; */
    }

    ~Derived(){ 
        /* cout << "~Derived()" << endl; */ 
    }

#if 0
    Derived(const Derived & rhs)
    : Base(rhs) //显式调用Base的拷贝构造
    , _derived(rhs._derived)
    { cout << "Derived(const Derived &)" << endl; }


    Derived & operator=(const Derived & rhs){
        //需要显式调用Base的赋值运算符函数
        Base::operator=(rhs);
        _derived = rhs._derived;
        cout << "Derived& operator=(const Derived&)" << endl;
        return *this;
    }
#endif

    void display() const{
        Base::display();
        cout << "_derived:" << _derived << endl; 
    }

    long _derived;
};

void test0(){
    Derived d1(2,3);
    Derived d2(7,8);
    Derived d3 = d2;
    d3.display();

    cout << endl;
    d2 = d1;
    d2.display();
}


int main(void){
    test0();
    return 0;
}
