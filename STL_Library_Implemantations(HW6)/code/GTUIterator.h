#ifndef GTU_ITERATOR
#define GTU_ITERATOR
#include<iostream>
#include<memory>
#include<string>
#include "MyException.h"
using namespace std;
namespace eagle{
    template<class T>
    class GTUIterator{
    protected:
       shared_ptr<T> ptr;
    public:
        GTUIterator();
        GTUIterator(shared_ptr<T> p);
        GTUIterator(const GTUIterator<T>& object);
        GTUIterator<T>& operator++();
        GTUIterator<T> operator++(int);
        bool operator==(const GTUIterator<T>& rightSide) const;
        bool operator!=(const GTUIterator<T>& rightSide) const;
        T& operator*() const;
        T* operator->() const;
        GTUIterator<T>& operator--();
        GTUIterator<T> operator--(int);
        T& operator[](int index) ;
        const T& operator[](int index) const;
        GTUIterator<T>& operator=(const GTUIterator<T>& other);
        shared_ptr<T>& getP(){return ptr;} //for derived class baseIterator
    };

}
#endif