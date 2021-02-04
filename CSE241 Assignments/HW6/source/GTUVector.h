#ifndef GTU_VECTOR
#define GTU_VECTOR
#include "GTUSet.h"
//create a vector class which derives from set class not to implement same function i.e empty() function
namespace eagle{
    template<class T>
    class GTUVector : public GTUSet<T>{
    public:
        GTUVector();
        GTUVector(int cap);
        typename GTUContainer<T>::baseIterator insert(const T& value)  ; //redefine
        const T& operator[](int index) const ;//new operator for vector
        T& operator[](int index) ; //new operator for vector
        // 2. overload of insert for vector also it is redefined function
        typename GTUContainer<T>::baseIterator insert(typename GTUContainer<T>::baseIterator position,const T& value) ;
    };

}
#endif