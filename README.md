City's Traffic and Vechicle Info Observer
****************************************
Overview
********
The Smart Traffic Management System is a console-based C++ application designed to manage and monitor traffic conditions within the city of Yangon. The system allows authorized users to view traffic conditions, manage traffic lights, view traffic jams, and access emergency helplines.

Features
********
Vehicle Management
******************
Vehicle Registration: Users can register vehicles by providing details such as the vehicle number, owner name, vehicle type, fuel type, and address. The system validates the vehicle number format according to Myanmar's license plate format.

View Registered Vehicles: The system allows users to view a list of all registered vehicles, sorted by vehicle number. The information is presented in a structured format, including the vehicle's plate, owner name, vehicle type, fuel type, and address.

Update Registration Information: Users can update the registration details of any vehicle by entering the vehicle number. The system provides an interface to modify specific fields such as the vehicle number, owner name, vehicle type, fuel type, and address.

Delete Registration Record: Users can remove a vehicle’s registration from the system.
Traffic Condition Monitoring: View real-time traffic information for various streets.


Traffic Light Management
************************
Manage Traffic Lights: The system provides functionality to set the status of traffic lights (e.g., red, green) for specific townships and streets. 


Traffic Monitoring
*******************
View Traffic Conditions: The system displays traffic conditions for different streets and townships. Users can select a specific township and street to get relevant traffic information.

View Traffic Jams: Users can monitor traffic jams within the city, helping in decision-making for traffic management.

Additional Features
*******************
Helpline: An in-built helpline feature allows users to access emergency contact information.

File Structure
***************
main.cpp: Contains the main implementation of the Smart Traffic Management System.
registration_information.txt: Stores registered vehicle information.
UpdatedRegistrationInfo.txt: Temporary file used during the update process for registration information.

Code Overview
*************
Main Classes
************
onlyDisplay: Handles the display of menus and initial user authentication.
authentication(): Secures the system with a password.
load(): Shows a loading animation.
menu(): Displays the main menu.
features: Implements the core functionality of the system, including vehicle management, traffic light control, and traffic monitoring.


gotoxy(int x, int y): Positions the cursor at specific coordinates in the console window.

Dependencies
************
C++ Standard Library: Utilizes standard C++ libraries for I/O operations, string manipulation, file handling, and regular expressions.
Windows API: The system uses the conio.h and windows.h headers for handling console-specific tasks such as cursor positioning and capturing user input.
GCC/G++: Requires a C++ compiler to compile and run the application.

