#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bracket{
public:
    Bracket(string str)
    : _str(str)
    {}

    bool match(){
        for(int i = 0; i < _str.size(); ++i){
            if((_str[i] == '(') || (_str[i] == '[') || (_str[i] == '{')){
                _vec.push_back(_str[i]);
            }
            if(_str[i] == ')' && _vec.back() != '('){
                return false;
            }
            else if(_str[i] == ']' && _vec.back() != '['){
                return false;
            }
            else if(_str[i] == '}' && _vec.back() != '{'){
                return false;
            }
            _vec.pop_back();
        }
        return true;
    }

private:
    string _str;
    vector<char> _vec;
};

int main(){
    string str;
    Bracket bra("({}[]");
    if(bra.match()){
        cout << "匹配成功" << endl;
    }
    else{
        cout << "语法错误" << endl;
    }

    return 0;
}
