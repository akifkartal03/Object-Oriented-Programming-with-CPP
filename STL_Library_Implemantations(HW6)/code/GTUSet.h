#ifndef GTU_SET
#define GTU_SET
#include "GTUContainer.h"
namespace eagle{
    template<class T>
    class GTUSet : public GTUContainer<T>{
    public:
        /*These are from GTUContainer Base Class*/
        GTUSet();
        GTUSet(int cap);
        bool empty() override;
        size_t size() override;
        size_t max_size() override;
        typename GTUContainer<T>::baseIterator insert(const T& value) override;
        size_t erase(const T& value) override;
        void clear() override;
        typename GTUContainer<T>::baseIterator begin() override;
        typename GTUContainer<T>::baseIterator end() override;
        //new insert function function with position
        typename GTUContainer<T>::baseIterator insert(typename GTUContainer<T>::baseIterator position,const T& value);
    protected:
        shared_ptr<T> p;
        int used;
        int capacity;
    };

}
#endif