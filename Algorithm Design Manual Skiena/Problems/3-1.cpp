#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct brack{
    int pos ;
    bool check;

    brack(int a, bool b){
        pos =a;check = b;
    }
};

struct par{
    bool p ;// true == (
    int pos;
};

string btos(bool a){
    if (a) return "True"; else return "False";
}


par create_par(bool p,int pos){
    par ex;
    ex.p = p;
    ex.pos = pos;
    return ex;
}

brack check_Parenthesis(string brac){
    int len = brac.length();
    int count = 0;
    int i = 0;
    while (count>=0 && i<len){
        if (brac[i] == '(' ) count++;
        else count --;

        i++;
    }

    if (count == 0){ 

        brack a(-1,true);
        return a;
    } 
    else if (count == -1) {
        brack a(i,false);
        return a;
    }
    else {
        vector<int> positions_paired ;
        vector<par> full;
        for (int i=1;i<=len;i++){
            if (brac[i-1] == '(') full.push_back(create_par(true,i));
            else full.push_back(create_par(false,i));
        }

        for (par i : full){
            if (i.p == false){
                for(int j = i.pos;j>=1;j--){
                    if(full[j-1].p && find(positions_paired.begin(), positions_paired.end(),full[j-1].pos)==positions_paired.end() ){
                        positions_paired.push_back(j);
                        break;
                    }
                }
            }
        }

        int first;
        for (par i:full) {
            if (i.p==true && find(positions_paired.begin(), positions_paired.end(),i.pos)==positions_paired.end()){
                first = i.pos;
                break;
            }
        }
        brack a(first,false);
        return a;


    }
}

int main(){
    string a;
    a = "((())())((((()";//((((
    brack bracket = check_Parenthesis(a);
    cout<< "Is the string a set of balanced parenthesis:           " << btos(bracket.check) <<" \n"<< "First offending bracket is at position(starts from 1): "<<bracket.pos <<endl;
}

