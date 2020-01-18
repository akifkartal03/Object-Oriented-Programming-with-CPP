#include "GTUIteratorConst.h"
namespace eagle{
    template<class T>
    GTUIteratorConst<T>::GTUIteratorConst(){
        ptr_c = shared_ptr<T>(new T[1],[](T * d){
            delete [] d;
        });   
        
    }
    template<class T>
    GTUIteratorConst<T>::GTUIteratorConst(shared_ptr<T> p){
        ptr_c=p;
    }
    template<class T>
    GTUIteratorConst<T>::GTUIteratorConst(const GTUIteratorConst<T>& object){
        ptr_c=object.ptr_c;
    }
    template<class T>
    GTUIteratorConst<T>& GTUIteratorConst<T>::operator++(){
        T* cp=ptr_c.get();
        cp++;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr_c=tmp;
        return *this;
    }
    template<class T>
    GTUIteratorConst<T> GTUIteratorConst<T>::operator++(int) {
        GTUIteratorConst<T> temp(*this);
        T* cp=ptr_c.get();
        cp++;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr_c=tmp;
        return temp;
    }
    template<class T>
    bool GTUIteratorConst<T>::operator==(const GTUIteratorConst<T>& rightSide) const {
        return ptr_c.get()==rightSide.ptr_c.get();
    }
    template<class T>
    bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst<T>& rightSide) const {
        return ptr_c.get()!=rightSide.ptr_c.get();
    }
    //const dereference operator
    template<class T>
    const T& GTUIteratorConst<T>::operator*() const{
        return *ptr_c.get();
    }
    //const arrow operator
    template<class T>
    const T* GTUIteratorConst<T>::operator->() const{
        return ptr_c.get();
    }
    template<class T>
    GTUIteratorConst<T>& GTUIteratorConst<T>::operator--() {
        T* cp=ptr_c.get();
        cp--;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr_c=tmp;
        return *this;
    }
    template<class T>
    GTUIteratorConst<T> GTUIteratorConst<T>::operator--(int) {
        GTUIteratorConst<T> temp(*this);
        T* cp=ptr_c.get();
        cp--;
        shared_ptr<T> tmp(cp,[](T *d){});
	    ptr_c=tmp;
        return temp;
    }
    //const index operator
    template<class T>
    const T& GTUIteratorConst<T>::operator[](int index) const  {
        if (index < 0)
        {
            throw MyException("Your index value is not valid");
            
        }
        return ptr_c.get()[index];
    }
    template<class T>
    GTUIteratorConst<T>& GTUIteratorConst<T>::operator=(const GTUIteratorConst<T>& other) { 
        ptr_c = other.ptr_c; 
        return *this; 
    }
}