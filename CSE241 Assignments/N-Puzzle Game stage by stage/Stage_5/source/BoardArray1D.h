#ifndef BOARD_ARRAY_1D
#define BOARD_ARRAY_1D
#include "AbstractBoard.h"
namespace eagle{
    class BoardArray1D:public AbstractBoard{
    public:
        BoardArray1D();
        BoardArray1D(int r,int c);
        /*Big three*/
        BoardArray1D(const BoardArray1D& object);
        BoardArray1D& operator=(const BoardArray1D& rightSide);
        ~BoardArray1D();
        /*---these are from base class---*/
        void setSize(int r,int c,int s) override;//overriden
        const int& operator()(int index1,int index2) const override;//overriden
        //my operator's overriden
        int& operator()(int index1,int index2) override; //overriden
    private:
        int *puzzle; //one dimensional dynamic C array.
    };
}
#endif