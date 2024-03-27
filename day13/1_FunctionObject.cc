#include <iostream>
using std::cout;
using std::endl;

class FunctionObject{
public:
    int operator()(){
        cout << "int operator()()" << endl;
        ++_cnt;
        return 1;
    }

}
