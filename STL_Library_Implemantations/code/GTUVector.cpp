#include "GTUVector.h"
namespace eagle{
    template<class T>
    GTUVector<T>::GTUVector():GTUSet<T>(10){
        //use base class constructor
    }
    template<class T>
    GTUVector<T>::GTUVector(int cap):GTUSet<T>(cap){
        //use base class constructor
    }
    //redefine insert function by using "this" keyword
    template<class T>
    typename GTUContainer<T>::baseIterator GTUVector<T>::insert(const T& value) {
        //we can add same element in the set
        if (this->capacity > this->used+1) //check capacity
        {
            (this->p).get()[this->used]=value;
            this->used++;
        }
        else //if it is not enough
        {
            if (this->capacity>1500)
            {
                throw MyException("Your vector capacity is full, you cannot insert a new element to the vector.");
            }
            else
            {
                //adjust capacity
                if (1500-this->capacity > this->used*2)
                {
                    this->capacity=this->used*2;
                }
                else
                {
                    this->capacity+=1500-this->capacity;
                }
                shared_ptr<T> temp;
                temp=shared_ptr<T>(new T[this->capacity],[](T * d){
                    delete [] d;
                });
                for (int i = 0; i < this->used; i++)
                {
                    temp.get()[i]=(this->p).get()[i];
                }
                (this->p)=temp;
                (this->p).get()[this->used]=value;
                this->used++;
                temp=nullptr;
            }
        }
        cout << "Your value added. Successfuly." << endl;
        T* cp=&(this->p).get()[0];
        cp=cp+this->used-1;
        shared_ptr<T> tmp(cp,[](T *d){});
        typename GTUContainer<T>::baseIterator position(tmp);
        return position;
    }
    //new operator implementation
    template<class T>
    const T& GTUVector<T>::operator[](int index) const{
        if (index < 0 || index > this->used-1)
        {
            throw MyException("index value is not valid!");
        }
        else
        {
            return (this->p).get()[index];
        }
    }
    //2.overload of index operator
    template<class T>
    T& GTUVector<T>::operator[](int index) {
        if (index < 0 || index > this->used-1)
        {
            throw MyException("index value is not valid!");
        }
        else
        {
            return (this->p).get()[index];
        }
    }
    // 2. overload of insert() function(redefine it for vector)
    template<class T>
    typename GTUContainer<T>::baseIterator GTUVector<T>::insert(typename GTUContainer<T>::baseIterator position,const T& value){ 
        if (this->capacity > this->used+1)// check capacity
        {
            if (this->used==0) //if size is 0 add begin
            {
                *(this->begin()) = value;
                this->used++;
                return position;
            }
            else if (position==this->end()) //add end
            {
                *(this->end()) = value;
                this->used++;
                return position;
            }
            /*other case of position*/
            typename GTUContainer<T>::baseIterator p,q;
            for (p=this->begin(); p!=this->end(); p++)
            {
                if (p==position)
                {
                    for ( q=this->end(); q!=p;)
                    {
                        //swap values
                        --q;
                        T tm;
                        tm=*q;
                        q++;
                        *q=tm;
                        --q;
                    }
                    *p=value; //add element
                    break;
                }
                
            }
            if (p==this->end())
            {
                throw MyException("Your position is wrong.");
            }
            this->used++;
            cout << "Your value added. Successfuly." << endl;
            return position;
        }
        else // if capacity is not enough
        {
            if (this->capacity>1500)
            {
                throw MyException("Your vector capacity is full, you cannot insert a new element to the vector.");
            }
            else
            {
                //adjust capacity
                if (1500-this->capacity > this->used*2)
                {
                    this->capacity=this->used*2;
                }
                else
                {
                    this->capacity+=1500-this->capacity;
                }
                shared_ptr<T> temp;
                temp=shared_ptr<T>(new T[this->capacity],[](T * d){
                    delete [] d;
                });
                for (int i = 0; i < this->used; i++)
                {
                    temp.get()[i]=(this->p).get()[i];
                }
                (this->p)=temp;
                //do swap that is like above
                if (position==this->end())
                {
                    *(this->end()) = value;
                    this->used++;
                    return position;
                }
                typename GTUContainer<T>::baseIterator p,q;
                for (p=this->begin(); p!=this->end(); p++)
                {
                    if (p==position)
                    {
                        for ( q=this->end(); q!=p;)
                        {
                            --q;
                            T tm;
                            tm=*q;
                            q++;
                            *q=tm;
                            --q;
                        }
                        *p=value;
                        break;
                    }
                    
                }
                if (p==this->end())
                {
                    throw MyException("Your position is wrong.");
                }
                this->used++;
                temp=nullptr;
            }
        }
        cout << "Your value added. Successfuly." << endl;
        return position;
    }
}