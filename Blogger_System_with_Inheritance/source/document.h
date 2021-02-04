#ifndef DOCUMENT
#define DOCUMENT
#include<iostream>
#include "person.h"
using namespace std;
namespace eagle{
    class Document{
    public:
        Document();
        Document(string textValue,string titleValue);
        string getText() const {return text;}
        string getTitle() const {return title;}
        Person& getDocOwner() {return ownerOfDocument;}
        void setText(string textValue) {text=textValue;}
        void setTitle(string titleValue) {title=titleValue;}
        void setOwner(const Person& own){ownerOfDocument=own;}
    private:
        string text;
        string title;
        Person ownerOfDocument;
    };

}
#endif