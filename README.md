# CS-253-OOPS-PROJECT

Car Rental Management System

This system is designed to manage the renting and returning of cars for a car rental company. It provides functionalities for users, employees, and managers to interact with the system according to their roles.

Program Structure:

The program is structured into the following directories and files:

1. main.cpp - Contains the main function and user interface logic.
2. data_files/ - Directory containing CSV files for storing user, car, and rental data.

Assumptions Made:

1. The program assumes the existence of CSV files ("all_people_data.csv", "rented_Cars_data.csv", "all_cars_data.csv") to store user, car, and rental information respectively, in the "data_files/" directory.
2. Each CSV file has specific columns for storing relevant data (e.g., user ID, car details, rental history).
3. The program assumes that the user will provide correct inputs during interactions with the system.
4. Credit score calculation is based on predefined rules and may not accurately represent a real-world credit scoring system.
5. Fine calculation is based on predefined rules related to overdue rentals.
6. The program assumes that the user has necessary permissions to perform certain actions based on their role (e.g., only managers can add or delete users/cars).

Instructions for Running the Software:

1. Ensure that you have a C++ compiler installed on your system.
2. Download all source code files and place them in the same directory.
3. Create a directory named "data_files" in the same directory as the source code files.
4. Place the required CSV files ("all_people_data.csv", "rented_Cars_data.csv", "all_cars_data.csv") inside the "data_files" directory.
5. Compile the program using the C++ compiler.



Car Rental System User Guide

Welcome to the Car Rental System! This guide will help you navigate through the system's functionalities.

1. Logging In:
    - To access the system, you need to log in using your credentials.

2. Main Menu:
    - After successful login, you will be presented with a menu based on your role: Customer, Employee, or Manager.

3. Customer/Employee Menu:
    - If you are logged in as a customeror an employee, you can:
        - See all available cars
        - View cars rented by you
        - Check car availability
        - View your credit score
        - View fines
        - View credit score
        - Rent a car
        - Return a car
        - Logout
        - Exit the system

4. Manager Menu:
    - If you are logged in as a manager, you have access to administrative functionalities such as:
        - See all users
        - See all cars
        - Add/update/delete users
        - Add/update/delete cars
        - View rented cars and their due dates
        - Logout
        - Exit the system

5. Navigation:
    - Use the provided menu options and input corresponding numbers or characters to navigate through the system.

6. Logging Out:
    - Remember to log out when you're done using the system to ensure the security of your account.

7. Exiting the System:
    - You can exit the system at any time by choosing the exit option from the menu.

Thank you for using the Car Rental System!

