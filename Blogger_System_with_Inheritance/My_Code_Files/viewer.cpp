#include "viewer.h"
namespace eagle{
    Viewer::Viewer():Blog(),readCapacity(10),numberOfReadPost(0){
        readPost=new Document[readCapacity];
    }
    Viewer::Viewer(int size):Blog(),readCapacity(size),numberOfReadPost(0){
        readPost=new Document[readCapacity];
    }
    Viewer::Viewer(const Viewer& bObject):Blog(bObject),readCapacity(bObject.readCapacity),numberOfReadPost(bObject.numberOfReadPost){
        readPost=new Document[readCapacity];
        for (int i = 0; i < numberOfReadPost; i++)
        {
            readPost[i]=bObject.readPost[i];
        }
    }
    Viewer& Viewer::operator=(const Viewer& rightSide){
        if (readCapacity<=rightSide.numberOfReadPost)
        {
            readCapacity=rightSide.numberOfReadPost*2;
            delete[] readPost;
            readPost=new Document[readCapacity];
           
        }
        numberOfReadPost=rightSide.numberOfReadPost;
        for (int i = 0; i < numberOfReadPost; i++)
        {
            readPost[i]=rightSide.readPost[i]; 
        }
        return *this;
    }
    
    void Viewer::menu(){
        cout << "Welcome Dear Reader " << endl;
        cout << "What Do you want to do?"<< endl;
        cout << "[1] Read a new Post."<< endl;
        cout << "[2] Show Your Already Read Post."<< endl;
        cout << "[0] Exit."<< endl;  
    }
    void Viewer::addReadPost(const Document& nPost){
        if (readCapacity<=numberOfReadPost)
        {
            Document *temp;
            readCapacity=numberOfReadPost*2;
            temp=new Document[readCapacity];
            for (int d = 0; d < numberOfReadPost; d++)
            {
                temp[d]=readPost[d];
            }
            delete[] readPost;
            readPost=new Document[readCapacity];
            for (int d = 0; d < numberOfReadPost; d++)
            {
                readPost[d]=temp[d];
            }
                            
        }
        readPost[numberOfReadPost] = nPost;
        numberOfReadPost++;
    }
    void Viewer::showReadPost(){
        if (numberOfReadPost==0)
        {
            cout << "you didn't read anything yet!" << endl;
        }
        else
        {
            for (int i = 0; i < numberOfReadPost; i++)
            {
                cout << i+1 << ") " << readPost[i].getTitle() << endl;
            }
        }
    }
    Viewer::~Viewer(){
        delete[] readPost;
    }
}
