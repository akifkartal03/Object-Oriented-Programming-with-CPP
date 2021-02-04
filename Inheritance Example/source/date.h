#ifndef date
#define date
#include<iostream>
using namespace std;
namespace v{
    class Date{
    public:
        Date( );
        Date(int dayValue,int monthValue,int yearValue);
        void input(int dayValue,int monthValue,int yearValue);
        void output() const;
    private:
        int year;
        int month;
        int day;
        void testDate( );
    };

}
#endif