#ifndef BLOG
#define BLOG
#include<iostream>
#include<vector>
#include "document.h"
using namespace std;
namespace eagle{
    class Blog{
    public:
        Blog();
        Blog(int size);
        /*Big three*/
        Blog(const Blog& bObject);
        Blog& operator=(const Blog& rightSide);
        ~Blog();
        /*since my variables are protected
        I don't need setter and getter*/
        Document& operator[](int index);
        Document& getPost(int index);
        void showPosts(int id);
        void menu();
    protected:
        Document *post;
        int numberOfPost;
        int capacity;
    };
}
#endif