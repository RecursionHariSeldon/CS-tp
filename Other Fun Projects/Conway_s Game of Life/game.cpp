#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;

double randomProb(){
    srand( (unsigned)time( NULL ) );
    double prob = (double) rand()/RAND_MAX;
    return prob;
}
vector<vector<int>> input(){
    int x , y;
    cout<<"Enter grid size:(X Y) : ";
    cin >> x >> y;

    vector<vector<int>> grid;

    for (int i =0;i<y;i++){
    vector<int> row;
        for(int j =0;j<x;j++)
            row.push_back(0);
    grid.push_back(row);
    }

    cout<< "Enter Initial State alive cells: ";
    int alive;
    cin>> alive;

    for (int i=0;i<alive;i++){
        int a,b;
        cout<< "Enter coordinate for cell "<< i+1 << " in format 'X Y' (starting from 1):  ";
        cin>>a>>b;
        grid[b-1][a-1] = 1;
        cout<<endl;
    }

    return grid;
}

vector<vector<int>> randGrid(){
    int x , y;
    cout<<"Enter grid size:(X Y) : ";
    cin >> x >> y;

    vector<vector<int>> grid;

    for (int i =0;i<y;i++){
    vector<int> row;
        for(int j =0;j<x;j++)
            row.push_back(0);
    grid.push_back(row);
    }

    for (int i=0;i<y;i++){
        for(int j=0;j<x;j++){
                double prob = (double)rand() / (double)(RAND_MAX + 1);
           if (prob>0.2) grid[i][j] =0;
           else grid[i][j] =1;
        }
    }

    return grid;
}

void printGrid(vector<vector<int>> grid, int choice){

    for (vector<int> i: grid){
        for (int j : i){
            if (j==0) cout<<"_";
            else cout<< "X";
        }


        cout<<endl;
    }
    cout<<endl;
    if(choice == 2) {
        cout<<"Press any key to continue to next generation "<<endl;
    getch();
    }else{
        Sleep(1500);
    }

    system("cls");
}

int noOfNeighbours(vector<vector<int>> grid, int i , int j){
    //i, j start at 0

    int X = grid[0].size();
    int Y = grid.size();
    int n = 0;

    vector<vector<int>> extendedGrid ;
    vector<int> row;
    for (int w=0;w<X+2;w++) row.push_back(0);

    for (int i=0;i<Y+2;i++)
            extendedGrid.push_back(row);

    for (int i=1;i<Y+1;i++)
        for(int j=1;j<X+1;j++)
            extendedGrid[i][j] = grid[i-1][j-1];

    int I = i+1;
    int J = j+1;

    n = extendedGrid[I-1][J-1] + extendedGrid[I][J-1] + extendedGrid[I+1][J-1] + extendedGrid[I-1][J] +
        extendedGrid[I+1][J] + extendedGrid[I-1][J+1] + extendedGrid[I][J+1] + extendedGrid[I+1][J+1] ;
    return n;
}

void updateGrid(vector<vector<int>> &grid){
    int X = grid[0].size();
    int Y = grid.size();

    vector<vector<int>> newGrid;
    for (int i =0;i<Y;i++){
    vector<int> row;
        for(int j =0;j<X;j++)
            row.push_back(0);
    newGrid.push_back(row);
    }

    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
                int n = noOfNeighbours(grid,i,j);
            if (grid[i][j] == 0){
                if ( n>= 3 && n<=3 ) newGrid[i][j] = 1;
                else                               newGrid[i][j] = 0;
            }
            else{
                if (n == 2 || n == 3) newGrid[i][j] = 1;
                else                  newGrid[i][j] = 0;
            }
        }
    }

    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
                grid[i][j] = newGrid[i][j];
        }
    }
}

int main(){

    cout<< "What kind of simulation? \n (1)User defined \n (2) Random : \n";
    int choice;
    cin>>choice;

    cout<< "Auto run sim or key controlled? \n (1)Auto run\n (2)key controlled: \n";
    int choice2;
    cin>>choice2;

    if (choice==1){
        vector<vector<int>> grid = input();
        while(true){
            printGrid(grid,choice2);
            updateGrid(grid);
        }
    }
    else{
        vector<vector<int>> grid = randGrid();
        while(true){
            printGrid(grid,choice2);
            updateGrid(grid);
        }
    }

}
