#include <iostream>
//create a structure
struct car{
    std::string brand;
    std::string model;
    int year;
};

int main()
{
    /*
    Structures(structs)= are a way to group several related variables
    into one place.
    Variable's in the structure are refered as a member of the structure.
    Data Types: int, string, bool
    */

    //Create a structure and store it in my car
    car myCar1;
    myCar1.brand="BMW";
    myCar1.model="X6";
    myCar1.year=2000;

    //display
    std::cout<<"Car Name: "<<myCar1.brand<<"\n";
    std::cout<<"Model: "<<myCar1.model<<"\n";
    std::cout<<"Year: "<<myCar1.year<<"\n";

    return 0;
}