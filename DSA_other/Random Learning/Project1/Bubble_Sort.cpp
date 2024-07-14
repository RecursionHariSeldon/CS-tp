#include <iostream>
#include <vector>
//using namespace std;

std::vector<int> bubble_sort(std::vector<int> vector)
{
    int len = vector.size();
    for (int i = 0; i < len ; i++)
    {
        for (int k = 0; k < len - i-1; k++) {
            if (vector[k] > vector[k + 1]) {
                int t = vector[k + 1];
                vector[k + 1] = vector[k];
                vector[k] = t;
            }
        }

    }

    return vector;

}

int main() {
    std::vector<int> unsorted = { 5,3,6,8,2,1,7,9,12,15,3,17,5,2,1 };
    std::vector<int> sorted = bubble_sort(unsorted);
    for (int i : sorted) {
        std::cout << i << '\t';
    }
}