#include <iostream>
using namespace std;

namespace swap{
    extern void swap(int &x, int &y);
}

int main(){
    using swap::swap;
    int a = 5;
    int b = 1;
    swap(a, b);
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

}
