#include <iostream>

using std::cout;
using std::endl;
using std::cin;  

int main(int argc, char** argv)
{
int x;
cin >> x;
if(x++ > 5)
{
cout << x << endl;
}
else
{
cout << x-- << endl;
}

return 0;
}
