#include "MyException.h"
namespace eagle{    
    MyException::MyException():MyException("There is no information!"){}
    MyException::MyException(string text):message(text){}
    string MyException::getExceptionDetails() const{
        return message;
    }

}