#ifndef GTU_CONTAINER
#define GTU_CONTAINER
/* Since we have templates because of compiler we need to include .cpp files */
#include "GTUIterator.h"
#include "GTUIterator.cpp"
#include "GTUIteratorConst.h"
#include "GTUIteratorConst.cpp"
/*Since the compiler gives a warning I didn't put any throw keyword in the functions declaration*/
/*But in the implementation I used them.*/
namespace eagle{
    template<class T>
    class GTUContainer{
    public:
        //My inner iterator class
        class baseIterator : public GTUIterator<T>{
        public:
            baseIterator();
            baseIterator(shared_ptr<T> p);
            baseIterator(const baseIterator& object); 
        };
        //My inner const_iterator class
        class const_baseIterator : public GTUIteratorConst<T>{
        public:
            const_baseIterator();
            const_baseIterator(shared_ptr<T> p);
            const_baseIterator(const const_baseIterator& object);
            const_baseIterator& operator=(const baseIterator& a);
        };
        //other versions insert function will be implemented in derived classes.
        virtual bool empty() = 0;
        virtual size_t size() = 0;
        virtual size_t max_size() = 0;
        virtual baseIterator insert(const T& value)  = 0;
        virtual size_t erase(const T& value) = 0;
        virtual void clear() = 0;
        virtual baseIterator begin() = 0;
        virtual baseIterator end() = 0;
        
    };
}
#endif