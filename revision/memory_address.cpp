#include <iostream>

int main()
{
    /*
    &= Displays the memory address of a variable; Location where the
    variable is stored on the computer.
    When a variable is created in C++ a memory address is assigned to it

    */
    // First access
    std::string food = "Pizza";
    int age = 24;

    std::cout << "String memory address= " << &food << "\n";
    std::cout << "Age address= " << &age;
    /*
    NOTES:
        The memory address is in hexadecimal(0x5ffafffac0)
    IMPORTANCE:
        Useful in Pointers because they give you the ability to manipulate
        data in a compuuter's memory---Reduces the code and improce the performance
    */

    return 0;
}