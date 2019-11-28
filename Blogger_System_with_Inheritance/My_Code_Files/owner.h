#ifndef OWNER
#define OWNER
#include "blog.h"
#include "person.h"
#include "viewer.h"
namespace eagle{
    class Owner:public Blog{
    public:
        Owner();
        Owner(int size);
        Owner(string name,int id,string password);
        /*Big three*/
        Owner(const Owner& bObject);
        Owner& operator=(const Owner& rightSide);
        ~Owner();
        /*since my variables are protected
        I don't need setter and getter*/
        Person& getPostOwner() {return myInformations;}
        void setOwner(const Person& own){myInformations=own;}
        void newPost(const Document& post);
        bool deletePost(string title);
        void menu();
        void showPosts();
        void showDeletedPost();
        int getSize() const;
        int getDeletedSize() const{return numberOfDeletedPost;}
        string getName() const{return myInformations.getName();}
        int getID() const{return myInformations.getID();}
        string getPassword() const{return myInformations.getPassword();}
        void setPassword(string p){myInformations.setPassword(p);}
        void setID(int id){myInformations.setID(id);}
        void setName(string n){myInformations.setName(n);}
        bool check(int id,string pass){return myInformations.checkInformation(id,pass);}
    private:
        Document *deletedPost;
        int numberOfDeletedPost;
        int deleteCapacity;
        Person myInformations;
    };
}
#endif