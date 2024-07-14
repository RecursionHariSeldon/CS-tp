#include <iostream>
using namespace std;

int main() {

    int varN = 100;
    int* ptrN = &varN; // ptrN points to varN address

    cout << "varN value: " << varN << endl;
    cout << "varN location: " << ptrN << endl;
    cout << "dereference ptrN: " << *ptrN << endl;

  /*
  int a = 100;
    int* ptra = a;  --> conversion error int* to int type

    cout << "varN value: " << a << endl;
    cout << "varN location: " << ptra << endl;
    cout << "ptrN points to varN: " << endl;
    cout << "dereference ptrN: " << *ptra << "\n\n";


    */  

    int x = 12345;
    int* ptrx = &x;

    while (ptrx) {
        cout << "Pointer ptrx points to " << ptrx << endl;
        ptrx = NULL;
    }

    cout << "Pointer ptrx points to nothing!" << endl;


	int* ptry = NULL;
	cout << ptry << endl; //0000000000000000
	// cout<< *ptry<< endl; error

}