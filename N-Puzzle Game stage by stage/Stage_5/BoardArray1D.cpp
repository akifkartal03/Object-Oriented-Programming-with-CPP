#include "BoardArray1D.h"
namespace eagle{
    BoardArray1D::BoardArray1D():AbstractBoard(false,0,'S',3,3,9){
        //create a dynamic array with size 9
        setSize(row,column,size);
    }
    BoardArray1D::BoardArray1D(int r,int c):AbstractBoard(false,0,'S',r,c,r*c){
        //create a dynamic array with size r*c
        setSize(row,column,size);
    }
    BoardArray1D::BoardArray1D(const BoardArray1D& object):AbstractBoard(object.is_end,object.number_Of_Moves,object.last_Move,object.column,object.row,object.size){
        puzzle=new int[row*column];
        for (int i = 0; i < row*column; ++i)
        {
            puzzle[i]=object.puzzle[i];
        }
    }
    BoardArray1D& BoardArray1D::operator=(const BoardArray1D& rightSide){
        //check size
        if (size!=rightSide.size)
        {
            delete[] puzzle;
            puzzle=new int[rightSide.size];
        }
        //make deep copy
        size=rightSide.size;
        for (int i = 0; i < size; ++i)
        {
            puzzle[i]=rightSide.puzzle[i];
        }
        number_Of_Moves=rightSide.number_Of_Moves;
        last_Move=rightSide.last_Move;
        row=rightSide.row;
        column=rightSide.column;
        return *this;
    }
    BoardArray1D::~BoardArray1D(){
        delete[] puzzle;
    }
    void BoardArray1D::setSize(int r,int c,int s){
        if (r!=row || c!=column || s!=size)
        {
            delete [] puzzle;
        }
        row=r;column=c;size=s;
        puzzle=new int[row*column]; //allocate memory
        for (int j = 0; j < row*column; j++)
        {
            puzzle[j]=-1;//fill all puzzle with -1
        }  
        this->reset();// and reset
    }
    const int& BoardArray1D::operator()(int index1,int index2) const{
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
            //since this is 1D dynamic array return context of cell that corresponding to 2D array 
            //that's why we did column*index1+index2
            return puzzle[column*index1+index2];
        }
        
    }
    int& BoardArray1D::operator()(int index1,int index2){
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
            //since this is 1D dynamic array return context of cell that corresponding to 2D array 
            //that's why we did column*index1+index2
            return puzzle[column*index1+index2];
        }
    }
   
}