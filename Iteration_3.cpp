/*
Author Details: 
  Shital Manoj Patil
  2324001011
  SY B77
*/

/*
TODO :
1] Store it in heap
2] Should be dynamic (no fixed size array)
3] Use a single array (person) instead of student & Teacher
4] Use flags to identify if person[cnt] is teacher or student -> set flag while entering details ->when displaying differentiate by using flag
5] Research on how to identify which element is at current position in array (dynamic casting methods)
6] Use lecture stuff (late-binding)
7] Use linked lists instead of array
*/

/*
ITERATION 3: 
> TODO Completed 1, 3, 4, 6 , 2 ,7
> Utilising Linkedlist instead of array for removal of upperbound(MAX) limitations
> Stored objects on Heap 
> Used a single array to store person pointers (create variables of Abs Class ) that point to heap objects instead of 2 arrays of student and teacher
> Used isTeacher flag to identify student or teacher from the people array
> *Used cout in classes of student & teacher( I think can be fixed using a common function getmoney() & PVF with overriding (late-binding)) 
> Late Binding implemented as using pure virtual func and overriding methods in child classes
  the call made is people[i]->display() the compiler determines obj is student or teacher at runtime 
> Created Personlist as pointer class and added methods such as addperson & displayAll for improved readability in main
> Using destructors to remove mem leaks
*/


#include <iostream>
#include <cstring>
using namespace std;

class Person {
private:
    unsigned int id;
    char name[10];
    bool isTeacher;

public:
    Person* next;  // Pointer to the next person in the list

    Person() : next(nullptr) {}
    virtual ~Person() {} //allows to call the correct destructor of child classes

    unsigned int getID() const { return id; }
    const char* getName() const { return name; }
    bool getIsTeacher() const { return isTeacher; }

    void setID(unsigned int personID) { id = personID; }
    void setName(const char* personName) {
        strncpy(name, personName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }
    void setIsTeacher(bool teacher) { isTeacher = teacher; }

    virtual void display() = 0; // PVF
};

class Student : public Person {
private:
    int fees;

public:
    Student() { this->setIsTeacher(false); }
    //int getFees() const { return fees; } unnecessary as 'fees' can be directly accessed
    void setFees(int studentFees) { fees = studentFees; }
    void display() override {
        cout << this->getID() << " | " << this->getName() << " | " << fees << endl;
    }
};

class Teacher : public Person {
private:
    int salary;

public:
    Teacher() { this->setIsTeacher(true); }
    //int getSalary() const { return salary; } unnecessary as 'salary' can be directly accessed
    void setSalary(int teacherSalary) { salary = teacherSalary; }
    void display() override {
        cout << this->getID() << " | " << this->getName() << " | " << salary << endl;
    }
};

class PersonList {
private:
    Person* head;

public:
    PersonList() : head(nullptr) {} // assigning nullptr to new node generated with member initalizer list 
    
    //destructor
    ~PersonList() { 
        Person* current = head;
        while (current != nullptr) {
            Person* next = current->next;
            delete current;
            current = next;
        }
    }

    void addPerson(Person* newPerson) { // adds person at beginning of the list
        newPerson->next = head;
        head = newPerson;
    }
    
    void displayCategory(bool isTeacher) {
        Person* current = head;
        while (current != nullptr) {
            if (current->getIsTeacher() == isTeacher) { // compares flags to identify student or teacher
                current->display(); // example of late-binding
            }
            current = current->next;
        }
    }
    
    void displayAll() {
        cout << "\nAll Members: ";
        cout << "\nStudents:" << endl;
        cout << "ID  | Name     | Fees" << endl;
        cout << "----------------------------" << endl;
        displayCategory(false);

        cout << "\nTeachers:" << endl;
        cout << "ID  | Name     | Salary" << endl;
        cout << "----------------------------" << endl;
        displayCategory(true);
    }
};

int main() {
    PersonList people;
    int choice;
    unsigned int id;
    char name[10];
    int money;

    cout << "ERP System\n-------------" << endl;
    while (true) {
        cout << "\nMenu: \n 1]Add Student\n 2]Add Teacher\n 3]Display All\n 4]Exit \nEnter Your Choice:";
        cin >> choice;

        switch (choice) {
            case 1:
            case 2:
                cout << "\nEnter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;

                if (choice == 1) {
                    cout << "Enter Fees: ";
                    cin >> money;
                    Student* student = new Student();
                    student->setID(id);
                    student->setName(name);
                    student->setFees(money);
                    people.addPerson(student);
                    cout << "Student added successfully!" << endl;
                } else {
                    cout << "Enter Salary: ";
                    cin >> money;
                    Teacher* teacher = new Teacher();
                    teacher->setID(id);
                    teacher->setName(name);
                    teacher->setSalary(money);
                    people.addPerson(teacher);
                    cout << "Teacher added successfully!" << endl;
                }
                break;

            case 3:
                people.displayAll();
                break;

            case 4:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
