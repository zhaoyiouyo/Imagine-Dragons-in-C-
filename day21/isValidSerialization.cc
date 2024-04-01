#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  bool isValidSerialization(string preorder) {
    istringstream iss(preorder);
    string node;
    while (getline(iss, node, ',')) {

      if (node != "#") {
        _stack.push(node);
      } else {

        while (!(_stack.empty()) && _stack.top() == "#") {
          if (_stack.size() == 1 && _stack.top() == "#")
            return false;
          _stack.pop();
          _stack.pop();
        }
        _stack.push(node);
      }
    }
    if (iss.eof() && _stack.size() == 1 && _stack.top() == "#") {
      return true;
    } else {
      return false;
    }
  }

private:
  stack<string> _stack;
};
