#include "document.h"
namespace eagle{
    Document::Document():Document("",""){
    }
    Document::Document(string textValue,string titleValue):text(textValue),title(titleValue){
    }
}