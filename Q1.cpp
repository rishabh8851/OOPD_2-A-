#include <iostream>
#include <cstring> // for strcmp
#include <limits>
using namespace std;

class Person {
public:
    string name;
    string roomNumber;
    string telePhnNo;
    string email;

    Person(string n, string rN, string telephn, string mail)
        : name(n), roomNumber(rN), telePhnNo(telephn), email(mail) {}

    Person() {}

    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "Room Number: " << roomNumber << endl;
        cout << "Telephone: " << telePhnNo << endl;
        cout << "Email: " << email << endl;
    }
};

class Dean : public Person {
    string depart;
public:
    Dean(string n, string rN, string telephn, string mail, string dep)
        : Person(n, rN, telephn, mail), depart(dep) {}

    void display() override {
        Person::display();
        cout << "Dean of department: " << depart << endl;
    }
};

class AssociateDean : public Person {
    string depart;
public:
    AssociateDean(string n, string rN, string telephn, string mail, string dep)
        : Person(n, rN, telephn, mail), depart(dep) {}

    void display() override {
        Person::display();
        cout << "Associate Dean of department: " << depart << endl;
    }
};

class Library : public Person {
    string depart;
public:
    Library(string n, string rn, string telephn, string mail, string dep)
        : Person(n, rn, telephn, mail), depart(dep) {}

    void display() override {
        Person::display();
        cout << "Department is: " << depart << endl;
    }
};

class Registrar : public Person {
public:
    Registrar(string n, string r, string t, string e)
        : Person(n, r, t, e) {}

    void display() override {
        cout << "Registrar" << endl;
        Person::display();
    }
};

class Department {
public:
    string deptName;
    static const int maxMembers = 10;  // Set a fixed number of members
    Person* members[maxMembers];
    int memberCount;

    Department(string name) : deptName(name), memberCount(0) {
        memset(members, 0, sizeof(members));  // Initialize member array
    }

    void addMember(Person* p) {
        if (memberCount < maxMembers) {
            members[memberCount++] = p;
        } else {
            cout << "Error: Maximum number of members reached for department " << deptName << endl;
        }
    }

    Person* findPerson(string name) {
        for (int i = 0; i < memberCount; ++i) {
            if (members[i]->name == name) {
                return members[i];
            }
        }
        return nullptr;
    }
};

class Administration {
public:
    static const int maxDepartments = 10;  // Set a fixed number of departments
    Department* dep[maxDepartments];
    int departmentCount;

    string registrarName = "Dr. Deepika Bhaskar";
    string registrarRoom = "Room No. B-204 (Academic Block)";
    string registrarPhone = "+91-11-26907419, +91-11-26907410";
    string registrarEmail = "registrar@iiitd.ac.in";

    Administration() : departmentCount(0) {
        // Initialize departments and members directly
        addDepartment(new Department("IRD"), new Dean("Vivek Ashok Bohara", "A-609, R & D Block", "+91-11-26907454", "dird@iiitd.ac.in", "IRD"), new AssociateDean("Debarka Sengupta", "A-306, R & D Block", "+91-11-26907446", "adird@iiitd.ac.in", "IRD"));
        addDepartment(new Department("Corporate Relations & Entrepreneurship (DCRE)"), new Dean("Pankaj Vajpayee", "Room 102", "+91-11-26907515", "dcre@iiitd.ac.in", "Corporate Relations & Entrepreneurship (CRE)"));
        addDepartment(new Department("Academic Affairs (AA)"), new Dean("Sumit J Darak", "Room 105", "+91-11-26907427", "doaa@iiitd.ac.in", "Academic Affairs (AA)"));
        addDepartment(new Department("Student Affairs"), new Dean("Shobha Sundar Ram", "Room No. B-606 (R & D Block)", "011-26907460", "dshobha@iiitd.ac.in", "Student Affairs (SA)"));
        addDepartment(new Department("Faculty Affairs"),new Dean("Ranjan Bose","A-707, R & D Block","+91-11-26907481","dofa@iiitd.ac.in","Faculty Affairs") ,new AssociateDean("Sanjit Krishnan Kaul", "B-411, R & D Block", "+91-11-26907457", "adofa@iiitd.ac.in", "Faculty Affairs"));
        addDepartment(new Department("Communication and Alumni Affairs (CAA)"), new Dean("Sonia Baloni Ray", "B-210, R & D Block", "+91-11-26907424", "dcaa@iiitd.ac.in", "Communication and Alumni Affairs (CAA)"));
        addDepartment(new Department("Library"), new Library("Librarian", "Room 106", "011-678901", "librarian@iiitd.ac.in", "Library"));
    }

    void addDepartment(Department* d, Person* p1, Person* p2 = nullptr) {
        if (departmentCount < maxDepartments) {
            dep[departmentCount++] = d;
            d->addMember(p1);
            if (p2) d->addMember(p2);
        } else {
            cout << "Error: Maximum number of departments reached!" << endl;
        }
    }

    Person* getPersonDetails(string name) {
        for (int i = 0; i < departmentCount; ++i) {
            Person* person = dep[i]->findPerson(name);
            if (person) {
                return person;
            }
        }
        return nullptr;
    }
};

#include <iostream>
#include <limits>
using namespace std;

int main() {
    Administration admin;

    string personName;
    int choice;

    do {
        cout << "\n1. Search for a person\n2. Exit\nEnter your choice: ";
        
        if (!(cin >> choice)) { // Input validation
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a valid number (1 or 2)." << endl;
            continue; // Ask for input again
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // To clear the newline character from the input buffer

        if (choice == 1) {
            cout << "Enter the name of the person: ";
            getline(cin, personName);

            // Check if the input matches the registrar's name
            if (personName == admin.registrarName) {
                cout << "Name: " << admin.registrarName << endl;
                cout << "Room Number: " << admin.registrarRoom << endl;
                cout << "Telephone: " << admin.registrarPhone << endl;
                cout << "Email: " << admin.registrarEmail << endl;
            } else {
                Person* person = admin.getPersonDetails(personName);
                if (person) {
                    person->display();
                } else {
                    cout << "Error: Person not found!" << endl;
                }
            }
        } else if (choice != 2) {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
    } while (choice != 2);

    return 0;
}
