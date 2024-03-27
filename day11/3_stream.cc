#include <string>
#include <limits>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::istream;


void checkStreamStatus(istream & is){
    cout << is.good() << endl;
    cout << is.bad() << endl;
    cout << is.fail() << endl;
    cout << is.eof() << endl;
}


void test0(){
    int num = 10;
    cout << endl;
    cin >> num;
    cin.clear();
    cin >> num;
    cin.clear();
    cin >> num;
    cin.clear();
    string str;
    cin >> str;
    cout << str << endl;
    cin >> str;
    cout << str << endl;
    cin >> str;
    cout << str << endl;

    //没有进行正常输入，会将num设为0
    
}

int main(void){
    test0();
    return 0;
}
