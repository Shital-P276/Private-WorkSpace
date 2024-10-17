/*
TODO :
1] -store-it-in-heap- 
2] Should be dynamic (no fixed size array)
3] -Use-a-single-array-(person)-instead-of-student-&-Teacher-
4] -use-flags-to-identify-if-person[cnt]-is-teacher-or-student-->set-flag-while-entering-details-->when-displaying-differentiate-by-using-flag
5] Research on how to identify which element is at current position in array
6] Use lecture stuff (late binding)
7] Use linked lists instead of array
*/

/*
ITERATION 2: 
> TODO Completed 1, 3, 4
> Stored objects on 
> Used a single array to store person instead of 2 arrays of student and teacher
> Used isTeacher flag to identify student or teacher from the people array
> Used cout in classes of student & teacher

*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAX 15

class Person {
private:
    unsigned int id;
    char name[10];
    bool isTeacher;

public:
    unsigned int getID() const {
		return id; 
	}
    const char* getName() const { 
		return name; 
	}
    bool getIsTeacher() const { 
		return isTeacher; 
	}

    void setID(unsigned int personID) { 
		id = personID; 
	}
    void setName(const char* personName) { 
        strncpy(name, personName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }
    void setIsTeacher(bool teacher) { 
		isTeacher = teacher; 
	}

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

int main() {
    Person* people[MAX];
    int count = 0;
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
                if (count < MAX) {
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
                        people[count] = student;
                        cout << "Student added successfully!" << endl;
                    } else {
                        cout << "Enter Salary: ";
                        cin >> money;
                        Teacher* teacher = new Teacher();
                        teacher->setID(id);
                        teacher->setName(name);
                        teacher->setSalary(money);
                        people[count] = teacher;
                        cout << "Teacher added successfully!" << endl;
                    }
                    count++;
                } else {
                    cout << "Maximum capacity reached!" << endl;
                }
                break;

            case 3:
				cout << "\nAll Members: ";
                cout << "\nStudents:" << endl;
                cout << "ID  | Name     | Fees" << endl;
                cout << "----------------------------" << endl;
				for (int i = 0; i < count; i++){
					if(!people[i]->getIsTeacher()){
						people[i]-> display();
					}
				}
				cout << "\nTeachers:" << endl;
                cout << "ID  | Name     | Salary" << endl;
                cout << "----------------------------" << endl;
				for (int i = 0; i < count; i++){
					if(people[i]->getIsTeacher()){
						people[i]-> display();
					}
				}
                break;

            case 4:
                cout << "Exiting..." << endl;
                for (int i = 0; i < count; i++) {
                    delete people[i];
                }
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
