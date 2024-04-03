#include <iostream>
using std::cout;
using std::endl;

class Singleton {
public:
    static Singleton * getInstance(){
        if(_pInstance == nullptr){
            _pInstance  = new Singleton();
        }
        return _pInstance;
    }


    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
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

private:
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = nullptr;

void test0()
{
    Singleton  *ps1 =  Singleton::getInstance();
    Singleton  *ps2 =  Singleton::getInstance();
    cout << "ps1 = " << ps1 << endl;
    cout << "ps2 = " << ps2 << endl;
}

int main(void){
    test0();
    return 0;
}

