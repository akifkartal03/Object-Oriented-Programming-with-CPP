
/* In this interface some functions are not virtual. */
/* Because they are same for three different derived class. */            
/* I just made 3 function vrtual that one of them is my new function. */
/* Since many of the function are common among three class  */
/* my new class prevent a huge code repetition. */                
#ifndef ABSTRACTBOARD
#define ABSTRACTBOARD
#include<iostream>
#include<string>
using namespace std;
namespace eagle{
    class AbstractBoard{
    public:
        AbstractBoard();
        AbstractBoard(bool end,int number_move,char lMove,int r,int c,int s);
        void print() const;
        bool readFromFile(string fileName);
        void writeToFile(string fileName);
        void reset();
        virtual void setSize(int r,int c,int s) = 0;//this will be different for three derived class
        bool move(char move_direction);
        bool is_solved();
        /*this function will be used in global function so, it should be pure virtual*/
        virtual const int& operator()(int index1,int index2) const = 0; 
        bool operator==(const AbstractBoard& rightSide);
        static int NumberOfBoards();
        char lastMove() const;
        int numberofMoves() const;
        /*----getters and setters----*/
        int getRow() const;
        int getColumn() const;
        int getSize() const;
        bool getEnd() const;
        void setEnd(bool result);
        void setNumberOfMoves();
        void setLastMove(char direction);
        //set size enough to set, so we don't need any other setter
        /*---my other operator---*/
        //this operator will be used in the base class's functions to acces and change values
        //this operator and other virtual operator will prevent code repetition.
        virtual int& operator()(int index1,int index2) = 0;
        virtual ~AbstractBoard();
    protected:
        bool is_end;
        static int number_Of_Board;
        int number_Of_Moves;
        char last_Move;
        int row,column,size;
    private:
        /*helper functions*/
        int convertStrToInt(string str,int sizeOfStr);
        void swapTiles(int index1,int index2,int index3,int index4);
    };
}
#endif
