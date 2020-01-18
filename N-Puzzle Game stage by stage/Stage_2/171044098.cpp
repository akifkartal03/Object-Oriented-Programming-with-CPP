#include<iostream>
#include<cstdlib>
#include <ctime>
#include<string>
#include<fstream>
using namespace std;
/*My function prototypes*/
//I explained their tasks in the their definition.
string takeFileName(int state);
bool initializePuzzleFromFile(int puzzle[][9],int &row,int &column,string fileName,int &size);//
int sizeofStr(string str);
int convertStrToInt(string str,int sizeOfStr);
int takeSize();//
bool checkSize(int input);
bool initializePuzzleRandomly(int puzzle[][9],int size);
bool checkRandomArr(int arr[],int size,int number);
int countInversionNumber(int puzzle[][9],int x_position,int y_position,int row,int column,int tile);
void findCoordinatesOfEmpty(int puzzle[][9],int row,int column,int arr[2]);
void gameRealTime(int puzzle[][9],int row,int column,int size,string fileName,int flag);
void printPuzzleRealtime(int puzzle[][9],int row,int column);//
char getDirectionOfMove();
bool moveLeft(int puzzle[][9],int row,int column,int flag);//
bool moveRight(int puzzle[][9],int row,int column,int flag);//
bool moveUp(int puzzle[][9],int row,int column,int flag);//
bool moveDown(int puzzle[][9],int row,int column,int flag);//
int findMinimumCase(int puzzle[][9],int row,int column,int &lastDirection,int size);//
int createSubPuzzleAndCheckThem(int puzzle[][9],int row,int column,int arr[4],int lastDirection,int size);
void returnBack(int tempPuzzle[][9],int puzzle[][9],int row,int column);
int sumManhattanOfAllTiles(int tempPuzzle[][9],int puzzle[][9],int row,int column,int size);
int calculateManhattanOfOneTile(int puzzle[][9],int tile,int x_position,int y_position,int row,int column);
void getSolution(int tempPuzzle[][9],int puzzle[][9],int row,int column);//
int absoluteValue(int value);
bool is_end(int puzzle[][9],int row,int column);//
bool shufflePuzzle(int puzzle[][9],int row,int column,int size,int task);//
void saveToFile(int puzzle[][9],int row,int column,string filename);//
void Quit();
int main(int argc,char *argv[]){
    const int maxSize=9;//define a costant size
    int puzzle[maxSize][maxSize],r,c,size,sizeofPuzzle; 
    if (argc<2) //if there is no filename
    {
        sizeofPuzzle=takeSize(); //take a size like hw1
        r=sizeofPuzzle;//update row
        c=sizeofPuzzle;//update column
        size=sizeofPuzzle*sizeofPuzzle;//update the big size
        gameRealTime(puzzle,r,c,size,"",1);//start the game according to hw1
    }
    else
    {
        gameRealTime(puzzle,r,c,size,argv[1],2);//start the according to hw2
    }
    return 0;
}
string takeFileName(int state){
    //take file name from user
    string filename;
    bool validty;
    if (state==1)
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
bool initializePuzzleFromFile(int puzzle[][9],int &row,int &column,string fileName,int &size){
    //get puzzle shape from file and fill puzzle array
    ifstream getNumbers;
    int i,j,tile,lenghtOfStr,columnNumber;
    auto sum=0,numberOfZero=0,rowNumber=0; //auto varible for integer variable
    string str;
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
        /*get one tile from file as a string then convert it to integer
        then assing it puzzle array if number is zero indicate the number of zero*/
        for ( i = 0; i < rowNumber; i++)
        {
            for (j = 0; j < columnNumber; j++)
            {
                
                getNumbers >> str;
                lenghtOfStr=sizeofStr(str);//get lenght
                tile=convertStrToInt(str,lenghtOfStr);//convert it
                puzzle[i][j]=tile;//fill array
                if (tile==0)
                {
                    numberOfZero++; 
                }
                
            }
            
        }
        /*update values*/
        size=sum-numberOfZero;
        row=rowNumber;
        column=columnNumber;
        getNumbers.close();    
    }
    
    return true;
    
}
int sizeofStr(string str){
    //find the sizeof string
    int i=0;
    for (i = 0; str[i]!='\0'; i++);
    return i;
    
}
int convertStrToInt(string str,int sizeOfStr){
    //get one string and convert it integer
    int digit,i,number=0;
    char onedigit;
    for ( i = 0; i < sizeOfStr; i++)
    {
        onedigit=str[i];
        if (onedigit>='0' && onedigit<='9' )
        {
            digit=onedigit-'0';//char to int
            number=number*10+digit;//return it number by using math
        }
        else
        {
            return -1;//empty cell(bb)
        }
    
    }
    return number;
    
}
int countInversionNumber(int puzzle[][9],int x_position,int y_position,int row,int column,int tile){
    // this function counts inversion number to find "unsolvable" puzzles.
    int i,j,number=0;
    for ( i = x_position; i < row; i++)
    {
        for ( j = y_position; j < column; j++)
        {
            if ((puzzle[i][j] < tile) && (puzzle[i][j]!=0) && (puzzle[i][j]!=-1))
                number++;
        }
        y_position=0;
    }
    return number;
}
int takeSize(){
    int size;
    bool validty;
    cout << "Please enter the problem size: ";
    /*Check for size validty(number or character)*/
    while(!(cin >> size)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please Enter a number: ";
    }
    //if it is not a character then,
    //check for correct size(3,4,...,9)
    validty=checkSize(size); 
    while (!validty)
    {
        cout << "Please enter a valid number(3,4,5,...,9): ";
        while(!(cin >> size)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please Enter a number: ";
        }
        validty=checkSize(size);
    }
    return size;
}
bool checkSize(int input){
    // this function is to check correct size
    const int size=7;// constant number of valid sizes
    int defaultsize[size]={3,4,5,6,7,8,9};
    for (int i = 0; i < 7; i++)
    {
        if (defaultsize[i]==input)
            return true;
    }
    return false;

}
bool initializePuzzleRandomly(int puzzle[][9],int size){
    // this function initialize the puzzle with random numbers
    srand(time(NULL));
    int i,j,number,range,k=0,sumOfInversion=0,rowOfZero;
    range=size*size;
    int randomArr[range],coord[2];
    bool flag;
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            number=rand()%range;//get random number between 0 and size*size
            flag=checkRandomArr(randomArr,size,number); // check random number to avoid get same number
            while (!flag) //if we get same number one of them others then create again
            {
                number=rand()%range;
                flag=checkRandomArr(randomArr,size,number);
                
            } // until being different
            // if different then save it on puzzle
            if (number==0)
            {
                puzzle[i][j]=-1;
            }
            else
            {
                puzzle[i][j]=number;
            }
            randomArr[k]=number; //save it on random array
            k++; //increment index of random array
        }

    }
    // check for unsolvable puzzle with inversion method
    // in this method if size is odd number calculate inversion number if even okey, if odd not okey
    //if size is even the empty tile's row counting from the bottom is even and number of inversions is odd then it is solvable
    // if the empty tile's row counting from the bottom is odd and number of inversions is even then it is solvable
    //otherwise for even size it is not unsolvable
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
            //count inversion number
            sumOfInversion+= countInversionNumber(puzzle,i,j,size,size,puzzle[i][j]);
    }
    if (size % 2!=0) //if size is odd number
    {
        if (sumOfInversion % 2 == 0)
            //if even okey
            return true;
        else
            //if odd not okey
            return false;
    }
    else //if size is even number
    {
        findCoordinatesOfEmpty(puzzle,size,size,coord);
        rowOfZero=size-coord[0];
        if (rowOfZero % 2 == 0)
        {
            if (sumOfInversion % 2 == 0)
                return false;
            else
                return true;
            
        }
        else
        {
            if (sumOfInversion % 2 == 0)
                return true;
            else
                return false;
        }
        
        
    }
    
    
}
bool checkRandomArr(int rndArr[],int size,int rndNumber){
    //check random number to avoid get same number one of them other numbers
    int i;
    for ( i = 0; i < size*size; i++)
    {
        if (rndArr[i]==rndNumber)
            //if same 
            return false;
    }
    //if not same
    return true;
}
void findCoordinatesOfEmpty(int puzzle[9][9],int row,int column,int arr[2]){
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
void gameRealTime(int puzzle[][9],int row,int column,int size,string fileName,int flag){
    //this function to play the game real time
    //auto integer varibles
    //double values with decltype
    auto totalMoves=0,lastDirection=5,queue=2,i=0,numberOfMoves=0,sumOfMinumums=0;
    decltype(lastDirection*3.5) avarage=0.0;
    decltype(lastDirection*3.5) avarage2=0.0;
    bool end=false,is_solvable,autoSolve=false,check=false;
    char moveDirection;
    string filenameToSave,filenameToLoad;
    if (flag==1)//if a filename didn't enter
    {
        check=true;
        do{ //get a puzzle filled randomly
            is_solvable=initializePuzzleRandomly(puzzle,row);
            
        }while (!is_solvable);
    
        
    }
    else //if a filename entered
    {
        //get a puzzle from file
        check=initializePuzzleFromFile(puzzle,row,column,fileName,size);
    }
    if (!check)
    {
        exit(1);
    }
    //start a game
    do //while game is not over
    {
        
        end=is_end(puzzle,row,column); //check for end
        printPuzzleRealtime(puzzle,row,column);//print puzzle
        if (!end)
        {
            if (!autoSolve) //if didn't choose "V" mode
            {
                moveDirection=getDirectionOfMove(); //get direction from user
            }
            else //if already choosen "V" mode contiune
            {
                moveDirection='V'; //choose otomaticly
            }
            //check direction
            switch(moveDirection){
            case 'L': //left
                if (moveLeft(puzzle,row,column,0))
                    totalMoves++;   
                break;
            case 'R': //right
                if (moveRight(puzzle,row,column,0))
                    totalMoves++;   
                break;
            case 'U': //up
                if (moveUp(puzzle,row,column,0))
                    totalMoves++;   
                break;
            case 'D': //down
                if (moveDown(puzzle,row,column,0))
                    totalMoves++;   
                break;
            case 'I': //intelligent move
                findMinimumCase(puzzle,row,column,lastDirection,size);
                totalMoves++;
                break;
            case 'S': //shuffle
                shufflePuzzle(puzzle,row,column,size,1);
                break;
            case 'Q': //quit
                Quit();
                break;
            case 'V': //solve puzzle new intelligent method
                cout << "Problem is Solving..." << endl;
                if (!autoSolve)
                    autoSolve=true;
                sumOfMinumums=0;
                //first make 10 intelligent move
                for (i = 0; i < 10; i++)
                {
                    
                    sumOfMinumums+=findMinimumCase(puzzle,row,column,lastDirection,size);
                    totalMoves++; 
                    end=is_end(puzzle,row,column);
                    if (end){

                        printPuzzleRealtime(puzzle,row,column);//print puzzle after move
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
                        
                        sumOfMinumums+=findMinimumCase(puzzle,row,column,lastDirection,size);
                        totalMoves++; 
                        end=is_end(puzzle,row,column);
                        if (end){

                            printPuzzleRealtime(puzzle,row,column);//print puzzle after move
                            break;
                        }  
                    }
                    if (!end){

                        avarage2=sumOfMinumums/10.0;
                        //compare these two 10 different moves if they are looks like each other and make 5 random moves
                        if (avarage>=avarage2-1.5 && avarage<=avarage2+1.5)
                        {
                            numberOfMoves=5;
                            end=shufflePuzzle(puzzle,row,column,size,numberOfMoves);
                            totalMoves+=numberOfMoves;
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
                break;
            case 'T': 
                if (!is_end(puzzle,row,column))
                {
                    cout << "Total number of moves " << totalMoves << endl;
                    cout << "Game is not over! " << endl;  
                }
                break;
            case 'E': //save to file
                filenameToSave=takeFileName(1);
                saveToFile(puzzle,row,column,filenameToSave);
                break;
            case 'Y': //take from file
                filenameToLoad=takeFileName(2);
                if (initializePuzzleFromFile(puzzle,row,column,filenameToLoad,size))
                    totalMoves=0;
                break;
            default:
                cout << "Please Enter Correctly!" << endl;
                break;
            }
        }
    }while (!end);
    //if game over
    //print results
    cout << endl  << "Problem Solved!" << endl; 
    cout << "Total number of moves " << totalMoves << endl; 
}
bool moveLeft(int puzzle[][9],int row,int column,int flag){
    //this function for move left
    int i,j,temp;
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
bool moveRight(int puzzle[][9],int row,int column,int flag){
    int i,j,temp;
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
bool moveUp(int puzzle[][9],int row,int column,int flag){
    int i,j,temp;
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
bool moveDown(int puzzle[][9],int row,int column,int flag){
    int i,j,temp;
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
void printPuzzleRealtime(int puzzle[][9],int row,int column){
    //print puzzle 
    int i,j,k,l;
    cout << endl;
    for ( i = 0; i < row; i++)
    {
        //at the beginning print --------
        for ( k = 0; k < column*3+1; k++)
        {
            cout << "-";
        }
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
            {
                cout << "0" << puzzle[i][j];
            }
            else
            {
                cout << puzzle[i][j];
            }
            
        }
        cout << "|";
        cout << endl; // new line
    }
    //at the end print ------
     for ( k = 0; k < column*3+1; k++)
    {
        cout << "-";
    }
    cout << endl;
    cout << endl;
}
char getDirectionOfMove(){
    //this function takes a letter from user to choice direction
    char moveDirection;
    cout << "Your Move: ";
    cin >> moveDirection;
    
    while (moveDirection!='L' && moveDirection!='R' && moveDirection!='U' && moveDirection!='D' && moveDirection!='I' && moveDirection!='S' && moveDirection!='Q'&& moveDirection!='V' && moveDirection!='T' && moveDirection!='E' && moveDirection!='Y'){

        cout << "Please enter a valid value: ";
        cin >> moveDirection;
    }
    return moveDirection; //return 
}
int findMinimumCase(int puzzle[][9],int row,int column,int &lastDirection,int size){
    //this function to make an intelligent moves by using manhattan+haming distance which I calculated them in createSubPuzzleAndCheckThem function
    //also in this function I used call by refence method for lastDirection since don't make the same move again
    srand(time(NULL));
    int result,i,direction,value,number;
    int distance[4]; //to keep each direction's manhattan+haming+tile's manhattan value.
    // distance[0]=left , distance[1]=right , distance[2]=up, distance[3]=down 
    int temp_Puzzle[9][9];//define a temp puzzle to check sub puzzles
    bool flag=false;
    value=lastDirection;
    returnBack(temp_Puzzle,puzzle,row,column);//fill the temp_puzzle with orijinal puzzle
    result=createSubPuzzleAndCheckThem(temp_Puzzle,row,column,distance,value,size); //get minumum manhattan+haming+tile's manhattan to choose best way
    for ( i = 0; i < 4; i++)
    {
        if (distance[i]==result)
        {
            if (i==0) //if the best way is left
            {
                if (lastDirection!=1) // if last move is not right 
                {
                    if (!flag) //if we didn't find best way
                    {
                        //you can move to the left as a best way
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
            else if (i==1) //if the best way is right
            {
               if (lastDirection!=0) // if last move is not left
                {
                    if (!flag) //if we didn't find best way
                    {
                        //you can move to the right as a best way
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
            else if (i==2) // if the best way is up
            {
               if (lastDirection!=3) // if last move is not down
                {
                    if (!flag) //if we didn't find best way
                    {
                        //you can move to the up as a best way
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
            else if (i==3) // if the best way is down
            {
               if (lastDirection!=2) // if last move is not up
                {
                    if (!flag) //if we didn't find best way
                    {
                        //you can move to the down as a best way
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
            
        }
                
    }

    if (flag) // if we find a best way
    {
        switch (direction)
        {
            case 0:// the best way is left
                moveLeft(puzzle,row,column,0); 
                //cout << "Problem is Solving..." << endl;
                break;
            case 1: // the best way is right
                moveRight(puzzle,row,column,0);
                //cout << "Problem is Solving..." << endl;
                break;
            case 2: // the best way is up
                moveUp(puzzle,row,column,0);
                //cout << "Problem is Solving..." << endl;
                break;
            case 3: // the best way is down
                moveDown(puzzle,row,column,0);
                //cout << "Problem is Solving..." << endl;
                break;
            default:
                break;
        } 
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
    
    lastDirection=direction; //update last direction
    return distance[direction]; //return minumum value
}
int createSubPuzzleAndCheckThem(int puzzle[][9],int row,int column,int arr[4],int lastDirection,int size){
    //this function checks all direction of empty tile can go, to find the best direction
    //in order to do that in here I calculated for all tile the distance from place that tile is there now to tile's place on solution, this is called as manhattan
    //also I calculated number of tiles which is not on own place, this is called as hamming
    //lastly I calculated for just one tile which will change it's position with empty tile the distance from place that tile is there now to tile's place on solution
    // at he end I sum these three result((manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)) 
    // and I found minumum result among  all direction of empty tile can go, and I returned minimum value 
    int i,min=10000,coord[2];
    for (i = 0; i < 4; i++) arr[i]=-1;
    bool left,right,up,down;
    int temp_Puzzle[9][9];
    returnBack(temp_Puzzle,puzzle,row,column); //fill the temp_puzzle with orijinal puzzle
    left=moveLeft(temp_Puzzle,row,column,1); // make a temporary move to the left
    if (left) //if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,row,column,coord);// find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[0]=sumManhattanOfAllTiles(temp_Puzzle,puzzle,row,column,size) + calculateManhattanOfOneTile(puzzle,temp_Puzzle[coord[0]][coord[1]+1],coord[0],coord[1]+1,row,column);
    }
    returnBack(temp_Puzzle,puzzle,row,column); //delete temporary left move and return back begining position of puzzle
    right=moveRight(temp_Puzzle,row,column,1); // make a temporary move to the right
    if (right) // if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,row,column,coord); // find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[1]=sumManhattanOfAllTiles(temp_Puzzle,puzzle,row,column,size)+ calculateManhattanOfOneTile(puzzle,temp_Puzzle[coord[0]][coord[1]-1],coord[0],coord[1]-1,row,column);   
    }
    returnBack(temp_Puzzle,puzzle,row,column);//delete temporary right move and return back begining position of puzzle
    up=moveUp(temp_Puzzle,row,column,1); // make a temporary move to the up
    if (up) //if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,row,column,coord); //find find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[2]=sumManhattanOfAllTiles(temp_Puzzle,puzzle,row,column,size)+ calculateManhattanOfOneTile(puzzle,temp_Puzzle[coord[0]+1][coord[1]],coord[0]+1,coord[1],row,column);
    }
    returnBack(temp_Puzzle,puzzle,row,column); //delete temporary up move and return back begining position of puzzle
    down=moveDown(temp_Puzzle,row,column,1); // make a temporary move to the down
    if (down) //if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,row,column,coord); // find find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[3]=sumManhattanOfAllTiles(temp_Puzzle,puzzle,row,column,size)+ calculateManhattanOfOneTile(puzzle,temp_Puzzle[coord[0]-1][coord[1]],coord[0]-1,coord[1],row,column);
    }
    returnBack(temp_Puzzle,puzzle,row,column); //delete temporary down move and return back begining position of puzzle
    /*set the last direction to not make same move*/
    switch (lastDirection)
    {
    case 0:
        lastDirection=1;
        break;
    case 1:
        lastDirection=0;
        break;
    case 2:
        lastDirection=3;
        break;
    case 3:
        lastDirection=2;
        break;        
    default:
        break;
    }
    // find minumum distance among all direction of empty tile can go
    for (i = 0; i < 4; i++){
    
        if(arr[i] != -1) // if we can move that direction
        {
            if (i!=lastDirection) //if our direction different than last direction
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
void returnBack(int tempPuzzle[][9],int puzzle[][9],int row,int column){
    //make the temp_puzzle unchanged (restore the temp puzzle)
    int i,j;
    for ( i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            tempPuzzle[i][j]=puzzle[i][j];
        }
    }
    
}
int sumManhattanOfAllTiles(int tempPuzzle[][9],int puzzle[][9],int row,int column,int size){
    //this function to calculate Manhattan + Hamming
   int i,j,sum_of_distance=0,tile,count=0,result=0,tileNo_OwnPlace;
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < column; j++)
        {
            if (tempPuzzle[i][j]!=0 && tempPuzzle[i][j]!=-1 ) //if tile different than impossible position and empty
            {
                tile=tempPuzzle[i][j]; //choose it
                result=calculateManhattanOfOneTile(puzzle,tile,i,j,row,column); //calculate it's manhattan distance
                if (result==0) // if it is own place
                    count++; //increment the count to calculate hamming
                sum_of_distance+=result; //sum all manhattan distance
            }
            
        }
        
    }
    tileNo_OwnPlace=(size-1)-count; // find number of tile that is not own place
    return sum_of_distance + tileNo_OwnPlace; //calculate and return Manhattan + Hamming
}
int calculateManhattanOfOneTile(int puzzle[][9],int tile,int x_position,int y_position,int row,int column){
    //this function to calculate manhattan distance of only one tile
    //in order calculate for one tile's manhattan I subtracted coordinates of tile on the unsolved puzzle from
    // coordinates of tile on the solved puzzle.
    int tempPuzzle[9][9],i,j,short_distance;
    getSolution(tempPuzzle,puzzle,row,column);//fill puzzle with solution(to make subtract)
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j< column; j++)
        {
            if (tile==tempPuzzle[i][j]) //find tile on the final soluion board
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
void getSolution(int tempPuzzle[][9],int puzzle[][9],int row,int column){
    //fill the puzzle with final solution(solved puzzle)
    int i,j,currentvalue=1;
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < column; j++)
        {
            
            if (i==row-1 && j==column-1)
                tempPuzzle[i][j]=-1;
            else{

                if (puzzle[i][j]!=0)
                {
                    tempPuzzle[i][j]=currentvalue;
                    currentvalue++;
                }
                else
                {
                    tempPuzzle[i][j]=0;  
                }
            }
        }
        
    }
    
}
int absoluteValue(int value){
    //get the absolute value of the given number
    if (value<0)
        return value*(-1);
    else
        return value;
    
}
bool is_end(int puzzle[][9],int row,int column){
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
                            return true;
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
bool shufflePuzzle(int puzzle[][9],int row,int column,int size,int task){
    // this is function to shuffle puzzle by making size*size random moves
    //also it doesn't make same move during this process
    srand(time(NULL));
    int tempPuzzle[9][9];
    int i,number,range,array[4],lastdirection=5;
    bool flag=false;
    if (task==1)//this is make shufle
    {
        range=size; // make row*column times random moves
        getSolution(tempPuzzle,puzzle,row,column);//get tempPuzzle to the final solution
    }
    else //this is make task times random moves
    {
        range=task; // make task times random moves
        returnBack(tempPuzzle,puzzle,row,column); // get tempPuzzle to the orijinal puzzle(copy the puzzle)
    }
    
    for ( i = 0; i < range; i++)
    {
        createSubPuzzleAndCheckThem(tempPuzzle,row,column,array,lastdirection,size);//bring possibilty move direction
        do
        {
            number=rand()%4; //chose a direction
        } while (array[number]==-1); // if direction has not room to go choose again
        lastdirection=number;
        switch (number)
        {
        case 0://left
            moveLeft(tempPuzzle,row,column,1);
            break;
        case 1: //right
            moveRight(tempPuzzle,row,column,1);
            break;
        case 2: //up
            moveUp(tempPuzzle,row,column,1);
            break;
        case 3: // down
            moveDown(tempPuzzle,row,column,1);
            break;        
        default:
            break;
        }
        
        if (task!=1)
            printPuzzleRealtime(tempPuzzle,row,column);
        flag=is_end(tempPuzzle,row,column);
        if (flag)
            return flag;
    }
    returnBack(puzzle,tempPuzzle,row,column);
    return flag;
}
void saveToFile(int puzzle[][9],int row,int column,string filename){
    //fill file with a loadable shape file
    ofstream outStream;
    int i,j,zero=0;
    string empty="bb";
    string blank=" ";
    outStream.open(filename); //open file
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
void Quit(){
    //finish the program
    exit(1);
}
