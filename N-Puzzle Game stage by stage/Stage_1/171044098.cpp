#include<iostream>
#include<cstdlib>
#include <ctime>
using namespace std;
/*My function prototypes*/
//I explained their tasks in the their definition.
int takeSize();
bool checkSize(int input);
bool initializePuzzleRandomly(int puzzle[][9],int size);
bool checkRandomArr(int arr[],int size,int number);
int countInversionNumber(int puzzle[][9],int x_position,int y_position,int size,int tile);
void findCoordinatesOfEmpty(int puzzle[9][9],int size,int arr[2]);
void gameRealTime(int puzzle[][9],int size);
void printPuzzleRealtime(int puzzle[][9],int size);
char getDirectionOfMove();
bool moveLeft(int puzzle[][9],int size,int flag);
bool moveRight(int puzzle[][9],int size,int flag);
bool moveUp(int puzzle[][9],int size,int flag);
bool moveDown(int puzzle[][9],int size,int flag);
bool findMinimumCase(int puzzle[][9],int size,int &lastDirection);
int createSubPuzzleAndCheckThem(int puzzle[9][9],int size,int arr[4],int lastDirection);
void returnBack(int tempPuzzle[][9],int puzzle[][9],int size);
int calculateManhattanOfAllTiles(int puzzle[][9],int size);
int calculateManhattanOfOneTile(int tile,int x_position,int y_position,int size);
void getSolution(int puzzle[][9],int size);
int absoluteValue(int value);
bool is_end(int puzzle[][9],int size);
void shufflePuzzle(int puzzle[][9],int size);
void Quit();

int main(){
    const int MAX_SIZE=9; //initialize max size with 9
    int puzzle[MAX_SIZE][MAX_SIZE],size; // create puzzle
    size=takeSize(); // take size from user
    gameRealTime(puzzle,size);// start game
    return 0;
   
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
    int defaultsize[7]={3,4,5,6,7,8,9};
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
            puzzle[i][j]=number; // if different then save it on puzzle
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
            sumOfInversion+= countInversionNumber(puzzle,i,j,size,puzzle[i][j]);
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
        findCoordinatesOfEmpty(puzzle,size,coord);
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
int countInversionNumber(int puzzle[][9],int x_position,int y_position,int size,int tile){
    // this function counts inversion number to find unsolvable puzzles
    int i,j,number=0;
    for ( i = x_position; i < size; i++)
    {
        for ( j = y_position; j < size; j++)
        {
            if ((puzzle[i][j] < tile) && (puzzle[i][j]!=0))
                number++;
        }
        y_position=0;
    }
    return number;
}
void findCoordinatesOfEmpty(int puzzle[9][9],int size,int arr[2]){
    // this funtion to find coordinates of empty cell
    int i,j;
    for ( i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (puzzle[i][j]==0)
            {
                arr[0]=i;
                arr[1]=j;
            }
            
        }
        
    }
    
}
void gameRealTime(int puzzle[][9],int size){
    // this function to play the game real time
    int totalMoves=0,lastDirection=5;
    bool end=false,is_solvable,flag;
    char moveDirection;
    //check solvable puzzle if solvable then initialize puzzle with it
    do{
        is_solvable=initializePuzzleRandomly(puzzle,size);
    }while (!is_solvable);
    printPuzzleRealtime(puzzle,size); // print puzzle
    end=is_end(puzzle,size); //check for end
    while (!end) //while game is not over
    {
        moveDirection=getDirectionOfMove(); //get direction from user
        //check direction
        switch(moveDirection){
        case 'L': //left
            if (moveLeft(puzzle,size,0))
                totalMoves++;   
            break;
        case 'R': //right
            if (moveRight(puzzle,size,0))
                totalMoves++;   
            break;
        case 'U': //up
            if (moveUp(puzzle,size,0))
                totalMoves++;   
            break;
        case 'D': //down
            if (moveDown(puzzle,size,0))
                totalMoves++;   
            break;
        case 'I': //intelligent move
            flag=findMinimumCase(puzzle,size,lastDirection);
            while (!flag)
                flag=findMinimumCase(puzzle,size,lastDirection);
            totalMoves++;
            break;
        case 'S': //shuffle
            shufflePuzzle(puzzle,size);
            break;
        case 'Q': //quit
            Quit();
            break;
        default:
            cout << "Please Enter Correctly" << endl;
            break;
        }
        printPuzzleRealtime(puzzle,size);//print puzzle after move  
        end=is_end(puzzle,size); //check for end

    }
    //if game over
    //print results
    cout << endl  << "Problem Solved!" << endl; 
    cout << "Total number of moves " << totalMoves << endl;
}
void printPuzzleRealtime(int puzzle[][9],int size){
    //print puzzle 
    int i,j,k,l;
    for ( i = 0; i < size; i++)
    {
        //at the begining print --------
        if (size==3) // print different sembol of -
        {
            for ( k = 0; k < size*3-2; k++)
            {
                cout << "-";
            }
            
        }
        else
        {
            for ( k = 0; k < size*3+1; k++)
            {
                cout << "-";
            }
        }
        cout << endl;
        //now prints numbers
        for ( j = 0; j < size; j++)
        {
            cout << "|";
            if (puzzle[i][j]==0)
                //if number is zero then print space
                 cout << " "; 
            else
                //if number is diffrent than zero then print number
                cout << puzzle[i][j] ;
            if (size!=3)
                if (puzzle[i][j]<10)
                    //if number is one digit make one space
                    cout << " "; 
        }
        cout << "|";
        cout << endl; // new line
    }
    //at the end print ------
    if (size==3)
    {
        for ( k = 0; k < size*3-2; k++)
        {
            cout << "-";
        }
            
    }
    else
    {
        for ( k = 0; k < size*3+1; k++)
        {
            cout << "-";
        }
    }
    cout << endl;
    cout << endl;
}
char getDirectionOfMove(){
    //this function takes a letter from user to choice direction
    char moveDirection;
    cout << "Your Move: ";
    cin >> moveDirection;
    
    while (moveDirection!='L' && moveDirection!='R' && moveDirection!='U' && moveDirection!='D' && moveDirection!='I' && moveDirection!='S' && moveDirection!='Q'){

        cout << "Please enter a valid value: ";
        cin >> moveDirection;
    }
    
    return moveDirection; //return 
    
}
bool moveLeft(int puzzle[][9],int size,int flag){
    //this function for move left
    int i,j,temp;
    for (i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            if (puzzle[i][j]==0) //find zero in order to moves the empty cell
            {
                if (j==0) // if there is no room left side of empty cell
                {
                    if (flag==0)
                       cout << "***You cannot move this direction!***" << endl;
                    return false;
                }
                else //if there is room
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
bool moveRight(int puzzle[][9],int size,int flag){
    int i,j,temp;
    for (i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++) 
        {
            if (puzzle[i][j]==0) //find zero in order to moves the empty cell
            {
                if (j==(size-1)) // if there is no room right side of empty cell
                {
                    if (flag==0)
                       cout << "***You cannot move this direction!***" << endl;
                    return false;
                }
                else //if there is room
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
bool moveUp(int puzzle[][9],int size,int flag){
    int i,j,temp;
    for (i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            if (puzzle[i][j]==0) //find zero in order to moves the empty cell
            {
                if (i==0) // if there is no room up side of empty cell
                {
                    if (flag==0)
                       cout << "***You cannot move this direction!***" << endl;
                    return false;
                }
                else //if there is room
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
bool moveDown(int puzzle[][9],int size,int flag){
    int i,j,temp;
    for (i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            if (puzzle[i][j]==0) //find zero in order to moves the empty cell
            {
                if (i==(size-1)) // if there is no room down side of empty cell
                {
                    if (flag==0)
                       cout << "***You cannot move this direction!***" << endl;
                    return false;
                }
                else //if there is room
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
bool findMinimumCase(int puzzle[][9],int size,int &lastDirection){
    //this function to make an intelligent moves by using manhattan+haming distance which I calculated them in createSubPuzzle function
    //also in this function I used call by refence method for lastDirection since don't make the same move again
    srand(time(NULL));
    int result,i,direction,value,number;
    int distance[4]; //to keep each direction's manhattan+haming+tile's manhattan value.
    // distance[0]=left , distance[1]=right , distance[2]=up, distance[3]=down 
    int temp_Puzzle[9][9];//define a temp puzzle to check sub puzzles
    bool flag=false;
    value=lastDirection;
    returnBack(temp_Puzzle,puzzle,size);//fill the temp_puzzle with orijinal puzzle
    result=createSubPuzzleAndCheckThem(temp_Puzzle,size,distance,value); //get minumum manhattan+haming+tile's manhattan to choose best way
    for ( i = 0; i < 4; i++)
    {
        if (distance[i]==result)
        {
            if (i==0) //if the best way is left
            {
                if (lastDirection==1) // if last move is right 
                {
                    if (!flag) //if we didn't find best way
                    {
                        //don't move left to not make same move again
                        flag=false;
                    }
                    
                }
                else // if last move is not right
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
               if (lastDirection==0) // if last move is left
                {
                    if (!flag) //if we didn't find best way
                    {
                        //don't move right to not make same move again
                        flag=false;
                    }
                    
                }
                else // if last move is not left
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
               if (lastDirection==3) // if last move is down
                {
                    if (!flag) //if we didn't find best way
                    {
                        //don't move up to not make same move again
                        flag=false;
                    }
                }
                else // if last move is not down
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
               if (lastDirection==2) // if last move is up
                {
                    if (!flag) //if we didn't find best way
                    {
                        //don't move down to not make same move again
                        flag=false;
                    }
                }
                else // if last move is not up
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
                moveLeft(puzzle,size,0); 
                cout << "Intelligent move chooses L" << endl;
                break;
            case 1: // the best way is right
                moveRight(puzzle,size,0);
                cout << "Intelligent move chooses R" << endl;
                break;
            case 2: // the best way is up
                moveUp(puzzle,size,0);
                cout << "Intelligent move chooses U" << endl;
                break;
            case 3: // the best way is down
                moveDown(puzzle,size,0);
                cout << "Intelligent move chooses D" << endl;
                break;
            default:
                break;
        } 
    }
    lastDirection=direction; //update last direction
    return flag; //return result
    
}
int createSubPuzzleAndCheckThem(int puzzle[][9],int size,int arr[4],int lastDirection){
    //this function checks all direction of empty tile can go, to find the best direction
    //in order to do that in here I calculated for all tile the distance from place that tile is there now to tile's place on solution, this called as manhattan
    //also I calculated number of tiles which is not on own place, this called as hamming
    //lastly I calculated for just one tile which will change it's position with empty tile the distance from place that tile is there now to tile's place on solution
    // at he end I sum these three result((manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)) 
    // and I found minumum result among  all direction of empty tile can go, and I returned minimum value 
    int i,min=10000,coord[2];
    for (i = 0; i < 4; i++) arr[i]=-1;
    bool left,right,up,down;
    int temp_Puzzle[9][9];
    returnBack(temp_Puzzle,puzzle,size); //fill the temp_puzzle with orijinal puzzle
    left=moveLeft(temp_Puzzle,size,1); // make a temporary move to the left
    if (left) //if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,size,coord);// find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[0]=calculateManhattanOfAllTiles(temp_Puzzle,size) + calculateManhattanOfOneTile(temp_Puzzle[coord[0]][coord[1]+1],coord[0],coord[1]+1,size);
    }
    returnBack(temp_Puzzle,puzzle,size); //delete temporary left move and return back begining position of puzzle
    right=moveRight(temp_Puzzle,size,1); // make a temporary move to the right
    if (right) // if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,size,coord); // find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[1]=calculateManhattanOfAllTiles(temp_Puzzle,size)+ calculateManhattanOfOneTile(temp_Puzzle[coord[0]][coord[1]-1],coord[0],coord[1]-1,size);   
    }
    returnBack(temp_Puzzle,puzzle,size);//delete temporary right move and return back begining position of puzzle
    up=moveUp(temp_Puzzle,size,1); // make a temporary move to the up
    if (up) //if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,size,coord); //find find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[2]=calculateManhattanOfAllTiles(temp_Puzzle,size)+ calculateManhattanOfOneTile(temp_Puzzle[coord[0]+1][coord[1]],coord[0]+1,coord[1],size);
    }
    returnBack(temp_Puzzle,puzzle,size); //delete temporary up move and return back begining position of puzzle
    down=moveDown(temp_Puzzle,size,1); // make a temporary move to the down
    if (down) //if there is room
    {
        findCoordinatesOfEmpty(temp_Puzzle,size,coord); // find find coordinates of empty cell
        //calculate (manhattan+hamming) + (manhattan distance of the tile that replaces it's position with the empty cell)
        arr[3]=calculateManhattanOfAllTiles(temp_Puzzle,size)+ calculateManhattanOfOneTile(temp_Puzzle[coord[0]-1][coord[1]],coord[0]-1,coord[1],size);
    }
    returnBack(temp_Puzzle,puzzle,size); //delete temporary down move and return back begining position of puzzle
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
void returnBack(int tempPuzzle[][9],int puzzle[][9],int size){
    //make the temp_puzzle unchanged (restore the temp puzzle)
    int i,j;
    for ( i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            tempPuzzle[i][j]=puzzle[i][j];
        }
    }
    
}
int calculateManhattanOfAllTiles(int puzzle[][9],int size){
    //this function to calculate Manhattan + Hamming
   int i,j,sum_of_distance=0,tile,count=0,result=0,tileNo_OwnPlace;
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            if (puzzle[i][j]!=0) //if tile different than empty
            {
                tile=puzzle[i][j]; //choose it
                result=calculateManhattanOfOneTile(tile,i,j,size); //calculate it's manhattan distance
                if (result==0) // if it is own place
                    count++; //increment the count to calculate hamming
                sum_of_distance+=result; //sum all manhattan distance
            }
            
        }
        
    }
    tileNo_OwnPlace=(size*size-1)-count; // find number of tile that is not own place
    return sum_of_distance + tileNo_OwnPlace; //calculate and return Manhattan + Hamming
}
int calculateManhattanOfOneTile(int tile,int x_position,int y_position,int size){
    //this function to calculate manhattan distance of only one tile
    //in order calculate for one tile's manhattan I subtracted coordinates of tile on the unsolved puzzle from
    // coordinates of tile on the solved puzzle.
    int tempPuzzle[9][9],i,j,short_distance;
    getSolution(tempPuzzle,size);//fill puzzle with solution(to make subtract)
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j< size; j++)
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
void getSolution(int puzzle[][9],int size){
    //fill the puzzle with final solution(solved puzzle)
    int i,j,currentvalue=1;
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            
            if (i==size-1 && j==size-1)
                puzzle[i][j]=0;
            else
               puzzle[i][j]=currentvalue;     
            currentvalue++;
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
bool is_end(int puzzle[][9],int size){
    //this function to check Is the game over ?
    int i,j,currentvalue=1;
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            
            if (puzzle[i][j]!=currentvalue)
            {
                if (i==size-1 && j==size-1)
                {
                    if (puzzle[i][j]==0) // check for empty cell
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
    return true;

}
void shufflePuzzle(int puzzle[][9],int size){
    // this is function to shuffle puzzle by making size*size random moves
    //also it doesn't make same move during this process
    getSolution(puzzle,size);//get board to the final solution
    srand(time(NULL));
    int i,number,range,array[4],lastdirection=5;
    range=size*size; // make size*size random moves
    bool flag;
    for ( i = 0; i < range; i++)
    {
        createSubPuzzleAndCheckThem(puzzle,size,array,lastdirection);//bring possibilty move direction
        do
        {
            number=rand()%4; //chose a direction
        } while (array[number]==-1); // if direction has not room to go choose again
        lastdirection=number;
        switch (number)
        {
        case 0://left
            moveLeft(puzzle,size,1);
            break;
        case 1: //right
            moveRight(puzzle,size,1);
            break;
        case 2: //up
            moveUp(puzzle,size,1);
            break;
        case 3: // down
            moveDown(puzzle,size,1);
            break;        
        default:
            break;
        }
        
    }
    
}
void Quit(){
    //finish the program
    exit(1);
}

