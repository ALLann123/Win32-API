#include <iostream>

int main()
{
    /*
    sizeof()= is an operator which measures the amount of memory used by
    a variable or data type.
    When Variable is specified it indicates how many bytes are needed to
    store data of that type.
    */
    /*1-------Count number of elements in an array*/
    int myNumber[5]={10,20,30,40,50};

    int getArraylength=sizeof(myNumber)/sizeof(int);

    std::cout<<"Array Length: "<<getArraylength<<"\n";


    //2--- Othe Data Type Memory sizes
    long int myLInt=5;
    std::cout<<"Long Size= "<<sizeof(myLInt)<<"\n";

    char* myName="Allan Mbugua";
    std::cout<<"Char Size= "<<sizeof(myName)<<"\n";

    std::string course="Engineering";
    std::cout<<"String Size= "<<sizeof(course)<<"\n";

    return 0;
}