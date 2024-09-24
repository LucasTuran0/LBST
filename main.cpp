#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>


int main() {
    LazyBST<Student> studentDb;
    LazyBST<Faculty> facultyDb;


    while(true){

        cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
        cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
        cout << "3. Find and display student information given the student id" << endl;
        cout << "4. Find and display faculty information given the faculty id" << endl;
        cout << "5. Add a new student" << endl;
        cout << "6. Delete a student given the id" << endl;
        cout << "7. Add a new faculty member" << endl;
        cout << "8. Delete a faculty member given the id." << endl;
        cout << "9. Change a students advisor given the student id and the new faculty id." << endl;
        cout << "10. Remove an advisee from a faculty member given the ids" << endl;
        cout << "11. Exit" << endl;


        int choice;
        cout << "Select action" << endl;
        cin >> choice;

        switch(choice){
            case 1:{
                studentDb.printTreeInOrder();
            }
            break;

            case 2:{
            facultyDb.printTreeInOrder();
            }
            break;

            case 3:{
            int queryID;
            cout << "Enter desired student ID" << endl;
            cin >> queryID;

            Student student = studentDb.findByID(queryID);
            student.printInfo();

            break;
            }
            case 4:{
            int queryID;
            cout << "Enter desired faculty ID" << endl;
            cin >> queryID;

            Faculty faculty = facultyDb.findByID(queryID);
            faculty.printInfo();
            break;
            }

            case 5:{
            cout << "Enter ID" << endl;
            int newID;
            cin >> newID;

            cout << "Enter name" << endl;
            string newName;
            cin >> newName;

            cout << "Enter grade" << endl;
            string newGrade;
            cin >> newGrade;

            cout << "Enter major" << endl;
            string newMajor;
            cin >> newMajor;
            
            cout << "Enter GPA" << endl;
            double newGPA;
            cin >> newGPA;

            cout << "Enter advisor ID" << endl;
            int advisorID;
            cin >> advisorID;

            Student newStudent(newID, newName, newGrade, newMajor, newGPA, advisorID);
            studentDb.insert(newStudent);
            }
            break;

            case 6: {//delete via id
            int queryID;
            cout << "Enter desired student ID" << endl;
            cin >> queryID;

            Student student = studentDb.findByID(queryID);
            studentDb.remove(student);
            break;
            }

            case 7:{
            cout << "Enter ID" << endl;
            int newID;
            cin >> newID;

            cout << "Enter name" << endl;
            string newName;
            cin >> newName;

            cout << "Enter title" << endl;
            string newTitle;
            cin >> newTitle;

            cout << "Enter Department" << endl;
            string newDepartment;
            cin >> newDepartment;

            
            Faculty newFaculty(newID, newName, newTitle, newDepartment);
            facultyDb.insert(newFaculty);
            break;
            }
            case 8:{//delete via id
            int queryID;
            cout << "Enter desired faculty ID" << endl;
            cin >> queryID;

            Faculty faculty = facultyDb.findByID(queryID);
            facultyDb.remove(faculty);
            break;
            }

            case 9:{
                cout << "Enter student ID: ";
                int studentID;
                cin >> studentID;

                cout << "Enter new faculty advisor ID: ";
                int facultyID;
                cin >> facultyID;

                Student student = studentDb.findByID(studentID);
                

                Faculty faculty = facultyDb.findByID(facultyID);
                

                student.setAdvisorID(facultyID);
                cout << "Advisor for student ID " << studentID << " has been changed to faculty ID " << facultyID << "." << endl;
                break;
            }

            break;

            case 10:{
                cout << "Enter faculty ID: ";
                int facultyID;
                cin >> facultyID;

                cout << "Enter advisee (student) ID to remove: ";
                int adviseeID;
                cin >> adviseeID;

                Faculty faculty = facultyDb.findByID(facultyID);
                

                if (faculty.removeAdvisee(adviseeID)) {
                    cout << "Advisee ID " << adviseeID << " removed from faculty member ID " << facultyID << "." << endl;
                } else {
                    cout << "Advisee ID " << adviseeID << " not found for faculty member ID " << facultyID << "." << endl;
                }
                break;
                }

            case 11:{
                ofstream outFile("runLog.txt");

                // Backup and then redirect
                streambuf* coutBuf = cout.rdbuf();
                cout.rdbuf(outFile.rdbuf());

                // Your cout statements will now go to the file
                studentDb.printTreeInOrder();
                facultyDb.printTreeInOrder();

                // Restore cout's original streambuf
                cout.rdbuf(coutBuf);

                // Optional: Explicitly close the file
                outFile.close();
                cout << "Data saved to runLog.txt." << endl;
                break;
            }
        }

        if(choice == 11){
            break;
        }
    }
    return 0;
}

