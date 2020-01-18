
/* Here, in many of implementation two virtual operator used very often.*/
/* These two operator provides us either access or change the cell context.*/            
/* So that we are able to implement many of the function here just one time .*/
/* Also operators(()) works according to type of class by using "this" keyword.*/ 
#include "AbstractBoard.h"
#include<fstream>
namespace eagle{
    AbstractBoard::AbstractBoard():AbstractBoard(false,0,'S',0,0,0){
        number_Of_Board++;
    }
    AbstractBoard::AbstractBoard(bool end ,int number_move,char lMove,int r,int c,int s):is_end(end),
            number_Of_Moves(number_move),last_Move(lMove),row(r),column(c),size(s){
            number_Of_Board++;
    }
    void AbstractBoard::print() const{
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
                if (this->operator()(i,j)==-1)
                    //if number is -1 then print space
                    cout << "  ";
                else if (this->operator()(i,j)==0)
                    cout << "00";
                else if (this->operator()(i,j)<10 && this->operator()(i,j)!=0 )
                    cout << "0" << this->operator()(i,j);
                else
                    cout << this->operator()(i,j);
            }
            cout << "|" << endl;
        }
        //at the end print ------
        for ( k = 0; k < column*3+1; k++) cout << "-";
        cout << endl << endl;

    }
    int AbstractBoard::convertStrToInt(string str,int sizeOfStr){
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
    bool AbstractBoard::readFromFile(std::string fileName){
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
                if (str.length()!=0) 
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
                if (str.length()!=0)
                {
                    rowNumber++;
                }
                
            }
            
            getNumbers.close();//close
            //find column number by using all tile and row number
            columnNumber=sum/rowNumber;
            //set size
            this->setSize(rowNumber,columnNumber,sum-numberOfZero);
            getNumbers.open(fileName);//open again
            /*get one tile from file as a string then convert it to integer
            then push it puzzle*/
            for ( i = 0; i < rowNumber; i++)
            {
                for (j = 0; j < columnNumber; j++)
                {
                    getNumbers >> str; //get a tile
                    tile=convertStrToInt(str,str.length());//convert it to int
                    this->operator()(i,j)=tile;//push it array
                }
                    
            }  
        }
        getNumbers.close();//close
        return true;
    }
    void AbstractBoard::writeToFile(std::string fileName){
        //fill file with a loadable shape file
        ofstream outStream;
        int i,j,zero=0;
        string empty="bb";
        string blank=" ";
        outStream.open(fileName); //open file
        /*check the file */
        if (!outStream.is_open())
            cout << "File is not opened";
        else
        {
            for ( i = 0; i < row; i++)
            {
                for ( j = 0; j < column; j++)
                {
                    if (this->operator()(i,j)==0)
                        outStream << zero << zero << blank ;
                    else if (this->operator()(i,j)==-1)
                        outStream << empty << blank ;
                    else
                    {
                        if (this->operator()(i,j)<10)
                        {
                            outStream << zero << this->operator()(i,j) << blank ;
                        }
                        else
                        {
                            outStream << this->operator()(i,j) << blank ;
                        }   
                    }
                }
                if (i!=row-1)
                    outStream << endl;
            } 
        }
    }
    void AbstractBoard::reset(){
        //reset puzzle with solution
        int i,j,currentvalue=1;
        for ( i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if (i==row-1 && j==column-1)
                    this->operator()(i,j)=-1;
                else{
                    if (this->operator()(i,j)!=0)
                    {
                        this->operator()(i,j)=currentvalue;
                        currentvalue++;
                    }
                    else
                    {
                        this->operator()(i,j)=0;
                    }
                }
            }
        }
        /*Update some important values*/
        number_Of_Moves=0;
        last_Move ='S';
    }
    bool AbstractBoard::move(char move_direction){
        int i,j;
        for (i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if (this->operator()(i,j)==-1) //find zero in order to moves the empty cell
                {
                    if (move_direction=='L')//left
                    {
                        if (j==0) // if there is no room left side of empty cell
                            return false;
                        else //if there is room
                        {
                            if (this->operator()(i,j-1)==0)//if it is impossible position return false
                                return false;
                            else
                            {
                                //swap the 0 and left tile and update values
                                swapTiles(i,j,i,j-1);
                                this->last_Move='L';
                                this->number_Of_Moves++;
                                return true;
                            }
                        }
                    }
                    else if (move_direction=='R')//right
                    {
                        if (j==(column-1)) // if there is no room right side of empty cell
                            return false;
                        else //if there is room
                        {
                            if (this->operator()(i,j+1)==0)//if it is impossible position return false
                                return false;
                            else
                            {
                                //swap the 0 and right tile and update values
                                swapTiles(i,j,i,j+1);
                                this->last_Move='R';
                                this->number_Of_Moves++;
                                return true;
                            }
                        }
                    }
                    else if (move_direction=='U')//up
                    {
                        if (i==0) // if there is no room up side of empty cell
                            return false;
                        else //if there is room
                        {
                            if (this->operator()(i-1,j)==0)//if it is impossible position return false
                                return false;
                            else
                            {
                                //swap the 0 and up tile and update values
                                swapTiles(i,j,i-1,j);
                                this->last_Move='U';
                                this->number_Of_Moves++;
                                return true;
                            }
                        }
                    }
                    else if (move_direction=='D')//down
                    {
                        if (i==(row-1)) // if there is no room down side of empty cell
                            return false;
                        else //if there is room
                        {
                            if (this->operator()(i+1,j)==0)//if it is impossible position return false
                                return false;
                            else
                            {
                                //swap the 0 and down tile and update values
                                swapTiles(i,j,i+1,j);
                                this->last_Move='D';
                                this->number_Of_Moves++;
                                return true;
                            }
                        }
                        
                    }
                    else
                    {
                        cout << "Invalid Direction!\n";
                        return false;
                    }
                   
                }
                
            }
        }

    }
    void AbstractBoard::swapTiles(int index1,int index2,int index3,int index4){
        //swap two tiles in the puzzle
        int temp;
        temp=this->operator()(index1,index2);
        this->operator()(index1,index2)=this->operator()(index3,index4);
        this->operator()(index3,index4)=temp;
    }
    void AbstractBoard::setLastMove(char direction){
        last_Move=direction;
    }
    void AbstractBoard::setNumberOfMoves(){
        //decrement number of moves by two(this will use in global function)
        number_Of_Moves-=2;
    }
    bool AbstractBoard::is_solved(){
        //this function to check Is the game over ?
        int i,j,currentvalue=1;
        for ( i = 0; i < row; i++)
        {
            for ( j = 0; j < column; j++)
            {
                if (this->operator()(i,j)!=0)
                {
                    if (this->operator()(i,j)!=currentvalue)
                    {
                        if (i==row-1 && j==column-1)
                        {
                            if (this->operator()(i,j)==-1) // check for empty cell
                            {
                                this->is_end=true;
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
    bool AbstractBoard::operator==(const AbstractBoard& rightSide){
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (this->operator()(i,j)!=rightSide.operator()(i,j))
                {
                    return false;
                }
            }
            
        }
        return true;
    }
    int AbstractBoard::NumberOfBoards(){
        return number_Of_Board;
    }
    char AbstractBoard::lastMove() const{
        return this->last_Move;
    }
    int AbstractBoard::numberofMoves() const{
        return this->number_Of_Moves;
    }
    int AbstractBoard::getRow() const{
        return this->row;
    }
    int AbstractBoard::getColumn() const{
        return this->column;
    }
    int AbstractBoard::getSize() const{
        return this->size;
    }
    bool AbstractBoard::getEnd() const{
        return this->is_end;
    }
    void AbstractBoard::setEnd(bool result){
        this->is_end=result;
    }
    AbstractBoard::~AbstractBoard(){
        //we don't have pointer in base class
        //but we have implement it.
    }
    
}