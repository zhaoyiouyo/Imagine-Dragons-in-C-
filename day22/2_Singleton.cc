#include <iostream>
using std::cout;
using std::endl;

class Singleton {
public:
    static Singleton &getInstance(){
        static Singleton s;

        return s;
    }

private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }

    ~Singleton(){
        cout << "~Singleton()" << endl;
    }

    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton& rhs) = delete;
};

void test0()
{
    Singleton &s1 = Singleton::getInstance();
    Singleton &s2 = Singleton::getInstance();
    cout << "&s1 = " << &s1 <<endl;
    cout << "&s2 = " << &s2 <<endl;
}

int main(void){
    test0();
    return 0;
}

