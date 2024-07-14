#include <iostream>
#include <string>
#include <vector>
using namespace std ;

int main(){
    cout << "Do you want \n(1) Check Sum  \nor  \n(2) Check div sum  \n";
    int choice; 
    cin>>choice;
    if (choice == 1){
        int checksum = 0 ;
    
        for(int i = 0;i<16;i++){

            int min ;
            int max ;

            for(int j = 0 ;j<16;j++){
                int current;
                cin >> current;
                if (j==0 ) {
                    min = current;
                    max = current;
                }
                if (min > current) min = current;
                if(max < current) max = current;
            }
            checksum += max - min;
        }
        
        cout << "Checksum : " << checksum << endl;
    }
    
    if (choice == 2){
        int checkdivsum = 0 ;

        for(int i = 0;i<16;i++){
            vector<int> divisors;
            for(int j = 0 ;j<16;j++){
                int dividend;
                cin >> dividend;
                divisors.push_back(dividend);
            }
            int divisor=0;
            int dividend;
            for(int a : divisors){
                for(int b: divisors){
                    if(a!=b && a%b==0){
                        dividend = a;
                        divisor = b;
                        break;
                    }
                    
                }
                if(divisor !=0) break;
            }

            checkdivsum += dividend/divisor;
        }
        cout << "Check_Div_sum : " << checkdivsum << endl;
    }

}