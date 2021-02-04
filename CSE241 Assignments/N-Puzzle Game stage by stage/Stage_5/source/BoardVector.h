#ifndef BOARDVECTOR
#define BOARDVECTOR
#include "AbstractBoard.h"
#include<vector>
using std::vector;
namespace eagle{
    class BoardVector:public AbstractBoard{
    public:
        BoardVector();
        BoardVector(int r,int c);
        /* Vector has its own big three.But to increase number of board I will redefine copy constructor*/
        BoardVector(const BoardVector& object);
        /*---these are from base class---*/
        void setSize(int r,int c,int s) override;//overriden
        const int& operator()(int index1,int index2) const override;//overriden
        //my operator's override
        int& operator()(int index1,int index2) override;//overriden
        
    private:
        vector<vector<int>> puzzle; //STL vector of STL vectors
    };
}
#endif