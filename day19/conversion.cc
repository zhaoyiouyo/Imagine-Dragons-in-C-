#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Conversion{
public:
    void read(const string &rule, const string &text){
        ifstream ifs(rule);
        if(!ifs){
            cerr << "ifs open file fail" << endl;
            return;
        }

        //将规则文件读到map容器里
        string line;
        string value;
        while(getline(ifs, line)){
            istringstream iss(line);        
            string word;
            iss >> word;//输入流可以直接读到word里，同时iss偏移到第一个空格处
            getline(iss, value);//在对其使用getline就可以把这一行的后半部分读到value里边
            if(value.size() > 1){
                _map[word] = value.substr(1);
            }
            else{
                cerr << "no rule for " << word << endl;
            }
        }
        ifs.close();

        //将text文件中的单词按map容器key值匹配，转换成对应的字符串
        ifstream ifs1(text);
        if(!ifs1){
            cerr << "ifs1 open file fail" << endl;
            return;
        }
        while(getline(ifs1, line)){
            istringstream iss(line);
            string word;
            while(iss >> word){
                if(_map.find(word) != _map.end()){
                    cout << _map[word] << " ";
                }
                else{
                    cout << word << " ";
                }
            }
            cout << endl;
        }
        ifs1.close();
    }

private:
    map<string, string> _map;    
};

int main(){
    Conversion con;
    con.read("rule.txt", "file.txt");

    return 0;
}
