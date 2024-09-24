#include "Student.h"

Student::Student(){         //default constructor
    m_id = -1;
    m_name = "";
    m_grade = "unknown";
    m_major = "unknown";
    m_gpa = -1;
    m_advisor = -1;
}

Student::Student(int id, string name, string grade, string major, double gpa, int advisor){         //overloaded constructor
    m_id = id;
    m_name = name;
    m_grade = grade;
    m_major = major;
    m_gpa = gpa;
    m_advisor = advisor;
}

Student::~Student(){
}

void Student::setAdvisorID(int newAdvisorID) {      //sets advisor iD
    m_advisor = newAdvisorID;
}

void Student::printInfo(){                  //prints student info
    cout << "Student Information:" << endl;
    cout << "------------------" << endl;
    cout << "Name: " << m_name << endl;
    cout << "ID: " << m_id << endl;
    cout << "Grade: " << m_grade << endl;
    cout << "Major: " << m_major << endl;
    cout << "GPA: " << m_gpa << endl;
    cout << "Advisor ID: " << m_advisor << endl;
    cout << "------------------" << endl;
}

bool Student::operator==(const Student& other) const {          //overloaded operators
    return this->m_id == other.m_id;
}

bool Student::operator<(const Student& other) const {
    return this->m_id < other.m_id;
}

bool Student::operator>(const Student& other) const {
    return this->m_id > other.m_id;
}

