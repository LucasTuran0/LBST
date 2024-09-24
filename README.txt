Lazy Balanced Binary Search Tree (BST) Project
Overview
This project was a summer project to keep my coding skills sharp. This implements a Lazy Balanced Binary Search Tree (BST) in C++ for managing student and faculty records. The tree structure ensures efficient operations such as insertion, deletion, and searching, while maintaining balance to optimize performance. The program allows users to interact with the database via a command-line interface, providing a range of functionalities to add, remove, or modify records for students and faculty members.

Features

Lazy Balanced BST: The tree dynamically rebalances itself to maintain optimal performance, adjusting node depths when necessary.
Student and Faculty Management: Store and manage records with attributes such as ID, name, GPA, major (for students), and department (for faculty).
CRUD Operations:

Add new student or faculty records.
Search for specific records by ID.
Modify student advisor relationships.
Remove records by ID.
In-Order Traversal: Print all student or faculty records in ascending order of their IDs.
File Logging: Save all data to a log file (runLog.txt) for future reference.

How It Works
The Lazy Balanced BST is designed to maintain balance by adjusting node depths after every insert or delete operation. The tree employs efficient search algorithms to quickly locate records by ID, and a rebalancing mechanism to keep operations performant, even with growing datasets. Users can interact with the tree through a simple command-line interface that offers a range of operations for managing student and faculty information.

Key Operations
Insert: Add a new student or faculty member.
Delete: Remove a student or faculty member by their ID.
Search: Find and display information about a student or faculty member by their ID.
Modify: Change a student’s advisor by updating their associated faculty member's ID.
Print: Display all student or faculty records in order of ascending ID.

Compile instructions:
g++ -o test *.cpp
./test
