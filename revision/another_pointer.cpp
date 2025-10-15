#include <iostream>

int main()
{
    std::string name="Allan";
    std::string* ptrName=&name;

    std::cout<<"Name: "<<name<<"\n";

    std::cout<<"Pointer Value: "<<ptrName<<"\n";

    return 0;
}