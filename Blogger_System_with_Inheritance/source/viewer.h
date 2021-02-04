#ifndef VIEWER
#define VIEWER
#include "blog.h"
#include "owner.h"
namespace eagle{
    class Viewer:public Blog{
    public:
        Viewer();
        Viewer(int size);
        /*Big three*/
        Viewer(const Viewer& bObject);
        Viewer& operator=(const Viewer& rightSide);
        ~Viewer();
        int getSize() const{return numberOfReadPost;}
        void menu();
        void addReadPost(const Document& nPost);
        void showReadPost();
    protected:
        Document *readPost;
        int numberOfReadPost;
        int readCapacity;
        
    };
}
#endif