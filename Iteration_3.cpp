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
    virtual ~Person() {}

    unsigned int getID() const { return id; }
    const char* getName() const { return name; }
    bool getIsTeacher() const { return isTeacher; }

    void setID(unsigned int personID) { id = personID; }
    void setName(const char* personName) {
        strncpy(name, personName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }
    void setIsTeacher(bool teacher) { isTeacher = teacher; }

    virtual void display() = 0;
};

class Student : public Person {
private:
    int fees;

public:
    Student() { this->setIsTeacher(false); }
    int getFees() const { return fees; }
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
    int getSalary() const { return salary; }
    void setSalary(int teacherSalary) { salary = teacherSalary; }
    void display() override {
        cout << this->getID() << " | " << this->getName() << " | " << salary << endl;
    }
};

class PersonList {
private:
    Person* head;

public:
    PersonList() : head(nullptr) {}

    ~PersonList() {
        Person* current = head;
        while (current != nullptr) {
            Person* next = current->next;
            delete current;
            current = next;
        }
    }

    void addPerson(Person* newPerson) {
        newPerson->next = head;
        head = newPerson;
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

private:
    void displayCategory(bool isTeacher) {
        Person* current = head;
        while (current != nullptr) {
            if (current->getIsTeacher() == isTeacher) {
                current->display();
            }
            current = current->next;
        }
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
                cin.ignore();
                cin.getline(name, sizeof(name));

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
