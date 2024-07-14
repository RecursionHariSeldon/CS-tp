#include <iostream>
#include <fstream>
#include <vector>

std::vector< std::vector<int> > sudoku ={
  {5,3,0,0,7,0,0,0,0},
  {6,0,0,1,9,5,0,0,0},
  {0,9,8,0,0,0,0,6,0},
  {8,0,0,0,6,0,0,0,3},
  {4,0,0,8,0,3,0,0,1},
  {7,0,0,0,2,0,0,0,6},
  {0,6,0,0,0,0,2,8,0},
  {0,0,0,4,1,9,0,0,5},
  {0,0,0,0,8,0,0,7,9}

};

// x,y are from 0 to 8 

std::vector<int> subSection(int x,int y){
    std::vector<int> sub;
    for(int x1 = (x/3)*3; x1<(x/3)*3 + 3 ; x1++){
        for(int y1 = (y/3)*3; y1<(y/3)*3 + 3 ; y1++){
            sub.push_back(sudoku[x1][y1]);
        } 
    }

    return sub;
}


bool checkValid( int x, int y, int k){
    for(int t=0;t<9;t++ )
        if (sudoku[x][t] == k) 
            return false;

    for(int t=0;t<9;t++)
        if (sudoku[t][y] == k) 
            return false;

    for(int t=0;t<9;t++)
        if(subSection(x,y)[t] == k)
            return false;
    
    return true;
}

bool solveSudoku(int i, int j){
    
    if(i==9)
        return true;
    
    if(j==9){
        j = 0;
        return solveSudoku(i+1,0);
    }
        
    if(sudoku[i][j] != 0){
        return solveSudoku(i,j+1);
    }
    
    if(sudoku[i][j] == 0){
        for (int a=1;a<10;a++){
            if(checkValid(i,j,a)){
                sudoku[i][j] = a;
                if (solveSudoku(i,j))
                    return true;
                else 
                    sudoku[i][j] = 0;
            }
        }
        return false;
    }
}

int main(){
    solveSudoku(0,0);
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            std::cout<< sudoku[i][j]<<"  ";
        }
        std::cout<<"\n";
    }

}