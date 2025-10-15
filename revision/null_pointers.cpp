#include <iostream>

int main()
{
    /*
    NULL Pointer= Indicates the absence of a valid memory address in C++.
    Tells the pointer its not pointing to any memory address. DOne during declaration

    */
    // create a null pointer for holding an int value
    int *ptrNum = NULL;

    // check pointer if null before dereferencing
    if (ptrNum == NULL)
    {
        std::cout << "Pointer is NULL!!" << std::endl;
    }
    else
    {
        std::cout << "Pointer is not Null" << "\n";
    }

    // assign a value to the pointer
    int num = 78;
    ptrNum = &num;

    // check pointer if null before dereferencing
    if (ptrNum == NULL)
    {
        std::cout << "Pointer is NULL!!" << std::endl;
    }
    else
    {
        std::cout << "Pointer is not Null" << "\n";
        std::cout << "Pointer Address: " << ptrNum << "\n";
        std::cout << "Value Stored at " << ptrNum << ":" << *ptrNum << "\n";
    }

    return 0;
}