#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
#include <iostream>
#include <string>

class Student{
public:
Student();
Student(int id, string name, string grade, string major, double gpa, int advisor);
~Student();
void printInfo();
bool operator==(const Student& other) const;
bool operator<(const Student& other) const;
bool operator>(const Student& other) const;
void setAdvisorID(int newAdvisorID);

int m_id;
string m_name;
string m_grade;
string m_major;
double m_gpa;
int m_advisor;
private:

};
#endif

