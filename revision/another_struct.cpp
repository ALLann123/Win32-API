#include <iostream>
// create a structure for students
struct student
{
    /* data */
    std::string name;
    int age;
    char grade;
};

int main()
{
    // create two structures
    student stud1;
    student stud2;

    stud1.name = "Allan";
    stud1.age = 28;
    stud1.grade = 'C';

    // another student
    stud2.name = "Rehema";
    stud2.age = 17;
    stud2.grade = 'B';

    // display
    std::cout << "----First Student Details----" << "\n";
    std::cout << "Name: " << stud1.name << "\n";
    std::cout << "Age: " << stud1.age << "\n";
    std::cout << "Grade:" << stud1.grade << "\n";
    std::cout << "\n";
    std::cout << "----Second Student Details----" << "\n";
    std::cout << "Name: " << stud2.name << "\n";
    std::cout << "Age: " << stud2.age << "\n";
    std::cout << "Grade:" << stud2.grade << "\n";

    return 0;
}
