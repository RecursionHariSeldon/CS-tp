#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <cmath>
#include <conio.h> // for getch()
//using namespace std;

//unicode ke liye
#include <windows.h>
#include <wchar.h>//for unicode
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD written = 0;
typedef const void* PCVOID;

// all forward declarations 
char allowedchar[] ={'a','b','c','d','e','f','g','h'};
int allowedrow[] = {1,2,3,4,5,6,7,8};
struct piece;
struct square{
char col;
int row;
piece* current = nullptr;
};

std::vector<std::vector<square>> board;
std::vector<std::vector<square>> * boardptr;
std::vector<piece> * killedptr ;
std::vector<piece> * activeptr;
std::ofstream * fileptr;
bool run = true;
bool isCheckBlack();
bool isCheckWhite();
bool isCheckMateBlack();
bool isCheckMateWhite();
struct move{
    int row;
    char col;
    move(char c, int r){
        row=r;
        col = c;
    }
};
std::vector<move> legal;

bool checkChar(char v[], char c){

    for (int i=0;i<8;i++)
        if (v[i] ==c )
            return true;
    return false;
}

bool checkint(int v[], int c){

    for (int i=0;i<8;i++)
        if (v[i] ==c )
            return true;
    return false;
}

struct piece{
    char type;
    std::string name;
    int row;
    char col;
    PCVOID symbol;
    char colour;
    std::vector<std::vector<square>>* cboard;

    piece(char t,std::string n,int r,char c,PCVOID s,char cl,std::vector<std::vector<square>>* cb){
        type = t;
        name = n;
        row = r;
        col = c;
        symbol = s;
        colour = cl;
        cboard = cb;
        this->setLocTo(c,r);
    }

    void setLocTo(char ncol,int nrow){

        board[8-row][col-97].current = nullptr;
        col = ncol;
        row = nrow;
        if (board[8-row][col-97].current != nullptr ){
            (*killedptr).push_back(*(board[8-row][col-97].current));
            (*fileptr) << "--by capturing the "<<board[8-row][col-97].current->name<<std::endl;
            std::cout<< "--by capturing the "<<board[8-row][col-97].current->name<<std::endl;

           char dcol = (*killedptr).back().col;
           int drow = (*killedptr).back().row;
           char dcolour = (*killedptr).back().colour;
           int i=0;
            for ( piece p:(*activeptr)){
                if( p.row == nrow && p.col == ncol && p.colour == dcolour )
                    break;
                i++;
                }
            (*activeptr).erase((*activeptr).begin() + i);
            board[8-row][col-97].current = this ;
        }else{
             board[8-row][col-97].current = this ;

        }
    }



    bool isLegal(char colTo, int rowTo){
        // if board is in check then false

        if((board[8-rowTo][colTo-97].current != nullptr) && board[8-rowTo][colTo-97].current->colour == colour)
            return false;

        if(type=='R'){

            if (row ==rowTo){
                bool clr = true;
                int c1 = std::min(col,colTo);
                int c2 = std::max(col,colTo);
                for(int i =c1+1;i<c2;i++)
                    if(board[8-row][i-97].current != nullptr)
                        clr =false;

                return clr;
            }
            if(col==colTo){
                bool clr = true;
                int r1 = std::min(row,rowTo);
                int r2 = std::max(row,rowTo);
                for(int i =r1+1;i<r2;i++)
                    if(board[8-i][col-97].current != nullptr)
                        clr =false;

                return clr;
            }
            return false;
        }

        if(type=='k'){
            if(  (abs(row-rowTo)== 1 && abs(col-colTo)==2 ) || (abs(row-rowTo)== 2 && abs(col-colTo)==1 )   )
                return true;

            return false;
        }

        if(type=='B'){
            if(abs(row-rowTo) == abs(col-colTo)){
                int dr = rowTo-row;
                int stepr = abs(dr)/dr;
                int dc = colTo-col;
                int stepc = abs(dc)/dc;

                bool clr = true;
                int r = row+stepr;
                int c = col+stepc;
                while(r != rowTo){
                    if(board[8-r][c-97].current != nullptr)
                        clr =false;

                    r += stepr;
                    c += stepc;
                }
                return clr;
            }


            return false;
        }

        if(type=='Q'){
            //as rook
            if (row ==rowTo){
                bool clr = true;
                int c1 = std::min(col,colTo);
                int c2 = std::max(col,colTo);
                for(int i =c1+1;i<c2;i++)
                    if(board[8-row][i-97].current != nullptr)
                        clr =false;

                return clr;
            }
            if(col==colTo){
                bool clr = true;
                int r1 = std::min(row,rowTo);
                int r2 = std::max(row,rowTo);
                for(int i =r1+1;i<r2;i++)
                    if(board[8-i][col-97].current != nullptr)
                        clr =false;

                return clr;
            }

            //as bishop
            if(abs(row-rowTo) == abs(col-colTo)){
                int dr = rowTo-row;
                int stepr = abs(dr)/dr;
                int dc = colTo-col;
                int stepc = abs(dc)/dc;

                bool clr = true;
                int r = row+stepr;
                int c = col+stepc;
                while(r != rowTo){
                    if(board[8-r][c-97].current != nullptr)
                        clr =false;

                    r += stepr;
                    c += stepc;
                }
                return clr;
            }
            return false;
        }

        if(type=='K'){
            if((  abs(row-rowTo)== 1 || abs(row-rowTo)== 0 )  && ( abs(col-colTo)==1 || abs(col-colTo)==0 ))
                return true;
            return false;
        }

        if(type=='P'){

            if(colour=='w'){
                if(row==2 && (colTo==col) && (rowTo==3 || rowTo ==4 ) && (board[8-rowTo][colTo-97].current == nullptr))
                    return true;
                if( (colTo==col) && (rowTo==row+1) && (board[8-rowTo][colTo-97].current == nullptr))
                    return true;
                if( (colTo==col+1  || colTo==col-1) && (rowTo==row+1) && (board[8-rowTo][colTo-97].current != nullptr))
                    return true;

            }

            if(colour=='b'){
                    if(row==7 && (colTo==col) && (rowTo==6 || rowTo ==5 ) && (board[8-rowTo][colTo-97].current == nullptr))
                        return true;
                    if( (colTo==col) && (rowTo==row-1) && (board[8-rowTo][colTo-97].current == nullptr))
                        return true;
                    if( (colTo==col+1  || colTo==col-1) && (rowTo==row-1) && (board[8-rowTo][colTo-97].current != nullptr))
                        return true;
            }

            return false;
        }

        return false;
    }

    bool checkWhiteSafe(char ncol,int nrow){
        // saving the older board
        int oldrow = row;
        char oldcol = col;
        piece * p1 = board[8-nrow][ncol-97].current;
        piece * p2 = board[8-row][col-97].current;

        // updating and getting new board to check for check
        board[8-row][col-97].current = nullptr;
        col = ncol;
        row = nrow;
        (board)[8-row][col-97].current = this ;

        //update activePieces
        *activeptr = {};
        for (int i=0;i<8;i++)
            for (int j =0;j<8;j++)
                if (board[i][j].current != nullptr)
                    (*activeptr).push_back( (*board[i][j].current));


        int i;
        for ( i=0;i<(*activeptr).size();i++){
        if((*activeptr)[i].type=='K' && (*activeptr)[i].colour=='w')
            break;
        }
        int kr = (*activeptr)[i].row;
        char kc = (*activeptr)[i].col;

        for (piece p: *activeptr){

            if (p.colour=='b' && p.type!='P'){
                if (p.isLegal(kc,kr)) {
                    row = oldrow;
                    col = oldcol;
                    board[8-row][col-97].current = this;
                    board[8-nrow][ncol-97].current = p1;
                    return false;
                }
            }

            if (p.colour=='b' && p.type=='P'){
                if (kr == p.row-1 && abs(p.col - kc)==1){
                    row = oldrow;
                    col = oldcol;
                    board[8-row][col-97].current = this;
                    board[8-nrow][ncol-97].current = p1;
                    return false;

                }
            }
        }
        row = oldrow;
        col = oldcol;
        board[8-row][col-97].current = this;
        board[8-nrow][ncol-97].current = p1;
        return true;
    }

    bool checkBlackSafe(char ncol,int nrow){
        // saving the older board
        int oldrow = row;
        char oldcol = col;
        piece * p1 = board[8-nrow][ncol-97].current;
        piece * p2 = board[8-row][col-97].current;

        // updating and getting new board to check for check
        board[8-row][col-97].current = nullptr;
        col = ncol;
        row = nrow;
        (board)[8-row][col-97].current = this ;

        //update activePieces
        *activeptr = {};
        for (int i=0;i<8;i++)
            for (int j =0;j<8;j++)
                if (board[i][j].current != nullptr)
                    (*activeptr).push_back( (*board[i][j].current));


        int i;
        for ( i=0;i<(*activeptr).size();i++){
        if((*activeptr)[i].type=='K' && (*activeptr)[i].colour=='b')
            break;
        }
        int kr = (*activeptr)[i].row;
        char kc = (*activeptr)[i].col;

        for (piece p: *activeptr){

            if (p.colour=='w' && p.type!='P'){
                if (p.isLegal(kc,kr)) {
                    row = oldrow;
                    col = oldcol;
                    board[8-row][col-97].current = this;
                    board[8-nrow][ncol-97].current = p1;
                    return false;
                }
            }

            if (p.colour=='w' && p.type=='P'){
                if (kr == p.row+1 && abs(p.col - kc)==1){
                    row = oldrow;
                    col = oldcol;
                    board[8-row][col-97].current = this;
                    board[8-nrow][ncol-97].current = p1;
                    return false;

                }
            }
        }
        row = oldrow;
        col = oldcol;
        board[8-row][col-97].current = this;
        board[8-nrow][ncol-97].current = p1;
        return true;
    }
};

void createBoard(std::vector<std::vector<square>> &board){
    for(int i=8;i>0;i--) {
        std::vector<square> row;

        for (int j=1;j<9;j++){
            square s{(char)(j+96)};
            row.push_back(s);
        }

        board.push_back(row);
    }
}

void printBoard(std::vector<std::vector<square>> board){

    std::cout<<"Black killed Pieces: ";
    for (piece i: *killedptr){
        if(i.colour =='b'){
            WriteConsoleW(handle, i.symbol, 1, &written, NULL);
            std::cout<<"   ";
        }

    }

    std::cout<<"\n    ____ ____ ____ ____ ____ ____ ____ ____ "<<std::endl;
    for (int i=0;i<8;i++){

        std::cout<<8-i<<"  ";
        for (int j =0;j<8;j++){

            std::cout<<"|"<<"  ";
            if (board[i][j].current != nullptr)
                WriteConsoleW(handle, board[i][j].current->symbol, 1, &written, NULL); // it works IDKY
            else
                std::cout<<" ";
            std::cout<<" ";

            }
        std::cout<<"|"<<std::endl;
        std::cout<<"   |____|____|____|____|____|____|____|____|"<<std::endl;
    }
    std::cout<<"     a    b    c    d    e    f    g   h   \n"<<std::endl;
    std::cout<<"White killed Pieces: ";
    for (piece i: *killedptr){
        if(i.colour =='w'){
            WriteConsoleW(handle, i.symbol, 1, &written, NULL);
            std::cout<<"   ";
        }

    }

    std::cout<<"\nAll pieces alive:  ";
    for (piece i: *activeptr){
            WriteConsoleW(handle, i.symbol, 1, &written, NULL);
            std::cout<<"  ";

    }
    std::cout<<std::endl;

}

void movePiece(char color){
    std::cout<<"Which piece do you want to move? ";
    char c;int r;
    
    std::cin>>c>>r;
    if (std::cin.fail()){
         std::cout << "Please enter valid input\n";
         // clear error state
         std::cin.clear();
         // discard 'bad' character(s)
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         movePiece(color);
         return;
}
    if(c=='r'){
        std::cout<<"Do you resign? (y/n) : ";
        char resign;
        std::cin >> resign;
        if (resign=='y') {
            run = false;
            if(color == 'w'){
                std::cout<<"Black wins by resignation! "<<std::endl;
                *fileptr<<"Black wins by resignation! "<<std::endl;
                *fileptr<<"black";

            }else{
                std::cout<<"White wins by resignation! "<<std::endl;
                *fileptr<<"White wins by resignation! "<<std::endl;
                *fileptr<<"white";
            }
        }
    }
    piece * ptr;
    if(checkChar(allowedchar,c) && checkint(allowedrow,r) && (board[8-r][c-97].current!=nullptr ) &&   (board[8-r][c-97].current->colour==color))
        ptr = board[8-r][c-97].current;
    else{
        std::cout<<"Please choose a piece on board of your colour "<<std::endl;
        movePiece(color);
        return;
        

    }

    std::cout<<"Where do you want to move the "<<(*ptr).name<<" to? ";
    char col;int row;
    std::cin>>col>>row;
    if (std::cin.fail()){
         std::cout << "Please enter valid input\n";
         // clear error state
         std::cin.clear();
         // discard 'bad' character(s)
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         movePiece(color);
         return;
}
    if(color == 'w'){
        if(checkChar(allowedchar,col) && checkint(allowedrow,row) && (*ptr).isLegal(col,row) && (*ptr).checkWhiteSafe(col,row) ){

        std::cout<<"Your "<<(*ptr).name<<" has been moved to "<<col<<row<<std::endl;
        *fileptr << "White's "<<(*ptr).name<< " has been moved from "<<c<<r<<" to "<<col<<row<<std::endl;
        (*ptr).setLocTo(col,row);
        if(isCheckBlack()){
            std::cout<<"# Black is under check! "<<std::endl;
            *fileptr <<"# Black is under check! "<<std::endl;
            if(isCheckMateBlack()){
                run = false;
                std::cout<<"CheckMate!! White wins! "<<std::endl;
                *fileptr<<"CheckMate!! White wins! "<<std::endl;
                *fileptr<<"white";
            }
        }
            
        
        std::cout<<"\nPress something to go ahead..."<<std::endl;
    }
    else{
        std::cout<<"Illegal move. Please retry! "<<std::endl;
        movePiece('w');
        return;
    }

    }else{
        if(checkChar(allowedchar,col) && checkint(allowedrow,row) && (*ptr).isLegal(col,row) && (*ptr).checkBlackSafe(col,row) ){
        std::cout<<"Your "<<(*ptr).name<<" has been moved to "<<col<<row<<std::endl;
        *fileptr << "White's "<<(*ptr).name<< " has been moved from "<<c<<r<<" to "<<col<<row<<std::endl;
        (*ptr).setLocTo(col,row);
        if(isCheckWhite()){
            std::cout<<"# White is under check! "<<std::endl;
            *fileptr <<"# White is under check! "<<std::endl;
            if(isCheckMateWhite()){
                run = false;
                std::cout<<"CheckMate!! Black wins! "<<std::endl;
                *fileptr<<"CheckMate!! Black wins! "<<std::endl;
                *fileptr<<"black";
            }
        }
        
        std::cout<<"\nPress something to go ahead..."<<std::endl;
    }
    else{
        std::cout<<"Illegal move. Please retry! "<<std::endl;
        movePiece('b');
        return;
    }
    }

}

//checks if black is under check
bool isCheckBlack(){
        int i;
        for ( i=0;i<(*activeptr).size();i++){
        if((*activeptr)[i].type=='K' && (*activeptr)[i].colour=='b')
            break;
        }
        int kr = (*activeptr)[i].row;
        char kc = (*activeptr)[i].col;
        for (piece p: *activeptr){
            if (p.colour=='w' && p.type!='P'){
                if (p.isLegal(kc,kr)) {
                    return true;
                }
            }
            if (p.colour=='w' && p.type=='P'){
                if (kr == p.row+1 && abs(p.col - kc)==1){
                    return true;
                }
            }
        }
        return false;
}

//checks if white is under check
bool isCheckWhite(){
        int i;
        for ( i=0;i<(*activeptr).size();i++){
        if((*activeptr)[i].type=='K' && (*activeptr)[i].colour=='w')
            break;
        }
        int kr = (*activeptr)[i].row;
        char kc = (*activeptr)[i].col;
        for (piece p: *activeptr){
            if (p.colour=='b' && p.type!='P'){
                if (p.isLegal(kc,kr)) {
                    return true;
                }
            }
            if (p.colour=='b' && p.type=='P'){
                if (kr == p.row-1 && abs(p.col - kc)==1){
                    return true;
                }
            }
        }
        return false;
}



void legalMoves(char c, int r){
    

}
//checks if black is checkmated
bool isCheckMateBlack() {
    return false;
    //return true;
}

//checks if white is checkmated
bool isCheckMateWhite() {
    return false;
    //return true;
}

int main(){

    createBoard(board);

    std::cout<<"What is the name of the game? ";
    std::string name;
    std::cin>>name;
    name = "games\\" +  name + ".txt";
    //std::cout<<name;
    std::ofstream file(name);
    fileptr = &file;
    if (!file)
    {
        // Print an error and exit
        std::cout << "Uh oh, "<<name<<" could not be opened!\n";
        return 1;
    }

    std::vector<piece> activePieces = {
    piece ('k',"Knight",1,'b',L"\u265E",'w',&board),
    piece ('k',"Knight",1,'g',L"\u265E",'w',&board),
    piece ('B',"Bishop",1,'c',L"\u265D",'w',&board),
    piece ('B',"Bishop",1,'f',L"\u265D",'w',&board),
    piece   ('R',"Rook",1,'a',L"\u265C",'w',&board),
    piece   ('R',"Rook",1,'h',L"\u265C",'w',&board),
    piece  ('Q',"Queen",1,'d',L"\u265B",'w',&board),
    piece   ('K',"King",1,'e',L"\u265A",'w',&board),

    piece ('P',"Pawn",2,'a',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'b',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'c',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'d',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'e',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'f',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'g',L"\u265F",'w',&board),
    piece ('P',"Pawn",2,'h',L"\u265F",'w',&board),

    piece  ('k',"Knight",8,'b',L"\u2658",'b',&board),
    piece  ('k',"Knight",8,'g',L"\u2658",'b',&board),
    piece  ('B',"Bishop",8,'c',L"\u2657",'b',&board),
    piece  ('B',"Bishop",8,'f',L"\u2657",'b',&board),
    piece  ('R',"Rook",8,'a',  L"\u2656",'b',&board),
    piece  ('R',"Rook",8,'h',  L"\u2656",'b',&board),
    piece   ('Q',"Queen",8,'d',L"\u2655",'b',&board),
    piece    ('K',"King",8,'e',L"\u2654",'b',&board),

    piece ('P',"Pawn",7,'a',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'b',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'c',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'d',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'e',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'f',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'g',L"\u2659",'b',&board),
    piece ('P',"Pawn",7,'h',L"\u2659",'b',&board),
    };
    activeptr = &activePieces;
    std::vector<piece> killed;
    killedptr = &killed;
    int moves = 0;
    while(run){
        moves++;

        //update activePieces
        activePieces = {};
        for (int i=0;i<8;i++)
            for (int j =0;j<8;j++)
                if (board[i][j].current != nullptr)
                    activePieces.push_back( (*board[i][j].current));



        std::cout<<"Move no. "<<moves<<std::endl;
        printBoard(board);
        std::cout<<"\nIt's White's Move!"<<std::endl;
        file<< "Move no. "<<moves<<std::endl;
        movePiece('w');
        getch();
        system("cls");

        if(!run) break;

        std::cout<<"Move no. "<<moves<<std::endl;
        printBoard(board);
        std::cout<<"\nIt's Black's Move!"<<std::endl;
        file<< "Move no. "<<moves<<std::endl;
        movePiece('b');
        getch();
        system("cls");

        file<<std::endl;

    }

}