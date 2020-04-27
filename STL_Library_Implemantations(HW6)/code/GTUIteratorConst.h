#ifndef GTU_ITERATOR_CONST
#define GTU_ITERATOR_CONST
#include<iostream>
#include<memory>
#include<string>
#include "MyException.h"
using namespace std;
namespace eagle{
    template<class T>
    class GTUIteratorConst{
    public:
       protected:
       shared_ptr<T> ptr_c;
    public:
        GTUIteratorConst();
        GTUIteratorConst(shared_ptr<T> p);
        GTUIteratorConst(const GTUIteratorConst<T>& object);
        GTUIteratorConst<T>& operator++();
        GTUIteratorConst<T> operator++(int);
        bool operator==(const GTUIteratorConst<T>& rightSide) const;
        bool operator!=(const GTUIteratorConst<T>& rightSide) const;
        const T& operator*() const;  //const dereference operator
        const T* operator->() const; //const arrow operator
        GTUIteratorConst<T>& operator--();
        GTUIteratorConst<T> operator--(int);
        const T& operator[](int index) const; //const arrow operator
        GTUIteratorConst<T>& operator=(const GTUIteratorConst<T>& other);
        void setP( shared_ptr<T>& rs){ptr_c=rs;} // this will be used in derived class const_baseIterator  
    };

}
#endif