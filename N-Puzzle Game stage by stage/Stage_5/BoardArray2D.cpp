#include "BoardArray2D.h"
using std::string;
namespace eagle{
    BoardArray2D::BoardArray2D():AbstractBoard(false,0,'S',3,3,9){
        /*create a 9x9 dynamic array*/
        setSize(row,column,size);
    }
    BoardArray2D::BoardArray2D(int r,int c):AbstractBoard(false,0,'S',r,c,r*c)
    {
        /*create a 9x9 dynamic array*/
        setSize(row,column,size);
    }
    BoardArray2D::BoardArray2D(const BoardArray2D& object):AbstractBoard(object.is_end,object.number_Of_Moves,object.last_Move,object.column,object.row,object.size){
        //allocate memory
        puzzle = new int *[row];
        for (int i = 0; i < column; i++)
        {
            puzzle[i] = new int[size];
        }
        //make deep copy
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                puzzle[i][j]=object.puzzle[i][j];
            }
        }
    }
    BoardArray2D& BoardArray2D::operator=(const BoardArray2D& rightSide){
        //check size
        if (size!=rightSide.size)
        {
            for (int i = 0; i < row; ++i)
            {
               delete puzzle[i];
            }
            delete [] puzzle;
            row=rightSide.row;
            column=rightSide.column;
            puzzle = new int *[row];
            for (int i = 0; i < row ; i++)
            {
                puzzle[i] = new int[column];
            }
        }
        //make deep copy
        size=rightSide.size;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                puzzle[i][j]=rightSide.puzzle[i][j];
            }
        }
        number_Of_Moves=rightSide.number_Of_Moves;
        last_Move=rightSide.last_Move;
        row=rightSide.row;
        column=rightSide.column;
        return *this;
    }
    BoardArray2D::~BoardArray2D(){
        //destructor
        for (int i = 0; i < row; ++i)
        {
            delete puzzle[i];
        }
        delete [] puzzle;
    }
    void BoardArray2D::setSize(int r,int c,int s){
        if (r!=row || c!=column || s!=size)
        {
            for (int i = 0; i < row; ++i)
            {
                delete puzzle[i];
            }
            delete [] puzzle;
        }
        row=r;column=c;size=s;
        //allocate memory
        puzzle = new int *[row];
        for (int i = 0; i < row ; i++)
        {
            puzzle[i] = new int[column];
        }
        //fill puzzle with -1
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                puzzle[i][j]=-1;
            }   
        }
        this->reset();//reset it
         
    }
    const int& BoardArray2D::operator()(int index1,int index2) const{
        //this operator is to access and return the value
        if (size<=0)
        {
            cout << "Puzzle is empty\n";
            exit(1);
        }
        else if (index1 < 0 || index1 >= row || index2 < 0 || index2 >= column)
        {
            cout << "Index Values are invalid.\n";
            exit(1);
        }
        else
        {
            //just return cell context as a const reference
            return puzzle[index1][index2];
        }
        
    }
    int& BoardArray2D::operator()(int index1,int index2){
        //this operator is to access and change the value(it is not return const so it can change cell context)
        if (size<=0)
        {
            cout << "Puzzle is empty\n";
            exit(1);
        }
        else if (index1 < 0 || index1 >= row || index2 < 0 || index2 >= column)
        {
            cout << "Index Values are invalid.\n";
            exit(1);
        }
        else
        {
            //just return cell context as a reference
            return puzzle[index1][index2];
        }
        
    }
}