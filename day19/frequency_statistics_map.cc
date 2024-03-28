#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Dictionary{
public:
    void read(const string &filename){
        ifstream ifs(filename);
        if(!ifs){
            cerr << "ifs open file fail" << endl;
            return;
        }
        string line;
        while(getline(ifs, line)){
            string word;
            istringstream iss(line);
            while(iss >> word){
                string newWord = dealWord(word);

                if(newWord != string()){
                    ++_unordered_map[newWord];
                }
            }
        }
        ifs.close();
    }

    string dealWord(string &word){
        for(int idx = 0; idx != word.size(); ++idx){
            if(!isalpha(word[idx])){
                return string();
            }
            else if(isupper(word[idx])){
                word[idx] = tolower(word[idx]);
            }
        }
        return word;
    }

    void store(const string &filename){
        ofstream ofs(filename);
        if(!ofs){
            cout << "ofs open file fail" << endl;
            return;
        }

        for(pair<string, int> elem: _unordered_map){
            ofs << elem.first << " " << elem.second << endl;
        }

        //unordered_map<string, int>::iterator it = _unordered_map.begin();
        //for(; it != _unordered_map.end(); ++it){
        //    ofs << it->first << " " << it->second << endl;
        //}
        ofs.close();
    }

private:
    unordered_map<string, int> _unordered_map;    
};

int main(){
    Dictionary dict;
    dict.read("china_daily.txt");
    dict.store("dictunordered_map.dat");

    return 0;
}
