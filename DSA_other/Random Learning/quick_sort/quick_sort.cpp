#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int index_of_element(vector<int> vector, int a) {
    int len = vector.size();
    for (int i = 0; i < len; i++) {
        if (vector[i] == a) return i;
    }
    return -1;
}

void swap(vector<int> &vector, int a, int b) {
    int t = vector[a];
    vector[a] = vector[b];
    vector[b] = t;
}

int partition(vector<int>& vector, int a, int b) {
    int pivot;
    if (vector.size() == 1)  pivot = vector[0];
    else if (vector.size() == 2)  pivot = vector[1];
    else  pivot = max(min(vector[a], vector[(a + b) / 2]), min(max(vector[a], vector[(a + b) / 2]), vector[b]));
    int count = 0;
    for (int i = a; i <= b;i++ ) {
        if (pivot >= vector[i]) count++;
    }

    swap(vector, index_of_element(vector, pivot), a + count-1);
    int index_of_pivot = a + count - 1;
    int i = a; int j = b;
    while (i< index_of_pivot && j> index_of_pivot) {
        while (vector[i] <= pivot)i++;
        while (vector[j] >= pivot)j--;

        if (i<j) swap(vector, i, j);
    }
    return index_of_pivot;
}

void quick_sort(vector<int> &vector, int a, int b) {
    
        if (a < b) {

            int p = partition(vector, a, b); 
            if (p!=0){
                quick_sort(vector, a, p - 1);
                quick_sort(vector, p + 1, b);
            }
            
        }
}
// it has some errors so preferably keep first elemnt in unsorted vector large


int main() {
    vector<int> unsorted = { 200,7,1,19,14,20,34,6,7,1,60,25 };
    quick_sort(unsorted, 0, unsorted.size() - 1);
    for (int i : unsorted) {
        cout << i << '\t';
    }
}