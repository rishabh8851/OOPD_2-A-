#include <iostream>
#include <string>
#include <iostream>
#include <cstring> // for strcmp
#include <limits>
using namespace std;

class Person {
public:
    string name;
    string phoneNumber;
    string roomNumber;

    Person() {}
    Person(string n, string p, string r) : name(n), phoneNumber(p), roomNumber(r) {}

    void display() {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Room Number: " << roomNumber << endl;
    }
};

class Department {
private:
    Person hod;
    Person adminOfficer;
    Person faculty[5];

public:
    Department(Person h, Person admin, Person facs[5]) : hod(h), adminOfficer(admin) {
        for (int i = 0; i < 5; ++i) {
            faculty[i] = facs[i];
        }
    }

    Person* findPerson(string name) {
        if (hod.name == name) return &hod;
        if (adminOfficer.name == name) return &adminOfficer;
        for (int i = 0; i < 5; ++i) {
            if (faculty[i].name == name) return &faculty[i];
        }
        return nullptr;
    }
};

class Administration {
private:
    Department* departments[6];
     
public:
    Administration() {
        // ECE Department
        Person hodECE("Dr. A V Subramanyam", "+91 011-26907437", "Room B-604");
        Person adminECE("Sanjna Khosla", "011 2690 7593", "Room A-601");
        Person facultyECE[5] = {
            Person("Abhijit Mitra", "011-26907450", "Room A-605"),
            Person("Anuj Grover", "011-26907494", "Room A-610"),
            Person("Sneh Saurabh", "011-26907456", "Room B-608"),
            Person("Sujay Deb", "011-26907452", "Room A-607"),
            Person("Sumit J Darak", "011-26907427", "Room B-605")
        };
        departments[0] = new Department(hodECE, adminECE, facultyECE);

        // CSE Department
        Person hodCSE("Sambuddho Chakravarty", "011-26907478", "Room B-503");
        Person adminCSE("Priti Patwal", "01126907411", "Room A-501");
        Person facultyCSE[5] = {
            Person("Arani Bhattacharya", "011-26907434", "Room B-510"),
            Person("Debajyoti Bera", "011-26907442", "Room B-508"),
            Person("Bapi Chatterjee", "011-26907371", "Room B-402"),
            Person("Pankaj Jalote", "011-26907499", "Room A-705"),
            Person("Saket Anand", "011-26907425", "Room B-410")
        };
        departments[1] = new Department(hodCSE, adminCSE, facultyCSE);

        // CSB Department
        Person hodCSB("GPS Raghava", "011-26907444", "Room A-302");
        Person adminCSB("Shipra Jain", "333-2222", "Room A-301");
        Person facultyCSB[5] = {
            Person("Arjun Ray", "011-26907438", "Room A-310"),
            Person("Ganesh Bagler", "01126907443", "Room A-305"),
            Person("Gaurav Ahuja", "01126907375", "Room A-303"),
            Person("Jaspreet Kaur Dhanjal", "01126907522", "Room A-307"),
            Person("N. Arul Murugan", "01126907372", "Room A-311")
        };
        departments[2] = new Department(hodCSB, adminCSB, facultyCSB);

        // CSD Department
        Person hodCSD("Dr. Aman Parnami", "444-1111", "Room 401");
        Person adminCSD("Binu Ann Joseph", "444-2222", "Room 402");
        Person facultyCSD[5] = {
            Person("Dr. Anmol Srivastava", "444-3333", "Room 403"),
            Person("Dr. Richa Gupta", "444-4444", "Room 404"),
            Person("Dr. Kalpana Shankhwar", "444-5555", "Room 405"),
            Person("Dr. Jainendra Shukla", "444-6666", "Room 406"),
            Person("Dr. Rajiv Ratn Shah", "444-7777", "Room 407")
        };
        departments[3] = new Department(hodCSD, adminCSD, facultyCSD);

        // CSAM Department
        Person hodCSAM("Kaushik Kalyanaraman", "011-26907456", "Room B-302");
        Person adminCSAM("Risha Lal", "011-26907548", "Room B-301");
        Person facultyCSAM[5] = {
            Person("Anuradha Sharma", "555-3333", "Room 503"),
            Person("Manuj Mukherjee", "555-4444", "Room 504"),
            Person("Monika Arora", "555-5555", "Room 505"),
            Person("Nabanita Ray", "555-6666", "Room 506"),
            Person("Debika Banerjee", "555-7777", "Room 507")
        };
        departments[4] = new Department(hodCSAM, adminCSAM, facultyCSAM);

        // CSSS Department
        Person hodCSSS("J. V. Meenakshi", "011 26907 535", "Room B-205");
        Person adminCSSS("Rubina Thakur", "91 11 2690 7497", "Room B-201");
        Person facultyCSSS[5] = {
            Person("Manohar Kumar", "011 26907 557", "Room B-207"),
            Person("Mrinmoy Chakrabarty", "011 26907 363", "Room A-202"),
            Person("Nishad Patnaik", "011 26907 364", "Room A-205"),
            Person("Paro Mishra", "011 26907 570", "Room A-209"),
            Person("Praveen Priyadarshi", "011 26907 359", "Room A-203")
        };
        departments[5] = new Department(hodCSSS, adminCSSS, facultyCSSS);
    }

    Person* getPersonDetails(string name) {
        for (int i = 0; i < 6; ++i) {
            Person* person = departments[i]->findPerson(name);
            if (person) return person;
        }
        return nullptr;
    }
};


int main() {
    Administration admin;
    int choice;
    string personName;

    do {
        cout << "\n1. Search for a person\n2. Exit\nEnter your choice: ";
        // cin >> choice;
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

            Person* person = admin.getPersonDetails(personName);
            if (person) {
                person->display();
            } else {
                cout << "Error: Person not found!" << endl;  // Handle the case when person is not found
            }
        } else if (choice != 2) {
            cout << "Invalid choice. Please enter 1 or 2." << endl;  // Handle invalid choice
        }

    } while (choice != 2);

    cout << "Exiting..." << endl;
    return 0;
}
