#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(){
    char a[200] = {0};
    cin.getline(a, 200, ' ');
    cout << a;

    return 0;
}
