#include "GTUSet.h"
namespace eagle{
    template<class T>
    GTUSet<T>::GTUSet():GTUSet<T>(10){
        //constructor delegation
    }
    template<class T>
    GTUSet<T>::GTUSet(int cap) {
        if (cap>1500 || cap<0)
        {
            throw MyException("Your capacity can not be grater than 1500 or less than 0");
        }
        else
        {
            capacity=cap;
            used=0;
            //allocate memory for shared pointer
            p = shared_ptr<T>(new T[cap],[](T * d){
                delete [] d;
            });
        }
        
    }
    template<class T>
    bool GTUSet<T>::empty(){
        if (used==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    template<class T>
    size_t GTUSet<T>::size(){
        return used;
    }
    template<class T>
    size_t GTUSet<T>::max_size(){
        return 1500;
    }
    template<class T>
    void GTUSet<T>::clear(){
        p.reset();
        p=shared_ptr<T>(new T[10],[](T * d){
            delete [] d;
        });
        used=0;
        capacity=10;
    }
    template<class T>
    typename GTUContainer<T>::baseIterator GTUSet<T>::insert(const T& value) {
        bool is_in=false;
        int index=-1;
        for (int i = 0; i < used ; i++)
        {
            if (p.get()[i]==value)
            {
                is_in=true;
                index=i;
            }
        }
        if (!is_in) //if element is not in the set
        {
            if (capacity > used+1) //if capacity is enough
            {
                p.get()[used]=value;
                used++;
            }
            else // if is not
            {
                if (capacity>1500)
                {
                    throw MyException("Your set capacity is full, you cannot insert a new element to the set.");
                }
                else
                {
                    if (1500-capacity > used*2)
                    {
                        capacity=used*2;
                    }
                    else
                    {
                        capacity+=1500-capacity;
                    }                  
                    shared_ptr<T> temp=shared_ptr<T>(new T[capacity],[](T * d){
                        delete [] d;
                    });
                    for (int i = 0; i < used; i++)
                    {
                        temp.get()[i]=p.get()[i];
                    }
                    p=temp;
                    p.get()[used]=value;
                    used++;
                    temp=nullptr;
                }
            }
            //return newly added element position
            cout << "Your value added. Successfuly." << endl;
            T* cp=&p.get()[0];
            cp=cp+used-1;
            shared_ptr<T> tmp(cp,[](T *d){});
            typename GTUContainer<T>::baseIterator position(tmp);
            return position;
        }
        else //if element is in the set
        {
            //return current position of element
            cout << "Your value already in the set!" << endl;
            T* cp=&p.get()[0];
            cp=cp+index;
            shared_ptr<T> tmp(cp,[](T *d){});
            typename GTUContainer<T>::baseIterator position(tmp);
            return position;
        }
        
    }
    template<class T>
    size_t GTUSet<T>::erase(const T& value) {
        //erase element that first find
        int index=-1,k=0;
        if(this->empty())
        {
            throw MyException("Set is empty!");
        }
        for (int i = 0; i < used ; i++)
        {
            if (p.get()[i]==value)
            {
                index=i;
            }
            
        }
        if (index!=-1)
        {
            for (int i = 0; i < used; i++)
            {
                if (i!=index)
                {
                    p.get()[k]=p.get()[i];
                    k++;
                }
                else if (i==used-1)
                {
                    T temp;
                    p.get()[k]=temp;
                }
                
            }
            used--;
            cout << "Your value was erased!" << endl;
            return 1;
        }
        else
        {
            cout << "Your value is not here" << endl;
            return 0;
        }
        
        
    }
    template<class T>
    typename GTUContainer<T>::baseIterator GTUSet<T>::begin(){
        typename GTUContainer<T>::baseIterator position(p);
        return position;

    }
    template<class T>
    typename GTUContainer<T>::baseIterator GTUSet<T>::end(){
        T* cp=&p.get()[0];//get first adress of shared pointer
        cp=cp+used;//increment it by using regular pointer
        shared_ptr<T> tmp(cp,[](T *d){}); //create a new shared pointer and by using constructor of shared pointer iterate the pointer
	    typename GTUContainer<T>::baseIterator position(tmp); //return iterated shared pointer
        return position;
    }
    template<class T>
    typename GTUContainer<T>::baseIterator GTUSet<T>::insert(typename GTUContainer<T>::baseIterator position,const T& value) {
        //insert by using position and value 
        bool is_in=false;
        int index=-1;
        for (int i = 0; i < used ; i++)
        {
            if (p.get()[i]==value)
            {
                is_in=true;
                index=i;
            }
        }
        if (!is_in) //if it is not in the set
        {
            if (capacity > used+1)
            {
                if (used==0) //if size is 0 add it begining of the set
                {
                    *(this->begin()) = value;
                    used++;
                    return position;
                }
                else if (position==this->end()) //if position is end add it end
                {
                    *(this->end()) = value;
                    used++;
                    return position;
                }
                /*other case of position do the swap*/
                typename GTUContainer<T>::baseIterator p,q;
                for (p=this->begin(); p!=this->end(); p++)
                {
                    if (p==position) //find the position
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
                        *p=value;//add element
                        break;//exit
                    }
                    
                }
                if (p==this->end()) //this is for when user try to add same element
                {
                    *(this->end()) = value;
                    used++;
                    return position;
                }
                used++;
                cout << "Your value added. Successfuly." << endl;
                return position;
            }
            else //if capcity is not enough
            {
                if (capacity>1500)
                {
                    throw MyException("Your set capacity is full, you cannot insert a new element to the set.");
                }
                else
                {
                    //adjust the capacity
                    if (1500-capacity > used*2)
                    {
                        capacity=used*2;
                    }
                    else
                    {
                        capacity+=1500-capacity;
                    }                  
                    shared_ptr<T> temp=shared_ptr<T>(new T[capacity],[](T * d){
                        delete [] d;
                    });
                    for (int i = 0; i < used; i++)
                    {
                        temp.get()[i]=p.get()[i];
                    }
                    p=temp;
                    //add the elemnt by using swap that is like above
                    if (position==this->end())
                    {
                        *(this->end()) = value;
                        used++;
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
                    used++;
                    temp=nullptr;
                }
            }
            cout << "Your value added. Successfuly." << endl;
            return position;
        }
        else
        {
            cout << "Your value already in the set!" << endl;
            T* cp=&p.get()[0];
            cp=cp+index;
            shared_ptr<T> tmp(cp,[](T *d){});
            typename GTUContainer<T>::baseIterator iter(tmp);
            return iter;
        }
        
    }

   
}