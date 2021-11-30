#include <item.h>
#include <string.h>
#include <iostream>

Item::Item(){
    strcpy(this->name,"null");
    strcpy(this->description,"Null.");
}

Item::Item(char icon, const char* name, const char* description){
    this->icon=icon;
    strcpy(this->name,name);
    strcpy(this->description,description);
}

Item::Item(const char* name, const char* description){
    strcpy(this->name,name);
    strcpy(this->description,description);
}

void Item::print(){
    std::cout<<this->name<<" - "<<this->description;
}