#include "owner.h"
#include "viewer.h"
namespace eagle{
    Owner::Owner():Blog(),deleteCapacity(10),numberOfDeletedPost(0){
        deletedPost=new Document[deleteCapacity];
        myInformations.setName("");
        myInformations.setID(0);
        myInformations.setPassword("");
    }
    Owner::Owner(int size):Blog(),deleteCapacity(size),numberOfDeletedPost(0){
        deletedPost=new Document[deleteCapacity];
        myInformations.setName("");
        myInformations.setID(0);
        myInformations.setPassword("");
    }
    Owner::Owner(string name,int id,string password):Blog(),deleteCapacity(10),numberOfDeletedPost(0),myInformations(name,id,password){
        
    }
    Owner::Owner(const Owner& bObject):Blog(bObject),deleteCapacity(bObject.deleteCapacity),numberOfDeletedPost(bObject.numberOfDeletedPost){
        deletedPost=new Document[deleteCapacity];
        for (int i = 0; i < numberOfDeletedPost; i++)
        {
            deletedPost[i]=bObject.deletedPost[i];
        }
        myInformations=bObject.myInformations;
    }
    Owner& Owner::operator=(const Owner& rightSide){
        if (deleteCapacity<=rightSide.numberOfDeletedPost)
        {
            deleteCapacity=rightSide.numberOfDeletedPost*2;
            delete[] deletedPost;
            deletedPost=new Document[deleteCapacity];
           
        }
        numberOfDeletedPost=rightSide.numberOfDeletedPost;
        for (int i = 0; i < numberOfDeletedPost; i++)
        {
            deletedPost[i]=rightSide.deletedPost[i]; 
        }
        return *this;
    }
    bool Owner::deletePost(string title){
        int k=0;
        for (int i = 0; i < numberOfPost; i++)
        {
            if (post[i].getTitle()==title && post[i].getDocOwner().getID()==myInformations.getID())
            {
                for (int j = 0; j < numberOfPost; j++)
                {
                    if (j!=i)
                    {
                        post[k]=post[j];
                        k++;
                    }
                    else//add deleted
                    {
                        if (deleteCapacity<=numberOfDeletedPost)
                        {
                            Document *temp;
                            deleteCapacity=numberOfDeletedPost*2;
                            temp=new Document[deleteCapacity];
                            for (int d = 0; d < numberOfDeletedPost; d++)
                            {
                                temp[d]=deletedPost[d];
                            }
                            delete[] deletedPost;
                            deletedPost=new Document[deleteCapacity];
                            for (int d = 0; d < numberOfDeletedPost; d++)
                            {
                                deletedPost[d]=temp[d];
                            }
                            
                        }
                        deletedPost[numberOfDeletedPost]= post[i];
                        numberOfDeletedPost++;
                    }
                }
                numberOfPost--;
                return true;
            }
        }
        return false;
        
    }
    void Owner::menu(){
        cout << "Welcome Blogger " << myInformations.getName() << endl;
        cout << "What Do you want to do?"<< endl;
        cout << "[1] Write a new Post."<< endl;
        cout << "[2] Delete a Post."<< endl;
        cout << "[3] Show Your Post."<< endl;
        cout << "[4] Show Your Deleted Post."<< endl;
        cout << "[5] Show Your Information."<< endl;
        cout << "[0] Exit."<< endl;  
    }
    int Owner::getSize() const{
        int j=0;
        for (int i = 0; i < numberOfPost; i++)
        {
            if (post[i].getDocOwner().getID()==myInformations.getID())
            {
               j++;
            }
        }
        return j;
    }
    void Owner::showPosts(){
        if (getSize()==0)
        {
            cout << "you don't have post yet!\n";
            return;
        }
        for (int i = 0; i < numberOfPost; i++)
        {
            if (post[i].getDocOwner().getID()==myInformations.getID())
            {
                cout << i+1 << ") " << post[i].getTitle() << endl;
            }
            
        }
        
    }
    void Owner::showDeletedPost(){
        if (numberOfDeletedPost==0)
        {
            cout << "you didn't delete anything yet!\n";
        }
        else
        {
            for (int i = 0; i < numberOfDeletedPost; i++)
            {
                cout << i+1 << ") " << deletedPost[i].getTitle() << endl;
            }
        }
    }
    void Owner::newPost(const Document& nPost){
        if (capacity<=numberOfPost)
        {
            Document *temp;
            capacity=numberOfPost*2;
            temp=new Document[capacity];
            for (int d = 0; d < numberOfPost; d++)
            {
                temp[d]=post[d];
            }
            delete[] post;
            post=new Document[capacity];
            for (int d = 0; d < numberOfPost; d++)
            {
                post[d]=temp[d];
            }
                            
        }
        post[numberOfPost] = nPost;
        numberOfPost++;
    }
    Owner::~Owner(){
        delete[] deletedPost;
    }
}
