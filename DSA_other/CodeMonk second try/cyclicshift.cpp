#include <iostream>
#include <bitset>
#include <string>

using namespace std;

void print(bitset<100000> & b , int n){
    for(int i = n-1; i>=0;i--)
        cout<< b[i];
    cout<<"\n";
}

void shift(bitset<100000> & b , int n){
    int t = b[n-1];
    b <<= 1;
    b[0] = t;
}

int compare(bitset<100000> a , bitset<100000> b,int n){
    for (int i =n-1;i>=0;i--){
        if(a[i] > b[i])
            return 1;
        else if(a[i] < b[i])
            return -1;
    }
    return 0;

}

int main(){
    int cases;
    cin>>cases;
    for(int w = 0; w<cases;w++){
        int n , k;
        string stringb;
        cin>>n>>k>>stringb;
        bitset<100000> b(stringb);
        // cout<< b;   -- this will gave us like a million 0s and 100111010010

        bitset<100000> max{"0"};
        long maxtimesinone = 0;

        for(int i = 0 ;i<n;i++){
            if(compare(b,max,n)==1){
                max = b;
                maxtimesinone = 1;
            }
            else if (compare(max,b,n)==0)
                maxtimesinone++;
            
            shift(b,n);
        }

        long r = k % maxtimesinone;
        long i=-1;
        long control = 0;

        if(r!=0){
            while(control<r){
                if (compare(max,b,n)==0)
                    control++;
                i++;
                shift(b,n);
            }

            long total = ((k-r)/maxtimesinone) * n  + i  ;
            // print(b,n);
            // print(max,n);
            // cout<<"No of loops   " << (k-r)/maxtimesinone<<endl;
            // cout<<"Max times in one   "<< maxtimesinone<<endl;
            // cout<<"Remainder  "<<r<<endl;
            // cout<<"Total  "<< total <<endl;
            cout<<total<<endl;

        }else{
            while(control<maxtimesinone){
                if (compare(max,b,n)==0)
                    control++;
                i++;
                shift(b,n);
            }

            long total = ((k/maxtimesinone)  -1)*n  + i  ;
            // print(b,n);
            // print(max,n);
            // cout<<"No of loops   " << (k-r)/maxtimesinone<<endl;
            // cout<<"Max times in one   "<< maxtimesinone<<endl;
            // cout<<"Remainder  "<<r<<endl;
            // cout<<"Total  "<< total <<endl;
            cout<<total<<endl;

        }
    }
}