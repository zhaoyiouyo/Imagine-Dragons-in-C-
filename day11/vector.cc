#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main() {
    vector<int> nums1{ 1, 1, 1, 1, 1 };
    vector<int> nums2{ 2, 2, 2, 2, 2, 2, 2 };
    vector<int> nums3{ 3, 3, 3 };

    vector<vector<int>> v{ nums1, nums2, nums3 };
    for (auto &vec : v) {
        for (auto &num : vec) {
            cout << num << " ";
        }
    }
    cout << endl;
    return 0;
}
