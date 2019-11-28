#include "blog.h"
namespace eagle{
    Blog::Blog():capacity(10),numberOfPost(0){
        post=new Document[capacity];
    }
    Blog::Blog(int size):capacity(size),numberOfPost(0){
        post=new Document[capacity];
    }
    Blog::Blog(const Blog& bObject):capacity(bObject.capacity),numberOfPost(bObject.numberOfPost){
        post=new Document[capacity];
        for (int i = 0; i < numberOfPost; i++)
        {
            post[i]=bObject.post[i];
        }
    }
    Blog& Blog::operator=(const Blog& rightSide){
        if (capacity<=rightSide.numberOfPost)
        {
            capacity=rightSide.numberOfPost*2;
            delete[] post;
            post=new Document[capacity];
           
        }
        numberOfPost=rightSide.numberOfPost;
        for (int i = 0; i < numberOfPost; i++)
        {
            post[i]=rightSide.post[i]; 
        }
        return *this;
    }
    Document& Blog::operator[](int index){
        if (index<0 || index>numberOfPost)
        {
            cout << "Your index is not correct" << endl;
            exit(1);
        }
        return post[index];
    }
    Document& Blog::getPost(int index){
        if (index<0 || index>numberOfPost)
        {
            cout << "Your index is not correct" << endl;
            exit(1);
        }
        return post[index];
    }
    void Blog::menu(){
        //this is not for base class
        cout << "wrong call!!" << endl;
        exit(1);
    }
    void Blog::showPosts(int id){
        //this is not for base class
        cout << "wrong call!!" << endl;
        exit(1);
    }
    Blog::~Blog(){
        delete[] post;
    }
}
