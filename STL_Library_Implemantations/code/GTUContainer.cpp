#include "GTUContainer.h"
namespace eagle{
    //implemention constructor of iterators and other fuctions
    template<class T>
    GTUContainer<T>::baseIterator::baseIterator():GTUIterator<T>(){
    }
    template<class T>
    GTUContainer<T>::baseIterator::baseIterator(shared_ptr<T> p):GTUIterator<T>(p){
    }
    template<class T>
    GTUContainer<T>::baseIterator::baseIterator(const baseIterator& object):GTUIterator<T>(object){
    }
    template<class T>
    GTUContainer<T>::const_baseIterator::const_baseIterator():GTUIteratorConst<T>(){
    }
    template<class T>
    GTUContainer<T>::const_baseIterator::const_baseIterator(shared_ptr<T> p):GTUIteratorConst<T>(p){
    }
    template<class T>
    GTUContainer<T>::const_baseIterator::const_baseIterator(const const_baseIterator& object):GTUIteratorConst<T>(object){
    }
    template<class T>
    typename GTUContainer<T>::const_baseIterator& GTUContainer<T>::const_baseIterator::operator=(const baseIterator& a){
        //since begin and end return a iterator, to use begin and end with const_iterator we have to implement assigment operator
        typename GTUContainer<T>::baseIterator iter(a);
        this->setP(iter.getP());
    }
    

}