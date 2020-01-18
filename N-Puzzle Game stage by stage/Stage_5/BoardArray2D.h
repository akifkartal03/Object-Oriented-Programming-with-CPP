#ifndef BOARD_ARRAY_2D
#define BOARD_ARRAY_2D
#include "AbstractBoard.h"
namespace eagle{
    class BoardArray2D:public AbstractBoard{
    public:
        BoardArray2D();
        BoardArray2D(int r,int c);
         /*Big three*/
        BoardArray2D(const BoardArray2D& object);
        BoardArray2D& operator=(const BoardArray2D& rightSide);
        ~BoardArray2D();
        /*---these are from base class---*/
        void setSize(int r,int c,int s) override;//overriden
        const int& operator()(int index1,int index2) const override;//overriden
        //my operator's overriden
        int& operator()(int index1,int index2);//overriden
    private:
        int **puzzle; // a two dimensional dynamic C array
    };
}
#endif