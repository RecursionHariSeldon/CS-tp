#include <iostream>
#include <string>
using namespace std ;

int main(){
    string input;
    cin >> input;
    int len = input.length();
    int sum = 0;
    int i;

    for(i=0;i<len;i++){
        if(input[i] == input[(i+1)%len])
            sum += ((int) input[i])-48;

    }
    cout << "One step forward captcha:  " << sum<< endl;

     sum = 0;
     i;

    for(i=0;i<len;i++){
        if(input[i] == input[(i + (len/2) )%len])
            sum += ((int) input[i])-48;

    }

    cout << "circular captcha:  " << sum<< endl;

}