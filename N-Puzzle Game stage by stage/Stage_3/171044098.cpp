#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
using namespace std;
class NPuzzle{
private:
    bool end;
    int totalMoves,intelligentMoves;
    //private inner class
    class Board{
    private:
        //member variables
        int puzzle[9][9];
        int row,column,size,lastDirection;
    public:
        //member functions
        //since I used all of them for board class I defined them in the board class.
        Board();//constructor
        void print() const;
        bool readFromFile(string fileName);
        void writeToFile(string fileName);
        void reset();
        void setSize(int r,int c,int s);
        bool move(char move_direction,int flag);
        bool is_solved();
        /*-----my helper functions for these functions-----*/
        int takeSize();
        bool checkSize(int input);
        int getSize();
        int sizeofStr(string str) const;
        int convertStrToInt(string str,int sizeOfStr);
        void getSolutionOfPuzzle(int soutionOfPuzzle[9][9]);
        int createSubPuzzleAndCheckThem(int arr[4]);
        void findCoordinatesOfEmpty(int arr[2]);
        int sumManhattanOfAllTiles();
        int calculateManhattanOfOneTile(int tile,int x_position,int y_position);
        int absoluteValue(int value);
        void setLastDirection(int last);
        int getLastDirection() const;
        string takeFileName(int flag);
    };
    Board game_board; //to use these function create an object as private
    
public:
    NPuzzle();//constructor
    void printReport() const;
    void shuffle(int N); 
    void moveRandom(int NumberOfTimes);
    int moveIntelligent();
    void solvePuzzle();
    /*-----my other helper functions for these functions-----*/
    void gameRealTime(string fileName,int gameType);
    int getTotalMoves() const;
    void setTotalMoves();
    bool getEnd();
    void Quit();
    char getDirection();
    void choice(char userWants);
};
int main(int argc,char *argv[]){
    NPuzzle n1;//create an object
    if (argc<2) //if there is no filename
       n1.gameRealTime("",1); //begin with hw1
    else if(argc==2){
        n1.gameRealTime(argv[1],2); //begin with hw2
    }
    else
        cout << "Enter Correctly!" << endl;
    return 0;
    
}
NPuzzle::NPuzzle(){ //implement constructor
    totalMoves=0;intelligentMoves=0;
    end=false;
}
NPuzzle::Board::Board(){ //implement constructor
    /* initialize puzzle with -1 */
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            puzzle[i][j]=-1;
        }
    }
    size=0;row=0;column=0;lastDirection=5;
}
void NPuzzle::gameRealTime(string fileName,int gameType){
    //play game
    bool is_solvable,check=false;
    char prefer;
    int sizeOfBoard;
    if (gameType==1)//if a filename didn't enter
    {
        check=true;
        sizeOfBoard=game_board.takeSize();
        game_board.setSize(sizeOfBoard,sizeOfBoard,sizeOfBoard*sizeOfBoard); //set size with new size
        game_board.reset();//reset
        shuffle(game_board.getSize()*3);//shuffle the solved puzzle to get solvable random puzzle
    }
    else //if a filename entered
        check=game_board.readFromFile(fileName);// set size and reset puzzle in the readFromFile function
    if (!check) //if there is an error with file then terminate the program..
        exit(1);
    game_board.is_solved();//check
    setTotalMoves();//set total move with zero
    while (!getEnd())
    {
        game_board.print();
        prefer=getDirection();
        if (prefer!='L' && prefer!='R' && prefer!='U' && prefer!='D')
            choice(prefer); //choice of user is not a direction
        else{
            if (game_board.move(prefer,0))
                totalMoves++;
        }
    }
    cout << endl  << "Problem Solved!" << endl; 
    cout << "Total number of moves " << getTotalMoves() << endl;
}
int NPuzzle::Board::takeSize()
{
    //take a valid size
    int s;
    bool validty;
    cout << "Please enter the problem size: ";
    /*Check for size validty(number or character)*/
    while(!(cin >> s)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please Enter a number: ";
    }
    //if it is not a character then,
    //check for correct size(3,4,...,9)
    validty=checkSize(s); 
    while (!validty)
    {
        cout << "Please enter a valid number(3,4,5,...,9): ";
        while(!(cin >> s)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please Enter a number: ";
        }
        validty=checkSize(s);
    }
    return s;

}
bool NPuzzle::Board::checkSize(int input){
    // this function is to check correct size
    const int lenght=7;// constant number of valid sizes
    int defaultsize[lenght]={3,4,5,6,7,8,9};
    for (int i = 0; i < lenght; i++)
    {
        if (defaultsize[i]==input)
            return true;
    }
    return false;
}
void NPuzzle::Board::setSize(int r,int c,int s)
{
    row=r;
    column=c;
    size=s;
}
void NPuzzle::shuffle(int N){
    //to shuffle make N times random moves
    moveRandom(N);
}
void NPuzzle::Board::reset(){
    //reset puzzle with solution
    int i,j,currentvalue=1;
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < column; j++)
        {
            
            if (i==row-1 && j==column-1)
                puzzle[i][j]=-1;
            else{

                if (puzzle[i][j]!=0)
                {
                    puzzle[i][j]=currentvalue;
                    currentvalue++;
                }
                else
                {
                     puzzle[i][j]=0;
                }
                
            }
           
        }
        
    }

}
void NPuzzle::Board::getSolutionOfPuzzle(int solutionOfPuzzle[9][9]){
    //fill the puzzle with solution to use make comparision
    int i,j,currentvalue=1;
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < column; j++)
        {
            
            if (i==row-1 && j==column-1)
                solutionOfPuzzle[i][j]=-1;
            else{

                if (puzzle[i][j]!=0)
                {
                    solutionOfPuzzle[i][j]=currentvalue;
                    currentvalue++;
                }
                else
                {
                    solutionOfPuzzle[i][j]=0;
                }
                
            }
        }
        
    }

}
bool NPuzzle::getEnd() {
    end=game_board.is_solved(); //check the puzzle
    return end;
}
/* my inline functions*/
inline void NPuzzle::Board::setLastDirection(int last){
    lastDirection=last;
}
inline int NPuzzle::Board::getLastDirection() const{
    return lastDirection;
}
inline int NPuzzle::Board::getSize(){
    return size;
}
inline int NPuzzle::getTotalMoves() const{
    return totalMoves;
}
inline void NPuzzle::setTotalMoves(){
    totalMoves=0;
}
char NPuzzle::getDirection(){
    //get a valid direction from user
    char d;
    cout << "Your Move: ";
    cin >> d;
    while (d!='L' && d!='R' && d!='U' && d!='D' && d!='I' && d!='S' && d!='Q'&& d!='V' && d!='T' && d!='E' && d!='O'){

        cout << "Please enter a valid value: ";
        cin >> d;
    }
    return d; //return 
}
void NPuzzle::Board::print() const{
    //print puzzle 
    int i,j,k;
    cout << endl;
    for ( i = 0; i < row; i++)
    {
        //at the beginning print --------
        for ( k = 0; k < column*3+1; k++) cout << "-";
        cout << endl;
        //now prints numbers
        for ( j = 0; j < column; j++)
        {
            cout << "|";
            if (puzzle[i][j]==-1)
                //if number is zero then print space
                 cout << "  ";
            else if (puzzle[i][j]==0)
                cout << "00";
            else if (puzzle[i][j]<10 && puzzle[i][j]!=0 )
                cout << "0" << puzzle[i][j];
            else
                cout << puzzle[i][j];
        }
        cout << "|" << endl;
    }
    //at the end print ------
    for ( k = 0; k < column*3+1; k++) cout << "-";
    cout << endl << endl;
}
bool NPuzzle::Board::move(char move_direction,int flag){
    //make a move according to given parameter
    int i,j,temp;
    if (move_direction=='L') //left
    {
        for (i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if (puzzle[i][j]==-1) //find zero in order to moves the empty cell
                {
                    if (j==0) // if there is no room left side of empty cell
                    {
                        if (flag==0)
                           cout << "***You cannot move this direction!***" << endl;
                        return false;
                    }
                    else //if there is room
                    {
                        if (puzzle[i][j-1]==0)//if it is impossible position warn the user
                        {
                            if (flag==0)
                                cout << "***You cannot move this direction!***" << endl;
                            return false;
                        }
                        else
                        {
                            //swap the 0 and left tile
                            temp=puzzle[i][j];
                            puzzle[i][j]=puzzle[i][j-1];
                            puzzle[i][j-1]=temp;
                            return true;
                        }
                        
                    }
                }
                
            }
            
            
        }

    }
    else if (move_direction=='R') //right
    {
        for (i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++) 
            {
                if (puzzle[i][j]==-1) //find zero in order to moves the empty cell
                {
                    if (j==(column-1)) // if there is no room right side of empty cell
                    {
                        if (flag==0)
                           cout << "***You cannot move this direction!***" << endl;
                        return false;
                    }
                    else //if there is room
                    {
                        if (puzzle[i][j+1]==0)//if it is impossible position warn the user
                        {
                            if (flag==0)
                                cout << "***You cannot move this direction!***" << endl;
                            return false;
                        }
                        else
                        {
                            //swap the 0 and right tile
                            temp=puzzle[i][j];
                            puzzle[i][j]=puzzle[i][j+1];
                            puzzle[i][j+1]=temp;
                            return true;
                        }
                    
                    }
                    
                }
                
                
            }
            
        }
    }
    else if (move_direction=='U') //up
    {
        for (i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if (puzzle[i][j]==-1) //find zero in order to moves the empty cell
                {
                    if (i==0) // if there is no room up side of empty cell
                    {
                        if (flag==0)
                           cout << "***You cannot move this direction!***" << endl;
                        return false;
                    }
                    else //if there is room
                    {
                        if (puzzle[i-1][j]==0)//if it is impossible position warn the user
                        {
                            if (flag==0)
                                cout << "***You cannot move this direction!***" << endl;
                            return false;
                        }
                        else
                        {
                            //swap the 0 and up tile
                            temp=puzzle[i][j];
                            puzzle[i][j]=puzzle[i-1][j];
                            puzzle[i-1][j]=temp;
                            return true;
                        }
                        
                        
                    }
                    
                }
                
            }
            
        }
    }
    else if (move_direction=='D') //down
    {
        for (i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if (puzzle[i][j]==-1) //find zero in order to moves the empty cell
                {
                    if (i==(row-1)) // if there is no room down side of empty cell
                    {
                        if (flag==0)
                           cout << "***You cannot move this direction!***" << endl;
                        return false;
                    }
                    else //if there is room
                    {
                        if (puzzle[i+1][j]==0)//if it is impossible position warn the user
                        {
                            if (flag==0)
                                cout << "***You cannot move this direction!***" << endl;
                            return false;
                        }
                        else
                        {
                            //swap the 0 and down tile
                            temp=puzzle[i][j];
                            puzzle[i][j]=puzzle[i+1][j];
                            puzzle[i+1][j]=temp;
                            return true; 
                        }
                        
                    }
                    
                }
                
            }
            
        }
    }
    else 
    {
        cout << "error!";
    }
    
}
void NPuzzle::choice(char userWants){
    //check for other choices of user
    switch(userWants){
    case 'I': //intelligent move
        moveIntelligent();
        totalMoves++;
        break;
    case 'S': //shuffle
        shuffle(game_board.getSize());//suffle the puzzle size*size time
        break;
    case 'Q': //quit
        Quit();
        break;
    case 'V': //solve puzzle new intelligent method(from hw2)
        solvePuzzle();
        break;
    case 'T': 
        printReport();
        break;
    case 'E': //save to file
        game_board.writeToFile(game_board.takeFileName(1));
        break;
    case 'O': //take from file
        if (game_board.readFromFile(game_board.takeFileName(2)))
            totalMoves=0; //set total move  
        break;
    default:
        cout << "Please Enter Correctly!" << endl;
        break; 
    }
}
bool NPuzzle::Board::is_solved(){
    //this function to check Is the game over ?
    int i,j,currentvalue=1;
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < column; j++)
        {
            if (puzzle[i][j]!=0)
            {
                if (puzzle[i][j]!=currentvalue)
                {
                    if (i==row-1 && j==column-1)
                    {
                        if (puzzle[i][j]==-1) // check for empty cell
                        {
                            return true;
                        } 
                        else
                            return false;
                    }
                    else
                        return false;
                }
                currentvalue++;
            }
            
        }
        
    }
}

int NPuzzle::moveIntelligent(){
    //this function to make an intelligent moves by using manhattan+haming distance which I calculated them in createSubPuzzleAndCheckThem function
    srand(time(NULL));
    int result,i,direction,number;
    int distance[4]; //to keep each direction's manhattan+haming+tile's manhattan value.
    // distance[0]=left , distance[1]=right , distance[2]=up, distance[3]=down 
    bool flag=false; 
    /* for each 7 intelligent move make 1 random move*/
    if (intelligentMoves==7)
    {
        intelligentMoves=0;
        moveRandom(1);
        return 0;
    }
    else
    {
        result=game_board.createSubPuzzleAndCheckThem(distance); //get minumum manhattan+haming+tile's manhattan to choose best way
        for ( i = 0; i < 4; i++)
        {
            if (distance[i]==result)
            {
                if (!flag) //if we didn't find best way
                {
                    //you can move to the that direction as a best way
                    direction=i;
                    flag=true;
                }
                else // if we have same minumum value then choose one of them randomly.
                {
                    number=rand()%2;
                    if (number==1)
                    {
                        direction=i;
                        flag=true;
                    }
                            
                }
            }    
        }
        if (flag) // if we find a best way
        {
            if (direction==0)
                game_board.move('L',1);
            else if (direction==1)
                game_board.move('R',1);
            else if (direction==2)
                game_board.move('U',1);
            else if (direction==3)
                game_board.move('D',1);
            getEnd();
        }
        else//if didn't find choose randomly
        {
            for (i = 0; i < 4; i++)
            {
                if (distance[i] != -1)
                {
                    direction=i;
                    break;
                }
                
            }
        }
        game_board.setLastDirection(direction); //update last direction
        intelligentMoves++;
        return distance[direction]; //return minumum value
    }
    
}
int NPuzzle::Board::createSubPuzzleAndCheckThem(int arr[4]){
    //this function checks all direction of empty tile can go, to find the best direction
    //in order to do that in here I calculated for all tile the distance from place that tile is there now to tile's place on solution, this is called as manhattan
    //also I calculated number of tiles which is not on own place, this is called as hamming
    //lastly I calculated for just one tile which will change it's position with empty tile the distance from place that tile is there now to tile's place on solution
    // at he end I sum these three result((manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)) 
    // and I found minumum result among  all direction of empty tile can go, and I returned minimum value 
    int i,min=10000,coord[2];
    for (i = 0; i < 4; i++) arr[i]=-1;
    bool left,right,up,down;
    left=move('L',1); // make a temporary move to the left
    if (left) //if there is room
    {
        findCoordinatesOfEmpty(coord);// find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[0]=sumManhattanOfAllTiles() + calculateManhattanOfOneTile(puzzle[coord[0]][coord[1]+1],coord[0],coord[1]+1);
        move('R',1);//return back to the orijinal
    }
    right=move('R',1); // make a temporary move to the right
    if (right) // if there is room
    {
        findCoordinatesOfEmpty(coord); // find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[1]=sumManhattanOfAllTiles()+ calculateManhattanOfOneTile(puzzle[coord[0]][coord[1]-1],coord[0],coord[1]-1); 
        move('L',1);//return back to the orijinal
    }
    up=move('U',1); // make a temporary move to the up
    if (up) //if there is room
    {
        findCoordinatesOfEmpty(coord); //find find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[2]=sumManhattanOfAllTiles()+ calculateManhattanOfOneTile(puzzle[coord[0]+1][coord[1]],coord[0]+1,coord[1]);
        move('D',1);//return back to the orijinal
    }
    down=move('D',1);; // make a temporary move to the down
    if (down) //if there is room
    {
        findCoordinatesOfEmpty(coord); // find find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[3]=sumManhattanOfAllTiles()+ calculateManhattanOfOneTile(puzzle[coord[0]-1][coord[1]],coord[0]-1,coord[1]);
        move('U',1);//return back to the orijinal
    }
    /*set the last direction to not make same move*/
    /* 0-left / 1-right / 2-up / 3-down */ 
    switch (getLastDirection())
    {
    case 0:
        setLastDirection(1);
        break;
    case 1:
        setLastDirection(0);
        break;
    case 2:
        setLastDirection(3);
        break;
    case 3:
        setLastDirection(2);
        break;        
    default:
        break;
    }
    // find minumum distance among all direction of empty tile can go
    for (i = 0; i < 4; i++){
    
        if(arr[i] != -1) // if we can move that direction
        {
            if (i!=getLastDirection()) //if our direction different than last direction
            {
                if (arr[i]<min) //find minimum distance
                {
                    min=arr[i];
                }
            }
            else //if i is last direction then skip it.
            {
                 arr[i]=-1; // to skip make -1
            }
            
        }
    }
    return min; //return minimum value
}
void NPuzzle::Board::findCoordinatesOfEmpty(int arr[2]){
    int i,j;
    for ( i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (puzzle[i][j]==-1)
            {
                arr[0]=i;
                arr[1]=j;
            }
            
        }
        
    }
    
}
int NPuzzle::Board::sumManhattanOfAllTiles(){
    //this function to calculate Manhattan + Hamming
   int i,j,sum_of_distance=0,tile,count=0,result=0,tileNo_OwnPlace;
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < column; j++)
        {
            if (puzzle[i][j]!=0 && puzzle[i][j]!=-1 ) //if tile different than impossible position and empty
            {
                tile=puzzle[i][j]; //choose it
                result=calculateManhattanOfOneTile(tile,i,j); //calculate it's manhattan distance
                if (result==0) // if it is own place
                    count++; //increment the count to calculate hamming
                sum_of_distance+=result; //sum all manhattan distance
            }
            
        }
        
    }
    tileNo_OwnPlace=(size-1)-count; // find number of tile that is not own place
    return sum_of_distance + tileNo_OwnPlace; //calculate and return Manhattan + Hamming
}
int NPuzzle::Board::calculateManhattanOfOneTile(int tile,int x_position,int y_position){
    //this function to calculate manhattan distance of only one tile
    //in order calculate for one tile's manhattan I subtracted coordinates of tile on the unsolved puzzle from
    // coordinates of tile on the solved puzzle.
    int i,j,short_distance=0;
    int tempPuzzle[9][9];
    for ( i = 0; i < 9; i++)
        for ( j = 0; j < 9; j++)
            tempPuzzle[i][j]=-1;
    getSolutionOfPuzzle(tempPuzzle); //get solution of puzzle
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j< column; j++)
        {
            if (tile==tempPuzzle[i][j]) //find tile on the final solution board
            {
                //then, calculate the it's manhattan distance by using it's coordinate
                //x_position and y position is the positon of tile on the unsolved puzzle
                //i and j is the positon of tile on the solved puzzle
                short_distance = absoluteValue(x_position-i) + absoluteValue(y_position-j);
            }
            
        }
        
    }
    return short_distance; // return manhattan distance of only one tile
}
int NPuzzle::Board::absoluteValue(int value){
    //get the absolute value of the given number
    if (value<0)
        return value*(-1);
    else
        return value;
    
}
void NPuzzle::solvePuzzle(){
    //Makes an attempt to solve the puzzle using my own algorithm from hw2
    double avarage,avarage2;
    int sumOfMinumums,i,numberOfMoves;
    do
    {
        cout << "Problem is Solving..." << endl;   
        sumOfMinumums=0;
        //first make 10 intelligent move
        for (i = 0; i < 10; i++)
        {
            sumOfMinumums+=moveIntelligent();
            game_board.print();
            cout << "Problem is Solving..." << endl;
            totalMoves++; 
            getEnd();
            if (end){
                break;
            }
              
        }
        if (!end)
        {
            
            avarage=sumOfMinumums/10.0;
            sumOfMinumums=0;
            //then make 10 intelligent move again
            for (i = 0; i < 10; i++)
            {
                sumOfMinumums+=moveIntelligent();
                totalMoves++;
                game_board.print();
                cout << "Problem is Solving..." << endl; 
                getEnd();
                if (end){
                    break;
                }  
                
            }
            if (!end){
                game_board.print();
                avarage2=sumOfMinumums/10.0;
                // then compare these two 10 different moves if they are looks like each other then make 7 random moves
                if (avarage>=avarage2-1.8 && avarage<=avarage2+1.8)
                {
                    moveRandom(7);
                    getEnd();
                    totalMoves+=7;
                    game_board.print();
                    cout << "Problem is Solving..." << endl;
                }
                    
            }  
                    
        }
        sumOfMinumums=0;
        avarage=0.0;
        avarage2=0.0;
        if (totalMoves>1000000)
        {
            cout << "***I couldn't solve puzzle with 1.000.000 move :( ****" << endl;
            exit(1);
        }
        getEnd();
    } while (!end);
}
void NPuzzle::moveRandom(int NumberOfTimes){
    //make random moves given parameter times
    //actually it makes a valid random move 
    //since I use this function with shuffle and solvePuzzle I want to make a loop in this function.
    //as you know I can make a loop in the shuffle and solvePuzzle so there is no difference. 
    //I think this way is more efficent otherwise I have to call this function many times.
    srand(time(NULL));
    int i,number,range,array[4];
    for ( i = 0; i < NumberOfTimes; i++)
    {
        if (!end)
        {
           game_board.createSubPuzzleAndCheckThem(array);
            do
            {
                number=rand()%4; //chose a direction
            } while (array[number]==-1); // if direction has not room to go choose again(for valid move)
            game_board.setLastDirection(number);//set last direction
            if (number==0)
                game_board.move('L',1);
            else if (number==1)
                game_board.move('R',1);
            else if (number==2)
                game_board.move('U',1);
            else if (number==3)
                game_board.move('D',1);
                
        }
        else
        {
            break;
        }
        getEnd();//check when make random move
    }
}
bool NPuzzle::Board::readFromFile(string fileName){

    //get puzzle shape from file and fill puzzle array
    ifstream getNumbers;
    int i,j,tile,lenghtOfStr,columnNumber;
    auto sum=0,numberOfZero=0,rowNumber=0,count=0; //auto varible for integer variable
    string str;
    bool flag=true;
    // open file
    getNumbers.open(fileName);
    if (!getNumbers.is_open())
    {   
        //if doesn't open warn user
        cout << "File is not opened!!" << endl;
        return false;
    }
    else //if file opens
    {
        //get number of all tiles
        while (getNumbers >> str)
        {
            if (sizeofStr(str)!=0) 
            {
                sum++;
            }
            if (str=="00")
            {
                numberOfZero++;
            }
            
        }
        getNumbers.close();//close file to use again
        getNumbers.open(fileName);//open again
        //get the number of lines from file
        while (getline(getNumbers,str))
        {
            if (sizeofStr(str)!=0)
            {
                rowNumber++;
            }
            
        }
        //find column number by using all tile and row number
        columnNumber=sum/rowNumber;
        /*get one tile from file as a string then convert it to integer
        then assing it puzzle array if number is zero indicate the number of zero*/
        while(flag){
            getNumbers.close();//close
            getNumbers.open(fileName);//open again
            for ( i = 0; i < rowNumber; i++)
            {
                for (j = 0; j < columnNumber; j++)
                {
                    
                    getNumbers >> str; //get a tile
                    lenghtOfStr=sizeofStr(str);//get lenght of it
                    tile=convertStrToInt(str,lenghtOfStr);//convert it to int
                    puzzle[i][j]=tile;//push it array
                }
                
            }
            count++;
            if (flag  && count%2==1)
            {
                /*set size and reset the puzzle with solution*/
                setSize(rowNumber,columnNumber,sum-numberOfZero);
                reset();
            }
            if (count%2==0)
            {
                flag=false;
            }
                
        }
        
    }
    getNumbers.close();//close
    return true;

}
string NPuzzle::Board::takeFileName(int flag){
    //take file name from user
    string filename;
    bool validty;
    if (flag==1)
        cout << "Please enter the file name to save it: ";
    else
        cout << "Please enter the file name to load it: ";
    /*Check for validty*/
    while(!(cin >> filename)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please Enter a string: ";
    }
    return filename;
}
int NPuzzle::Board::sizeofStr(string str) const{
    //find the sizeof string
    int i=0;
    for (i = 0; str[i]!='\0'; i++);
    return i;
    
}
int NPuzzle::Board::convertStrToInt(string str,int sizeOfStr){
    //convert the given string to integer
    int digit,i,number=0;
    char onedigit;
    for ( i = 0; i < sizeOfStr; i++)
    {
        onedigit=str[i];
        if (onedigit>='0' && onedigit<='9' )
        {
            digit=onedigit-'0';//char to int
            number=number*10+digit;//return it a number by using mathematical stuff
        }
        else
        {
            return -1;//empty cell(bb)
        }
    
    }
    return number;
}
void NPuzzle::Board::writeToFile(string fileName){
    //fill file with a loadable shape file
    ofstream outStream;
    int i,j,zero=0;
    string empty="bb";
    string blank=" ";
    outStream.open(fileName); //open file
    /*check the file */
    if (!outStream.is_open())
    {
        cout << "File is not opened";
    }
    else
    {
       for ( i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if ( puzzle[i][j]==0)
                {
                    outStream << zero << zero << blank ;
                }
                else if (puzzle[i][j]==-1)
                {
                    outStream << empty << blank ;
                }
                else
                {
                    if (puzzle[i][j]<10)
                    {
                        outStream << zero << puzzle[i][j] << blank ;
                    }
                    else
                    {
                        outStream << puzzle[i][j] << blank ;
                    }   
                }
            }
            if (i!=row-1)
            {
                outStream << endl;
            }
        } 
    }
    
}
void NPuzzle::printReport() const{
    //Prints a report about how many moves have been done since reset and
    //if the solution is found
    if (end)
        cout << "Game over" << endl << "Total Moves: " << totalMoves << endl;
    else
        cout << "Game is not over" << endl << "Total Moves: " << totalMoves << endl;
    
}
void NPuzzle::Quit(){
    //finish the program
    exit(1);
}

