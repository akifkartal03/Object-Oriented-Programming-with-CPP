#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
class NPuzzle{
private:
    bool end;
    //private inner class
    class Board{
    private:
        //member variables of Board
        vector<vector<int>> puzzle;
        int totalMoves,numberOfPuzzle;
        char lastDirection;
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
        int operator()(int index1,int index2) const;
        bool operator==(const Board& b2);
        int NumberOfBoards();
        char lastMove();
        int numberofMoves() const;
        /*-----my helper functions for these functions-----*/
        int takeSize();
        bool checkSize(int input);
        int getPuzzleSize(int flag) const;
        int sizeofStr(string str) const;
        int convertStrToInt(string str,int sizeOfStr);
        void getSolutionOfPuzzle(vector<vector<int>>& solutionOfPuzzle);
        void setLastDirection(char last);
        void setNumberOfBoards();
        string takeFileName(int flag) const;
        void setTotalMoves(bool flag);
        void initialVector();
        void setPuzzle(int newValue,int i1,int j1);
    };
    Board main_board; // my real time board as private
    vector<Board> game_boards; // my vector of Board objects as private to apply solving algorithm 
    
public:
    NPuzzle();//constructor
    void print() const;
    void printReport() const;
    bool readFromFile(string fileName);
    void writeToFile(string fileName);
    void shuffle(int N);
    void reset();
    void setSize(int r,int c,int s);
    void moveRandom(int NumberOfTimes);
    bool move(char move_direction,int flag); 
    void solvePuzzle();
    friend ostream& operator<<(ostream& outstream,const NPuzzle& b1);
    friend istream& operator>>(istream& instream, NPuzzle& b1);
    /*-----my other helper functions for these functions-----*/
    void gameRealTime(string fileName,int gameType);
    bool getEnd();
    void Quit();
    char getDirection();
    void choice(char userWants); 
    void getPossibleMove(char direction[4]);
    int checkAndPushBackPossibleDirections(Board temp);
    bool is_same(Board temp,char direction);
    int getPuzzleSize(int flag) const;
    string takeFileName(int flag) const;
    void moveInverse();
    
};
int main(int argc,char *argv[]){
    NPuzzle n1;//create an object
    if (argc<2) //if there is no filename
        n1.gameRealTime("",1); //begin with like hw1
    else if(argc==2){
        n1.gameRealTime(argv[1],2); //begin with like hw2
    }
    else
        cout << "Enter Correctly!" << endl;
    return 0;
}
NPuzzle::NPuzzle(){ //implement constructor
    end=false;
    game_boards.resize(0);
}
NPuzzle::Board::Board(){ //implement constructor
    lastDirection='S';totalMoves=0;numberOfPuzzle=1;//real time puzzle
}
void NPuzzle::gameRealTime(string fileName,int gameType){
    //play game
    int size;
    bool is_solvable;
    char prefer;
    if (gameType==1)//if a filename didn't enter
    {
        size=main_board.takeSize();//take size
        setSize(size,size,size*size); //set size with new size
        reset();
        shuffle(main_board.getPuzzleSize(1)*main_board.getPuzzleSize(1)*2);//shuffle the solved puzzle to get solvable random puzzle.
    }
    else{ //if a filename entered
         readFromFile(fileName);
    }
    main_board.is_solved();//check
    main_board.setTotalMoves(true);//set total move with zero
    while (!end)
    {
        cout << *this; //print();
        prefer=getDirection();
        if (prefer!='L' && prefer!='R' && prefer!='U' && prefer!='D')
            choice(prefer); //choice of user is not a direction
        else{
            if (move(prefer,0))
                 main_board.setTotalMoves(false);
        }
    }
    cout << endl  << "Problem Solved!" << endl; 
    cout << "Total number of moves " << main_board.numberofMoves() << endl;
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
    // set the size of vector puzzle
    int i;
    puzzle.resize(r);
    for ( i = 0; i < puzzle.size(); i++)
    {
        puzzle[i].resize(c);
    }
    initialVector(); //initialize puzzle with -1
}
void NPuzzle::Board::initialVector()
{
    int i,j;
    for ( i = 0; i < puzzle.size(); i++)
    {
        for ( j = 0; j < puzzle[i].size(); j++)
        {
            puzzle[i][j]=-1;
        }
        
    }
    
}
void NPuzzle::shuffle(int N){
    //to shuffle make N times random moves
    moveRandom(N);
    main_board.setLastDirection('S');
    game_boards.resize(1);
    game_boards[0]=main_board;
}
void NPuzzle::moveRandom(int NumberOfTimes){
    //make a random move
    srand(time(NULL));
    int i,number,range;
    char directions[4];
    for ( i = 0; i < NumberOfTimes; i++)
    {
        if (!end)
        {
            getPossibleMove(directions);
            do
            {
                number=rand()%4; //chose a direction
            } while (directions[number]=='S'); // if direction has not room to go choose again
            main_board.setLastDirection(directions[number]);
            if (number==0)
                main_board.move('L',1);
            else if (number==1)
                main_board.move('R',1);
            else if (number==2)
                main_board.move('U',1);
            else if (number==3)
                main_board.move('D',1);
                
        }
        else
        {
            break;
        }
        getEnd();
    }
    game_boards.resize(1);
    game_boards[0]=main_board;
}
void NPuzzle::getPossibleMove(char direction[4]){
    for (int i = 0; i < 4; i++) direction[i]='S';
    if (main_board.move('L',1)) //if there is room
    {
        direction[0]='L';
        main_board.move('R',1);
    }
    if (main_board.move('R',1)) // if there is room
    {
        direction[1]='R';
        main_board.move('L',1);
    }
    if (main_board.move('U',1)) //if there is room
    {
        direction[2]='U';
        main_board.move('D',1);
    }
    if (main_board.move('D',1)) //if there is room
    {
        direction[3]='D';
        main_board.move('U',1);
    }
    /*set the last direction to not make same move*/
    switch (main_board.lastMove())
    {
    case 'L':
        main_board.setLastDirection('R');
        break;
    case 'R':
        main_board.setLastDirection('L');
        break;
    case 'U':
        main_board.setLastDirection('D');
        break;
    case 'D':
        main_board.setLastDirection('U');
        break;        
    default:
        break;
    }
    //check for last move
    for (int i = 0; i < 4; i++){
    
        if(direction[i] != 'S') 
        {
            if (direction[i]==main_board.lastMove()) //if our direction equal last direction
            {
                direction[i]='S';
            }
        }
    }
}
void NPuzzle::Board::reset(){
    //reset puzzle with solution
    int i,j,currentvalue=1;
    for ( i = 0; i < puzzle.size(); i++)
    {
        for ( j = 0; j < puzzle[i].size(); j++)
        {
            
            if (i==puzzle.size()-1 && j==puzzle[i].size()-1)
                puzzle[i][j]=-1;
            else{

                if (puzzle[i][j]!=0)
                {
                    puzzle[i][j]=currentvalue;
                    currentvalue++;
                }
            }
        }
        
    }
    
}
void NPuzzle::Board::getSolutionOfPuzzle(vector<vector<int>>& solutionOfPuzzle){
    //fill the parameter vector puzzle with solution to use at the future
    int i,j,currentvalue=1;
    for ( i = 0; i < puzzle.size(); i++)
    {
        for ( j = 0; j < puzzle[i].size(); j++)
        {
            
            if (i==puzzle.size()-1 && j==puzzle[i].size()-1)
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
    end=main_board.is_solved();
    return end;
}
/* my inline functions*/
inline void NPuzzle::Board::setLastDirection(char last){
    lastDirection=last;
}
inline char NPuzzle::Board::lastMove(){
    return lastDirection;
}
inline int NPuzzle::Board::getPuzzleSize(int flag) const{
    if (flag==1)
        return puzzle.size();//return row
    else
        return puzzle[0].size(); // return column
}
inline int NPuzzle::Board::numberofMoves() const{
    return totalMoves;
}
inline int NPuzzle::Board::NumberOfBoards(){
    return numberOfPuzzle;
}
inline void NPuzzle::Board::setNumberOfBoards(){
    numberOfPuzzle++;
}
inline void NPuzzle::Board::setTotalMoves(bool flag){
    if (flag)
        totalMoves=0;
    else
        totalMoves+=1;
}
int NPuzzle::getPuzzleSize(int flag) const{
    main_board.getPuzzleSize(flag);
}
char NPuzzle::getDirection(){
    //get a valid direction from user
    char d;
    cout << "Your Move: ";
    cin >> d;
    while (d!='L' && d!='R' && d!='U' && d!='D' && d!='S' && d!='Q'&& d!='V' && d!='T' && d!='E' && d!='O'){

        cout << "Please enter a valid value: ";
        cin >> d;
    }
    return d; //return 
}
void NPuzzle::Board::print() const{ 
   //print puzzle 
    int i,j,k;
    cout << endl;
    for ( i = 0; i < puzzle.size(); i++)
    {
        //at the beginning print --------
        for ( k = 0; k < puzzle[0].size()*3+1; k++) cout << "-";
        cout << endl;
        //now prints numbers
        for ( j = 0; j < puzzle[0].size(); j++)
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
    for ( k = 0; k < puzzle[0].size()*3+1; k++) cout << "-";
    cout << endl << endl;
}
bool NPuzzle::Board::move(char move_direction,int flag){
    //make a move according to given parameter by doing check
    int i,j,temp;
    if (move_direction=='L') //left
    {
        for (i = 0; i < puzzle.size(); i++)
        {
            for ( j = 0; j < puzzle[i].size(); j++)
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
        for (i = 0; i < puzzle.size(); i++)
        {
            for ( j = 0; j < puzzle[i].size(); j++) 
            {
                if (puzzle[i][j]==-1) //find zero in order to moves the empty cell
                {
                    if (j==(puzzle[i].size()-1)) // if there is no room right side of empty cell
                    {
                        if (flag==0)
                           cout << "***You cannot move this direction!***" << endl;
                        return false;
                    }
                    else if (j!=(puzzle[i].size())) //if there is room
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
        for (i = 0; i < puzzle.size(); i++)
        {
            for ( j = 0; j < puzzle[i].size(); j++)
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
        for (i = 0; i < puzzle.size(); i++)
        {
            for ( j = 0; j < puzzle[i].size(); j++)
            {
                if (puzzle[i][j]==-1) //find zero in order to moves the empty cell
                {
                    if (i==(puzzle.size()-1)) // if there is no room down side of empty cell
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
    case 'S': //shuffle
        shuffle(main_board.getPuzzleSize(1)*main_board.getPuzzleSize(1));
        break;
    case 'Q': //quit
        Quit();
        break;
    case 'V': //solve puzzle new intelligent method
        solvePuzzle();
        break;
    case 'T': 
        printReport();
        break;
    case 'E': //save to file
        writeToFile(main_board.takeFileName(1));
        break;
    case 'O': //take from file
        cin >> *this; //use operator(for testing)
        main_board.setTotalMoves(true); //totalMoves=0
        break;
    default:
        cout << "Please Enter Correctly!" << endl;
        break; 
    }
}
bool NPuzzle::Board::is_solved(){
    //this function to check Is the game over ?
    int i,j,currentvalue=1;
    for ( i = 0; i < puzzle.size(); i++)
    {
        for ( j = 0; j < puzzle[i].size(); j++)
        {
            if (puzzle[i][j]!=0)
            {
                if (puzzle[i][j]!=currentvalue)
                {
                    if (i==puzzle.size()-1 && j==puzzle[i].size()-1)
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
void NPuzzle::solvePuzzle(){
    //Makes an attempt to solve the puzzle using the new algorithm.
    int i=0;
    cout << "Problem is solving..." << endl << "Filling the vector and searching for solution..." << endl;
    while (!end)
    {
        game_boards[i].setTotalMoves(false);//totalMoves++
        checkAndPushBackPossibleDirections(game_boards[i]);
        if (end)
            moveInverse();
        else
             i++; //contiune searching for...
    }
}
int NPuzzle::checkAndPushBackPossibleDirections(Board temp){
    if (!end && temp.move('L',1)) //if there is room
    {
        end=temp.is_solved();//check is it solution?
        is_same(temp,'L'); // check and push_back to vector
        if (!end)
            temp.move('R',1); //return back original puzzle
    }
    if (!end && temp.move('R',1)) // if there is room
    {
        end=temp.is_solved();//check is it solution?
        is_same(temp,'R');// check and push_back to vector
        if (!end)
            temp.move('L',1); //return back original puzzle
    }
    if (!end && temp.move('U',1)) //if there is room
    {
        end=temp.is_solved();
        is_same(temp,'U');
        if (!end)
            temp.move('D',1);
    }
    if (!end && temp.move('D',1)) //if there is room
    {
        end=temp.is_solved();
        is_same(temp,'D');
        if (!end)
            temp.move('U',1);
    }
}
bool NPuzzle::is_same(Board temp,char direction){
    /*check if the same board is already in the vector*/
    for (int i = 0; i < game_boards.size(); i++)
    {
        if (temp==game_boards[i]){
            return true;
        }
    }
    //if it is not then push_back it
    game_boards.push_back(temp);
    game_boards[game_boards.size()-1].setLastDirection(direction);//set direction
    game_boards[game_boards.size()-1].setNumberOfBoards();//set number
    return false;
}
void NPuzzle::moveInverse(){
    /*if the solution is found then we can go back to the original board by applying the inverse moves */
    /*while this process we should save the solving steps*/
    vector<char> solutionDirections;
    /*to make inverse move begin at end of the vector*/
    for ( int i = game_boards.size()-1; i > 0 ; i--)
    {

        if (game_boards[game_boards.size()-1]==game_boards[i])
        {
            solutionDirections.push_back(game_boards[i].lastMove()); //save the direction
            /*make inverse move*/
            switch (game_boards[i].lastMove())
            {
            case 'L':
                game_boards[game_boards.size()-1].move('R',1);
                break;
            case 'R':
                game_boards[game_boards.size()-1].move('L',1);
                break;
            case 'U':
                game_boards[game_boards.size()-1].move('D',1);
                break;
            case 'D':
                game_boards[game_boards.size()-1].move('U',1);
                break;
            default:
                break;
            }
        }
            
    }
    /*apply the solution steps on our orijinal puzzle and solve it.*/
    for (int j = solutionDirections.size()-1; j >=0 ; j--)
    {
        main_board.move(solutionDirections[j],1);
        main_board.setTotalMoves(false);//totalmoves++
        main_board.print();
    }
    
}
bool NPuzzle::Board::readFromFile(string fileName){
    //get puzzle shape from file and fill puzzle array
    ifstream getNumbers;
    int i,j,tile,lenghtOfStr,columnNumber;
    auto sum=0,numberOfZero=0,rowNumber=0; //auto varible for integer variable
    string str;
    // open file
    getNumbers.open(fileName);
    if (!getNumbers.is_open())
    {   
        //if doesn't open warn user and terminate program.
        cout << "File is not opened!!" << endl;
        exit(1);
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
        getNumbers.close();//close
        getNumbers.open(fileName);//open again
        //get one tile from file as a string then convert it to integer
        //then assing it puzzle array if number is zero indicate the number of zero
        //set size
        setSize(rowNumber,columnNumber,sum-numberOfZero);
        reset();
        for ( i = 0; i < rowNumber; i++)
        {
            for (j = 0; j < columnNumber; j++)
            {
                
                getNumbers >> str; //get a tile
                lenghtOfStr=sizeofStr(str);//get lenght of it
                if (lenghtOfStr!=2) //check for proper file shape
                {
                    cout << "Your File Format is not good!"<< endl
                        << "Please correct it." << endl;
                    exit(1);
                }
                else
                {
                    tile=convertStrToInt(str,lenghtOfStr);//convert it to int
                    puzzle[i][j]=tile;//push it array
                }
            }
            
        }
        
    }
    getNumbers.close();//close
    return true;
}
string NPuzzle::Board::takeFileName(int flag) const{
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
string NPuzzle::takeFileName(int flag) const{
    return main_board.takeFileName(flag);
}
int NPuzzle::Board::sizeofStr(string str) const{
    //find the sizeof string
    int i=0;
    for (i = 0; str[i]!='\0'; i++);
    return i;
    
}
int NPuzzle::Board::convertStrToInt(string str,int sizeOfStr){
    //get one string and convert it integer
    int digit,i,number=0;
    char onedigit;
    for ( i = 0; i < sizeOfStr; i++)
    {
        onedigit=str[i];
        if (onedigit>='0' && onedigit<='9' )
        {
            digit=onedigit-'0';//char to int
            number=number*10+digit;//return it number by using math stuff
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
        for ( i = 0; i < puzzle.size(); i++)
        {
            for ( j = 0; j < puzzle[i].size(); j++)
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
            if (i!=puzzle.size()-1)
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
        cout << "Game over" << endl << "Total Moves: " << main_board.numberofMoves() << endl;
    else
        cout << "Game is not over" << endl << "Total Moves: " << main_board.numberofMoves() << endl;
   
}
void NPuzzle::Board::setPuzzle(int newValue,int i1,int j1){
    //update puzzle cell
    puzzle[i1][j1]=newValue;
}
int NPuzzle::Board::operator()(int index1,int index2) const{
    //index operator
    /*Terminates program if the indexes are not valid*/
    if (index1>=0 && index1 <puzzle.size())
    {
        if (index2>=0 && index2<puzzle[0].size())
        {
           return puzzle[index1][index2]; 
        }
        else
        {
            exit(1);
        }
        
    }
    else
    {
        exit(1);
    }
    
}
bool NPuzzle::Board::operator==(const Board& b1){

    for (int i = 0; i < puzzle.size(); i++)
    {
        for (int j = 0; j < puzzle[0].size(); j++)
        {
            if (puzzle[i][j]!=b1.puzzle[i][j])
            {
                return false;
            }
            
        }
        
    }
    return true;
}
ostream& operator<<(ostream& outstream,const NPuzzle& b1){
    //print puzzle by using index operator("()")
    //getPuzzleSize(1) ==> row
    //getPuzzleSize(2) ==> column
    int i,j,k;
    outstream << "\n";
    for ( i = 0; i < b1.getPuzzleSize(1); i++)
    {
        //at the beginning print --------
        for ( k = 0; k < b1.getPuzzleSize(2)*3+1; k++) outstream << "-";
        outstream << "\n";
        //now prints numbers
        for ( j = 0; j < b1.getPuzzleSize(2); j++)
        {
            outstream << "|";
            if (b1.main_board(i,j)==-1)
                //if number is zero then print space
                 outstream << "  ";
            else if (b1.main_board(i,j)==0)
                outstream << "00";
            else if (b1.main_board(i,j)<10 && b1.main_board(i,j)!=0 )
                outstream << "0" << b1.main_board(i,j);
            else
                outstream << b1.main_board(i,j);
        }
        outstream << "|" << "\n";
    }
    //at the end print ------
    for ( k = 0; k < b1.getPuzzleSize(2)*3+1; k++) outstream << "-";
    outstream << "\n" << "\n";
    return outstream;
}
istream& operator>>(istream& instream,NPuzzle& b1){
    /*read puzzle from file since I don't want to make copy-past*/
    /*I called readfromfile fuction*/
    b1.readFromFile(b1.takeFileName(2));
    return instream;
}
bool NPuzzle::readFromFile(string fileName){

    main_board.readFromFile(fileName);
    game_boards.resize(1);
    game_boards[0]=main_board;
}
void NPuzzle::reset(){
    main_board.reset();
    game_boards.resize(0);
}
void NPuzzle::print() const{
    main_board.print();
}
void NPuzzle::writeToFile(string fileName){

    main_board.writeToFile(fileName);
}
void NPuzzle::setSize(int r,int c,int s){
    main_board.setSize(r,c,s);
}
bool NPuzzle::move(char move_direction,int flag){
    main_board.move(move_direction,flag);
    game_boards.resize(1);
    game_boards[0]=main_board;
} 
void NPuzzle::Quit(){
    //finish the program
    exit(1);
}