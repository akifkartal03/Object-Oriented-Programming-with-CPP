#include "BoardVector.h"
namespace eagle{
    BoardVector::BoardVector():AbstractBoard(false,0,'S',3,3,9){
        //resize vector
        setSize(row,column,size);
    }
    BoardVector::BoardVector(int r,int c):AbstractBoard(false,0,'S',r,c,r*c)
    {
        //resize vector
        setSize(row,column,size);
    }
    BoardVector::BoardVector(const BoardVector& object):AbstractBoard(object.is_end,object.number_Of_Moves,object.last_Move,object.column,object.row,object.size){
        //allocate memory
        puzzle.resize(row);
        for (int i = 0; i < puzzle.size(); i++)
        {
            puzzle[i].resize(column);
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
    void BoardVector::setSize(int r,int c,int s){
        if (r!=row || c!=column || s!=size)
        {
            for (int i = 0; i < puzzle.size(); i++)
            {
                puzzle[i].clear();
            }
            puzzle.clear();
        }
        row=r;column=c;size=s;
        //allocate memory
        puzzle.resize(row);
        for (int i = 0; i < puzzle.size(); i++)
        {
            puzzle[i].resize(column);
        }
        //fill the puzzle with -1
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                puzzle[i][j]=-1;
            }   
        }
        this->reset();//reset it
    }
    const int& BoardVector::operator()(int index1,int index2) const{
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
    int& BoardVector::operator()(int index1,int index2){
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

    