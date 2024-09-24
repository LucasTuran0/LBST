#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <iostream>
#include <vector>
#include "DblList.h"
using namespace std;

class Faculty {
public:
    Faculty();
    Faculty(int id, string name, string title, string department);
    ~Faculty();

    void printInfo();
    void addAdvisee(int studentID);
    bool removeAdvisee(int studentID);
    void printAdvisees();
    
    bool operator==(const Faculty& other)const;
    bool operator<(const Faculty& other)const;
    bool operator>(const Faculty& other)const;

    int m_id;
    string m_name;
    string m_title;
    string m_department;
    DblList<int> advisees; 
private:
    
};

#endif
