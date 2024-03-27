#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Record{
    Record(const string &word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {}

    string _word;
    int _frequency;
};

bool operator<(const Record &lhs, const Record &rhs){
    return lhs._word < rhs._word;
}

class Dictionary{
public:
    Dictionary(int capacity){
        _dict.reserve(capacity);
    }

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

                insert(newWord);
            }
        }
        sort(_dict.begin(), _dict.end());
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

    void insert(const string &word){
        if(word == string()){
            return;
        }

        size_t idx = 0;
        for(; idx != _dict.size(); ++idx){
            if(word == _dict[idx]._word){
                ++_dict[idx]._frequency;
                break;
            }
        }

        if(idx == _dict.size()){
            _dict.push_back(Record(word, 1));
        }
    }

    void store(const string &filename){
        ofstream ofs(filename);
        if(!ofs){
            cout << "ofs open file fail" << endl;
            return;
        }

        for(size_t idx = 0; idx != _dict.size(); ++idx){
            ofs << _dict[idx]._word << " " << _dict[idx]._frequency << endl;
        }
        ofs.close();
    }

private:
    vector<Record> _dict;
};

int main(){
    Dictionary dict(10000);
    dict.read("china_daily.txt");
    dict.store("dictMap.dat");

    return 0;
}
