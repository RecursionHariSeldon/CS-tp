

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> a = { 1,2 };
    cout <<  &a << endl;
    cout << &a[0] << endl;
    vector<int>* pa = &a;
    int* pa1 = &a[0];


    a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4); a.push_back(4);
    cout << &a << endl;
    cout << &a[0] << endl;

    cout << *pa1 << endl;
   
}
