#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    string phone;
    string room;

    Person(string n, string p, string r) : name(n), phone(p), room(r) {}

    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Room: " << room << endl;
    }
};

class Dean : public Person {
public:
    Dean(string n, string p, string r) : Person(n, p, r) {}
};

class AssociateDean : public Person {
public:
    AssociateDean(string n, string p, string r) : Person(n, p, r) {}
};

class Registrar : public Person {
public:
    Registrar(string n, string p, string r) : Person(n, p, r) {}
};

class Faculty : public Person {
public:
    Faculty(string n, string p, string r) : Person(n, p, r) {}
};

class HOD : public Person {
public:
    HOD(string n, string p, string r) : Person(n, p, r) {}
};

class AdminOfficer : public Person {
public:
    AdminOfficer(string n, string p, string r) : Person(n, p, r) {}
};

class Complaint {
public:
    string description;
    Person* initialHandler;
    Person* currentHandler;
    int daysPassed;

    Complaint(string desc, Person* handler, int days)
        : description(desc), initialHandler(handler), currentHandler(handler), daysPassed(days) {}

    // Escalate in Administrative Department
    void escalateAdmin() {
        if (dynamic_cast<AssociateDean*>(currentHandler)) {
            currentHandler = new Dean("Dean: Ranjan Bose", "A-707, R & D Block", "+91-11-26907481");
        } else if (dynamic_cast<Dean*>(currentHandler)) {
            currentHandler = new Registrar("Registrar: Dr. Deepika Bhaskar", "Room B-204", "+91-11-26907419");
        }
    }

    // Escalate in Academic Department
    void escalateAcademic(string department) {
        if (dynamic_cast<Faculty*>(currentHandler)) {
            if (department == "ECE") {
                currentHandler = new HOD("HOD: Dr. A V Subramanyam", "+91 011-26907437", "Room B-604");
            } else if (department == "CSE") {
                currentHandler = new HOD("HOD: Sambuddho Chakravarty", "011-26907478", "Room B-503");
            } else if (department == "CSB") {
                currentHandler = new HOD("HOD: GPS Raghava", "011-26907444", "Room A-302");
            }
        } else if (dynamic_cast<HOD*>(currentHandler)) {
            if (department == "ECE") {
                currentHandler = new AdminOfficer("Admin Officer: Sanjna Khosla", "011 2690 7593", "Room A-601");
            } else if (department == "CSE") {
                currentHandler = new AdminOfficer("Admin Officer: Priti Patwal", "01126907411", "Room A-501");
            } else if (department == "CSB") {
                currentHandler = new AdminOfficer("Admin Officer: Shipra Jain", "333-2222", "Room A-301");
            }
        }
    }

    void displayInitialHandler() {
        cout << "Your complaint was originally handled by: " << initialHandler->name << endl;
    }

    void displayCurrentHandler() {
        cout << "Now, after " << daysPassed << " days, your complaint is being handled by: " << currentHandler->name << endl;
    }
};

class Administration {
public:
    void handleComplaint(Complaint& complaint, string department, string academicDept = "") {
        complaint.displayInitialHandler();  // Display original handler

        if (complaint.daysPassed <= 3) {
            cout << "Your complaint is still in the initial stage with " << complaint.currentHandler->name << endl;
        } else if (complaint.daysPassed > 3 && complaint.daysPassed <= 6) {
            cout << "Since " << complaint.daysPassed << " days have passed, your complaint has been escalated to the next level." << endl;
            if (department == "IRD" || department == "Student Affairs" || department == "Faculty Affairs") {
                complaint.escalateAdmin();
            } else if (department == "Academic") {
                complaint.escalateAcademic(academicDept);
            }
            complaint.displayCurrentHandler();  // Display escalated handler
        } else if (complaint.daysPassed > 6) {
            cout << "Since more than 6 days have passed, your complaint has been escalated to the highest level." << endl;
            if (department == "IRD" || department == "Student Affairs" || department == "Faculty Affairs") {
                complaint.escalateAdmin();
                complaint.escalateAdmin(); // Escalate to the highest level
            } else if (department == "Academic") {
                complaint.escalateAcademic(academicDept);
                complaint.escalateAcademic(academicDept); // Escalate to the highest level
            }
            complaint.displayCurrentHandler();  // Display highest level handler
        }
    }
};

int main() {
    string department, complaintDescription, academicDept;
    int daysPassed;


    // Choose department
    cout << "Choose department (IRD/Student Affairs/Faculty Affairs/Academic): ";
    cin >> department;
    cin.ignore(); // Ignore remaining newline

    // Create initial handler based on the department
    Person* handler;
    if (department == "IRD") {
        handler = new AssociateDean("Associate Dean: Debarka Sengupta", "+91-11-26907446", "A-306, R & D Block");
    } else if (department == "Student Affairs") {
        handler = new AssociateDean("Associate Dean: Shobha Sundar Ram", "011-26907460", "Room B-606");
    } else if (department == "Faculty Affairs") {
        handler = new AssociateDean("Associate Dean: Sanjit Krishnan Kaul", "+91-11-26907457", "B-411, R & D Block");
    } else if (department == "Academic") {
        cout << "Choose Academic department (CSE/ECE/CSB): ";
        cin >> academicDept;
        cin.ignore(); // Ignore remaining newline
        if (academicDept == "ECE") {
            handler = new Faculty("Faculty: Abhijit Mitra", "011-26907450", "Room A-605");
        } else if (academicDept == "CSE") {
            handler = new Faculty("Faculty: Arani Bhattacharya", "011-26907434", "Room B-510");
        } else if (academicDept == "CSB") {
            handler = new Faculty("Faculty: Arjun Ray", "011-26907438", "Room A-310");
        } else {
            cout << "Invalid Academic department selected." << endl;
            return 1;
        }
    } else {
        cout << "Invalid department selected." << endl;
        return 1;
    }

    // Input complaint description
    cout << "Enter your complaint description: ";
    getline(cin, complaintDescription);

    // Input days since the complaint was filed
    cout << "How many days have passed since the complaint was filed? ";
    cin >> daysPassed;

    // Create a complaint
    Complaint complaint(complaintDescription, handler, daysPassed);

    // Display initial complaint status
    cout << "\nInitial complaint status:\n";
    // complaint.displayInitialHandler();

    Administration admin;

    // Handle the complaint based on the department and days passed
    admin.handleComplaint(complaint, department, academicDept);

    return 0;
}
