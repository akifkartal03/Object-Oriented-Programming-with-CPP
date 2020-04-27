#ifndef MY_EXCEPTION
#define MY_EXCEPTION
#include<iostream>
#include<string>
using namespace std;
/*This is my exception class for my exceptions*/
namespace eagle{
    class MyException{
    public:
        MyException();
        MyException(string text);
        string getExceptionDetails() const;
    private:
        string message;
    };

}
#endif