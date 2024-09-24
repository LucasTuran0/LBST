#include "Faculty.h"

Faculty::Faculty(){     //default constructor
    m_id = -1;
    m_name = "";
    m_title = "unknown";
    m_department = "unknown";
    
}

Faculty::Faculty(int id, string name, string title, string department){         //overloaded constructor
    m_id = id;
    m_name = name;
    m_title = title;
    m_department = department;
}

Faculty::~Faculty(){
}

void Faculty::printInfo() {     //prints faculty info
    cout << "Faculty Information:" << endl;
    cout << "------------------" << endl;
    cout << "ID: " << m_id << endl;
    cout << "Name: " << m_name << endl;
    cout << "Title: " << m_title << endl;
    cout << "Department: " << m_department << endl;
    cout << "Advisees: ";
    
    if (advisees.isEmpty()) {
        cout << "None";
    } else {
        for (int i = 0; i < advisees.getSize(); ++i) {
            cout << advisees.get(i);
            if (i < advisees.getSize() - 1) {
                cout << ", ";  // Print a comma between IDs
            }
        }
    }

    cout << endl;
    cout << "------------------" << endl;
}

void Faculty::addAdvisee(int studentID) {       //adds student id to list of advisees
    advisees.addBack(studentID);
}

bool Faculty::removeAdvisee(int studentID) {        //removes advisee
    for (int i = 0; i < advisees.getSize(); ++i) {
        if (advisees.get(i) == studentID) {
            advisees.remove(i);
            return true;
        }
    }
    return false;
}

void Faculty::printAdvisees() {     //prints all advisees
    cout << "Advisees: ";
    for (int i = 0; i < advisees.getSize(); ++i) {
        cout << advisees.get(i) << " ";
    }
    cout << endl;
}

bool Faculty::operator==(const Faculty& other) const {      //overloaded operators
    return this->m_id == other.m_id;
}

bool Faculty::operator<(const Faculty& other) const {
    return this->m_id < other.m_id;
}

bool Faculty::operator>(const Faculty& other) const {
    return this->m_id > other.m_id;
}
