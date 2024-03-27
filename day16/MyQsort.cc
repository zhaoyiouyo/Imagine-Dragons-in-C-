#include <iostream>
#include <vector>

using namespace std;

template<typename T,typename Compare = less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare com);

    void print();

private:
    void quick(int left, int right, Compare &com);

    int partition(int left, int right, Compare &com);

private:
    vector<T> _vec;
};

template<typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com)
: _vec(arr, arr + size)
{
    quick(0, size - 1, com);    
}

template<typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare &com){
    if(left < right){
        int pivot = partition(left, right, com);
        quick(left, pivot - 1, com);
        quick(pivot + 1, right, com);
    }
}

template<typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com){
    T pivot = _vec[right];
    int i = left - 1;
    //int i = left;
    for(int j = left; j < right; ++j){
        if(com(_vec[j], pivot)){
            i++;
            swap(_vec[i], _vec[j]);
            //i++;
        }
    }
    //swap(_vec[i], _vec[right]);
    swap(_vec[i + 1], _vec[right]);
    //return i;
    return i + 1;
}

template<typename T, typename Compare>
void MyQsort<T, Compare>::print(){
    for(auto &elem: _vec){
        cout << elem << " ";
    }
    cout << endl;
}

int main(){
    int arr[] = {5, 2, 7, 3, 1, 8, 9, 4, 6, 10};
    size_t size = sizeof(arr)/sizeof(arr[0]);

    less<int> com;
    MyQsort<int> qsort(arr, size, com);
    qsort.print();

    return 0;
}
