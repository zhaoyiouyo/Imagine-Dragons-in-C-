#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size);
    void heapAdjust(size_t ,size_t);
    void sort();
    void print(){
        for(auto &elem: _vec){
            cout << elem << " ";
        }
        cout << endl;
    }
private:
    vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size)
: _vec(arr, arr + size)
{}

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t n, size_t noleafnode){
    int max_min = noleafnode;
    int left = 2 * noleafnode + 1;
    int right = 2 * noleafnode + 2;

    if(left < n && !_cmp(_vec[left], _vec[max_min])){
        max_min = left;
    }

    if(right < n && !_cmp(_vec[right], _vec[max_min])){
        max_min = right;
    }

    if(max_min != noleafnode){
        swap(_vec[noleafnode], _vec[max_min]);
        heapAdjust(n, max_min);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort(){
    int n = _vec.size();

    for(int i = n / 2 - 1; i >= 0; i--){
        heapAdjust(n, i);
    }

    for(int i = n - 1; i > 0; i--){
        swap(_vec[0], _vec[i]);
        heapAdjust(i, 0);
    }
}

int main(){
    int arr[] = {3, 2, 1, 6, 4, 9, 5, 8, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    HeapSort<int> heap(arr, n);
    heap.print();
    heap.sort();
    heap.print();

    return 0;
}
