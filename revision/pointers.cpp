#include <iostream>

int main()
{
    /*
    Pointers= is a variable that stores the memory address as its value

    This variable points to a data type(int, string) of the same type
    and is created with the * operator. The address of the variable you're 
    working with is assigned to the pointer
    */
    std::string food="pizza";  //the variable
    std::string* ptr=&food;  //stores the mem address of food

    //output food
    std::cout<<"String: "<<food<<"\n";

    //output the memory address
    std::cout<<"Memory Address: "<<&food<<"\n";

    //output memory value on the pointer
    std::cout<<"Pointer Value: "<<ptr<<"\n";

    return 0;
}