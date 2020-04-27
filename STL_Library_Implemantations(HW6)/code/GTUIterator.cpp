#include "GTUIterator.h"
namespace eagle {
    template<class T>
    GTUIterator<T>::GTUIterator(){
        //allocate memory for shared pointer
        ptr = shared_ptr<T>(new T[1],[](T * d){
            delete [] d;
        });   
        
    }
    template<class T>
    GTUIterator<T>::GTUIterator(shared_ptr<T> p){
        ptr=p;
    }
    template<class T>
    GTUIterator<T>::GTUIterator(const GTUIterator<T>& object){
        ptr=object.ptr;
    }
    template<class T>
    GTUIterator<T>& GTUIterator<T>::operator++(){
        //Prefix version
        //use regular pointer arithmetic to increment shared pointer by using it's constructor
        T* cp=ptr.get();
        cp++;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr=tmp;
        return *this;
    }
    template<class T>
    GTUIterator<T> GTUIterator<T>::operator++(int) {
        //Postfix version
        //use regular pointer arithmetic to increment shared pointer by using it's constructor
        GTUIterator<T> temp(*this);
        T* cp=ptr.get();
        cp++;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr=tmp;
        return temp;
    }
    template<class T>
    bool GTUIterator<T>::operator==(const GTUIterator<T>& rightSide) const {
        return ptr.get()==rightSide.ptr.get();
    }
    template<class T>
    bool GTUIterator<T>::operator!=(const GTUIterator<T>& rightSide) const {
        return ptr.get()!=rightSide.ptr.get();
    }
    template<class T>
    T& GTUIterator<T>::operator*() const{
        return *ptr.get();
    }
    template<class T>
    T* GTUIterator<T>::operator->() const{
        return ptr.get();
    }
    template<class T>
    GTUIterator<T>& GTUIterator<T>::operator--() {
        //Prefix version
        //use regular pointer arithmetic to increment shared pointer by using it's constructor
        T* cp=ptr.get();
        cp--;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr=tmp;
        return *this;
    }
    template<class T>
    GTUIterator<T> GTUIterator<T>::operator--(int) {
        //Postfix version
        GTUIterator<T> temp(*this);
        T* cp=ptr.get();
        cp--;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr=tmp;
        return temp;
    }
    template<class T>
    T& GTUIterator<T>::operator[](int index)  {
        if (index < 0)
        {
            throw MyException("Your index value is not valid");
            
        }
        return ptr.get()[index];
    }
    template<class T>
    const T& GTUIterator<T>::operator[](int index) const  {
        if (index < 0)
        {
            throw MyException("Your index value is not valid");
            
        }
        return ptr.get()[index];
    }
    template<class T>
    GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator<T>& other) { 
        ptr = other.ptr; 
        return *this; 
    }
    
}