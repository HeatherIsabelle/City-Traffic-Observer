#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <climits>
#include <regex>
#include <sstream> // for std::stringstream
#include <unordered_map>
#include <memory>     // For smart pointers
#include <functional> // For std::function
#include <limits>

#define DEBUG // Comment this out to disable debug output
#define PASS 20098
using namespace std;

int choice = 0, dd = 0, mm = 0, yy = 0, hr = 0, mint = 0, sound = 0;

void date_time();
void gotoxy(int x, int y);

class onlyDisplay
{
public:
    void authentication();
    void load();
    void menu();
};

class features
{
public:
    void displayTownships(const vector<string> &townships);
    void displayStreets(const vector<string> &streets);
    void showTrafficInformation(const string &selectedStreet, const string &timePeriod);
    void setTrafficLight(const string &township, const string &street, const string &trafficLightStatus);
    string getCurrentTimePeriod();
    void viewTrafficConditions();
    void viewTrafficJams();
    void add_vehicle_record();
    void view_vehicle_records();
    void update_registration_info();
    void view_registered_vehicles();
    void delete_registration_record();
    void view_daily_vehicle_records();
    void registration_portal();
    void registered_vehicles();
    void record_veh();
    void control();
    void helpline();
    void booths();
    void manageTrafficLights();
    void trafficInformation();
    bool isValidDateFormat(const string &date);
};

// Function to validate the Myanmar car license number format
bool validateLicenseNumber(const string &license)
{
    // Define a regex pattern for Myanmar license plates
    const regex pattern(R"((\d{1,2}/\d{4} [A-Z]{2} \d{2}|\d{1,2}/\d{4} [A-Z]{2} \d{4}))");

    return regex_match(license, pattern);
}
// Function to handle vehicle registration
void features::registration_portal()
{
    system("cls");
    string filePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\registration_information.txt";

    char continueChoice;
    do
    {
        ofstream file;
        file.open(filePath, ios::app);

        if (!file)
        {
            cout << "Error in creating file!";
            return;
        }

        string veh_no, owner_name, veh_type, fuel_type, address;
        gotoxy(65, 5);
        cout << "Vehicle Registration Portal\n";
        gotoxy(65, 6);
        cout << "-----------------------------\n";

        // Input vehicle number with validation
        while (true)
        {
            cout << "Enter Vehicle Number (Format: 1/2345 AA 12 or 1/2345 AA 1234): ";
            cin.ignore();
            getline(cin, veh_no); // Use getline to handle spaces in input

            // Check if input is valid
            if (validateLicenseNumber(veh_no))
            {
                cout << "Valid format: " << veh_no << endl;
                break; // Exit the loop if the format is valid
            }
            else
            {
                cout << "Invalid format! Please enter a valid license number.\n";
            }
        }
        // Get other vehicle details

        cout << "Enter Owner Name: ";
        // cin.ignore(); // Ignore leftover newline
        getline(cin, owner_name);
        // Debugging output to verify the input
        cout << "DEBUG: Owner Name Entered: " << owner_name << endl;

        // Display or process the owner_name as needed
        cout << "Owner Name: " << owner_name << endl;
        cout << "Enter Vehicle Type (e.g., Car, Truck): ";
        getline(cin, veh_type);
        cout << "Enter Fuel Type (e.g., Petrol, Diesel): ";
        getline(cin, fuel_type);
        cout << "Enter Address: ";
        getline(cin, address);

        // Write details to file
        file << veh_no << "\t" << owner_name << "\t" << veh_type << "\t" << fuel_type << "\t" << address << "\n";
        file.close();

        cout << "\nVehicle registered successfully!";
        cout << "\nEnter 'n' to register another vehicle or 'b' to go back to the main session: ";
        cin >> continueChoice;

        while (continueChoice != 'n' && continueChoice != 'b')
        {
            cout << "Invalid choice. Please enter 'n' to add another vehicle or 'b' to go back: ";
            cin >> continueChoice;
        }

        if (continueChoice == 'b')
        {
            // Call to function that returns to the previous session
            system("cls");
            record_veh();
        }

    } while (continueChoice == 'n');
}
// Function to display registered vehicles
void features::view_registered_vehicles()
{
    system("cls");

    string filePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\registration_information.txt";

    ifstream file(filePath);

    if (!file)
    {
        cout << "Error opening file! No registered vehicles found.\n";
        return;
    }

    vector<string> records;
    string line;

    // Read all lines from the file
    while (getline(file, line))
    {
        records.push_back(line);
    }
    file.close();

    // Sort records based on vehicle number (assuming the vehicle number is the first field)
    sort(records.begin(), records.end(), [](const string &a, const string &b)
         {
        size_t pos1 = a.find('\t');
        size_t pos2 = b.find('\t');
        return a.substr(0, pos1) < b.substr(0, pos2); });

    // Display headers
    gotoxy(65, 5);
    cout << "\xB2\xB2\xB2 Registered Vehicles Overview \xB2\xB2\xB2\n";
    gotoxy(65, 6);
    cout << "\xB2\xB2\xB2***************************** \xB2\xB2\xB2\n";

    cout << left << setw(26) << "Vehicle's Plate"
         << setw(25) << "Owner Name"
         << setw(20) << "Vehicle Type"
         << setw(20) << "Fuel Type"
         << "Address\n";

    cout << "----------------------------------------------------------------------------------------------------\n";

    // Display each record
    for (const string &record : records)
    {
        size_t pos1 = record.find('\t');
        size_t pos2 = record.find('\t', pos1 + 1);
        size_t pos3 = record.find('\t', pos2 + 1);
        size_t pos4 = record.find('\t', pos3 + 1);

        string veh_no = record.substr(0, pos1);
        string owner_name = record.substr(pos1 + 1, pos2 - pos1 - 1);
        string veh_type = record.substr(pos2 + 1, pos3 - pos2 - 1);
        string fuel_type = record.substr(pos3 + 1, pos4 - pos3 - 1);
        string address = record.substr(pos4 + 1);

        cout << left << setw(26) << veh_no
             << setw(30) << owner_name
             << setw(17) << veh_type
             << setw(17) << fuel_type
             << address << "\n";
    }

    cout << "\nPress any key to return to the Vehicle Management menu...";
    getch();
    record_veh(); // Return to Vehicle Management menu
}
void features::update_registration_info()
{
    system("cls");
    gotoxy(65, 5);
    cout << "Update Registration Information\n";
    gotoxy(65, 6);
    cout << "--------------------------------\n";

    // File paths for debugging
    string filePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\registration_information.txt";
    string tempFilePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\UpdatedRegistrationInfo.txt";
    string veh_no;
    cout << "Enter Vehicle Number to Update: ";
    cin >> veh_no;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

    ifstream file(filePath);
    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    ofstream tempFile(tempFilePath);
    if (!tempFile)
    {
        cout << "Error creating temporary file!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        // Debugging: Print the line read from the file
        cout << "DEBUG: Line from file: " << line << endl;

        // Check if the line contains the vehicle number
        if (line.find(veh_no) != string::npos)
        {
            found = true;

            // Parse current details for the vehicle
            stringstream ss(line);
            string currentPlate, ownerName, vehicleType, fuelType, address;

            getline(ss, currentPlate, '\t'); // Vehicle number
            getline(ss, ownerName, '\t');    // Owner name
            getline(ss, vehicleType, '\t');  // Vehicle type
            getline(ss, fuelType, '\t');     // Fuel type
            getline(ss, address);            // Address

            // Display current details
            cout << "\nCurrent Details:\n";
            cout << "1. Vehicle Number: " << currentPlate << endl;
            cout << "2. Owner Name: " << ownerName << endl;
            cout << "3. Vehicle Type: " << vehicleType << endl;
            cout << "4. Fuel Type: " << fuelType << endl;
            cout << "5. Address: " << address << endl;

            // Ask user to update each field
            string newPlate, newOwnerName, newVehicleType, newFuelType, newAddress;
            char choice;

            cout << "\nDo you want to update Vehicle Number? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Enter new Vehicle Number: ";
                getline(cin, newPlate);
            }
            else
            {
                newPlate = currentPlate;
            }

            cout << "Do you want to update Owner Name? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Enter new Owner Name: ";
                getline(cin, newOwnerName);
            }
            else
            {
                newOwnerName = ownerName;
            }

            cout << "Do you want to update Vehicle Type? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Enter new Vehicle Type: ";
                getline(cin, newVehicleType);
            }
            else
            {
                newVehicleType = vehicleType;
            }

            cout << "Do you want to update Fuel Type? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Enter new Fuel Type: ";
                getline(cin, newFuelType);
            }
            else
            {
                newFuelType = fuelType;
            }

            cout << "Do you want to update Address? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Enter new Address: ";
                getline(cin, newAddress);
            }
            else
            {
                newAddress = address;
            }

            // Write updated information to the temporary file
            tempFile << newPlate << "\t" << newOwnerName << "\t" << newVehicleType << "\t" << newFuelType << "\t" << newAddress << "\n";
        }
        else
        {
            tempFile << line << "\n"; // Write existing data
        }
    }
    file.close();
    tempFile.close();

    // Ensure the file operations are successful
    if (remove(filePath.c_str()) != 0)
    {
        cout << "Error deleting original file!" << endl;
        return;
    }
    if (rename(tempFilePath.c_str(), filePath.c_str()) != 0)
    {
        cout << "Error renaming temporary file!" << endl;
        return;
    }

    if (found)
    {
        cout << "\nRegistration information updated successfully!\n";
    }
    else
    {
        cout << "\nVehicle number not found.\n";
    }

    cout << "\nPress any key to go back...";
    getch();
    record_veh(); // Return to Vehicle Management menu
}

// Function to add a vehicle record
void features::add_vehicle_record()
{
    system("cls");

    string regFilePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\registration_information.txt";
    string dailyRecordFilePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\DailyVehicleRecord.txt";

    string veh_no, owner_name, vehicleType;
    int speed;
    double vehicleTonnage, tollFee = 0.0;
    const int SPEED_LIMIT = 60; // Example speed limit
    int fineAmount = 0;
    bool isEmergencyVehicle = false;

    // Get current date and time
    time_t now = time(0);
    tm *localTime = localtime(&now);
    char date[11], timeStr[6];

    // Format date as "dd-mm-yyyy"
    strftime(date, sizeof(date), "%d-%m-%Y", localTime);
    // Format time as "hh:mm"
    strftime(timeStr, sizeof(timeStr), "%H:%M", localTime);
    gotoxy(65, 5);
    cout << "Add Vehicle Record\n";
    gotoxy(65, 6);
    cout << "-------------------\n";

    cout << "Enter Vehicle Number (Format: 1/2345 AA 12 or 1/2345 AA 1234): ";
    cin >> veh_no;

    bool isRegistered = false;
    ifstream regFile(regFilePath);
    string line;
    while (getline(regFile, line))
    {
        if (line.find(veh_no) != string::npos)
        {
            isRegistered = true;
            break;
        }
    }
    regFile.close();

    if (!isRegistered)
    {
        cout << "Unregistered vehicle detected! Notifying the associated office...\n";
        cout << "1. Try Again\n";
        cout << "2. Go Back to Previous Menu\n";
        cout << "Select an option: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            add_vehicle_record();
        }
        else
        {
            return; // Exiting the function instead of calling another function (adjust according to your needs)
        }
    }

    cin.ignore(); // Ignore leftover newline character from previous input

    cout << "Enter Owner Name: ";
    getline(cin, owner_name);

    cout << "Enter Vehicle Type (e.g., car, truck, ambulance, firetruck, policecar): ";
    getline(cin, vehicleType);

    cout << "Enter Vehicle Tonnage: ";
    cin >> vehicleTonnage;

    cout << "Enter Measured Speed (manually input by operator): ";
    cin >> speed;

    // Determine if the vehicle is an emergency vehicle
    if (vehicleType == "ambulance" || vehicleType == "firetruck" || vehicleType == "policecar")
    {
        isEmergencyVehicle = true;
    }

    // Calculate toll fee
    if (!isEmergencyVehicle)
    {
        if (vehicleTonnage <= 1.5)
        {
            tollFee = 2.0; // Example toll fee for light vehicles
        }
        else if (vehicleTonnage > 1.5 && vehicleTonnage <= 5.0)
        {
            tollFee = 5.0; // Example toll fee for medium vehicles
        }
        else
        {
            tollFee = 10.0; // Example toll fee for heavy vehicles
        }
    }
    else
    {
        tollFee = 0.0; // Emergency vehicles are exempt from toll fees
    }

    // Check for overspeeding and calculate fine
    if (speed > SPEED_LIMIT)
    {
        fineAmount = (speed - SPEED_LIMIT) * 10; // Example fine calculation: $10 per km over limit
        cout << "Overspeed detected! Fine amount: $" << fineAmount << "\n";
    }
    else
    {
        cout << "Speed within the limit.\n";
    }

    // Save vehicle record to file in the correct order
    ofstream dailyRecordFile;
    dailyRecordFile.open(dailyRecordFilePath, ios::app);
    dailyRecordFile << veh_no << "\t" << owner_name << "\t" << date << "\t" << timeStr << "\t" << speed << " km/h\t$" << tollFee << "\t$" << fineAmount << "\n";
    dailyRecordFile.close();

    cout << "\nVehicle record added successfully!";
    cout << "\nToll Fee: $" << tollFee << "\n";
    cout << "Press any key to go back...";
    getch();
    record_veh();
}

bool isValidTimeFormat(const string &timeStr)
{
    // Check if the time string is in the correct format (HH:MM)
    return timeStr.length() == 5 && timeStr[2] == ':';
}

string formatTimeWithAMPM(const string &timeStr)
{
    // Convert the time string to a `tm` structure
    struct tm timeinfo = {};
    istringstream iss(timeStr);
    char colon;
    int hour, minute;

    // Read time components
    if (!(iss >> hour >> colon >> minute) || colon != ':' || hour < 0 || hour > 23 || minute < 0 || minute > 59)
    {
        return timeStr; // Invalid time format, return original string
    }

    // Convert 24-hour format to 12-hour format with AM/PM
    stringstream formattedTime;
    if (hour >= 12)
    {
        formattedTime << ((hour == 12) ? hour : (hour - 12)) << ':' << setfill('0') << setw(2) << minute << " PM";
    }
    else
    {
        formattedTime << ((hour == 0) ? 12 : hour) << ':' << setfill('0') << setw(2) << minute << " AM";
    }

    return formattedTime.str();
}

// Helper function to validate flexible date formats
bool features::isValidDateFormat(const string &date)
{
    regex datePattern(R"(\b(\d{1,2})[./-](\d{1,2})[./-](\d{4})\b)");
    return regex_match(date, datePattern);
}

void features::view_daily_vehicle_records()
{
    system("cls");

    string dailyRecordFilePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\DailyVehicleRecord.txt";
    gotoxy(65, 5);
    cout << "View Daily Vehicle Records\n";
    cout << "--------------------------\n";

    string inputDate;
    while (true)
    { // Loop to repeatedly prompt the user until a valid date is entered

        cout << "Enter Date to View (Format: dd-mm-yyyy, dd.mm.yyyy, or dd/mm/yyyy): ";
        cin >> inputDate;

        if (!isValidDateFormat(inputDate))
        {
            cout << "Invalid date format. Please enter a valid date.\n";
        }
        else
        {

            break; // Exit the loop when a valid date format is entered
        }
    }

    ifstream dailyRecordFile(dailyRecordFilePath);
    if (!dailyRecordFile)
    {
        cout << "Error opening file!\n";
        cout << "Press any key to return to the previous menu...";
        getch();
        return;
    }

    string line;
    bool found = false;

    cout << " Daily Vehicle Records Overview for " << inputDate << " \n";
    cout << "Vehicle Number             Owner Name                    Date           Time        Speed      Toll Amount  Fine Amount\n";
    cout << "-----------------------------------------------------------------------------------------------------------------\n";

    while (getline(dailyRecordFile, line))
    {
        size_t pos1 = line.find('\t');
        size_t pos2 = line.find('\t', pos1 + 1);
        size_t pos3 = line.find('\t', pos2 + 1);
        size_t pos4 = line.find('\t', pos3 + 1);
        size_t pos5 = line.find('\t', pos4 + 1);
        size_t pos6 = line.find('\t', pos5 + 1);

        if (pos6 == string::npos)
            continue; // Skip lines that don't have enough fields

        string veh_no = line.substr(0, pos1);
        string owner_name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string timeStr = line.substr(pos3 + 1, pos4 - pos3 - 1);
        string speed = line.substr(pos4 + 1, pos5 - pos4 - 1);
        string tollFee = line.substr(pos5 + 1, pos6 - pos5 - 1);
        string fineAmount = line.substr(pos6 + 1);

        if (date == inputDate)
        {
            found = true;
            cout << std::left << std::setw(26) << veh_no
                 << std::setw(30) << owner_name
                 << std::setw(15) << date
                 << std::setw(14) << formatTimeWithAMPM(timeStr)
                 << std::setw(14) << speed
                 << std::setw(13) << tollFee
                 << fineAmount << "\n";
        }
    }

    if (!found)
    {
        cout << "No records found for the date: " << inputDate << "\n";
    }

    cout << "\nPress any key to return to the previous menu...";
    getch();
    record_veh(); // Return to the previous menu
}

// Function to delete a registration record
void features::delete_registration_record()
{
    system("cls");
    gotoxy(65, 5);
    cout << "Delete Registration Record\n";
    gotoxy(65, 6);
    cout << "---------------------------\n";

    string filePath = "C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\registration_information.txt";
    string veh_no;

    gotoxy(55, 8);
    cout << "Enter Vehicle Number to Delete: ";
    cin >> veh_no;

    ifstream file(filePath);
    ofstream tempFile("C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\TempFile.txt");
    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line.find(veh_no) != string::npos)
        {
            found = true;
            continue; // Skip the line to be deleted
        }
        else
        {
            tempFile << line << "\n";
        }
    }
    file.close();
    tempFile.close();

    // Replace original file with the updated one
    remove(filePath.c_str());
    rename("C:\\Users\\Chan Myae May\\Downloads\\Smart-Traffic-Management-main\\Smart-Traffic-Management-main\\TempFile.txt", filePath.c_str());

    if (found)
    {
        gotoxy(65, 10);
        cout << "Record deleted successfully.\n";
    }
    else
    {
        gotoxy(65, 10);
        cout << "Vehicle number not found.\n";
    }
    gotoxy(65, 12);
    cout << "\nPress any key to go back...";
    getch();
    record_veh();
}

void features::record_veh()
{

    system("cls");
    gotoxy(65, 5);
    cout << "\xB2\xB2\xB2\xB2  Vehicle Record Management  \xB2\xB2\xB2\xB2\n";
    gotoxy(65, 6);
    cout << "\xB2\xB2\xB2\xB2  *************************  \xB2\xB2\xB2\xB2\n";
    gotoxy(55, 8);
    cout << "\xB2 1. Registration Portal\n";
    gotoxy(55, 10);
    cout << "\xB2 2. View Registered Vehicles\n";
    gotoxy(55, 12);
    cout << "\xB2 3. Update Registration Info\n";
    gotoxy(55, 14);
    cout << "4. Delete Registration Record\n";
    gotoxy(55, 16);
    cout << "5. Add Vehicle Record\n";
    gotoxy(55, 18);
    cout << "6. History of Vehicle Passing Through\n";
    gotoxy(55, 20);
    cout << "7. Back\n";
    gotoxy(55, 22);
    cout << "Enter your choice: ";
    gotoxy(55, 24);
    cin >> choice;

    switch (choice)
    {
    case 1:
        registration_portal();
        break;
    case 2:
        view_registered_vehicles();
        break;
    case 3:
        update_registration_info();
        break;
    case 4:
        delete_registration_record();
        break;
    case 5:
        add_vehicle_record();
        break;
    case 6:
        view_daily_vehicle_records();
        break;
    case 7:
        return;
    default:
        cout << "\nInvalid Option, try again!";
        getch();
        record_veh();
        break;
    }
}

void features::viewTrafficConditions()
{
    system("cls");

    vector<string> townships = {
        "Hlaing", "Sanchaung", "Downtown", "Insein", "Shwepyithar", "Thingangyun", "North Okkalapa",
        "South Okkalapa", "Mayangone", "Kyeemyindaing", "Dagon", "Bahan", "Ahlone", "Kyauktada",
        "Yangon North", "Yangon South", "Yankin", "Kalay", "Bago", "Yangon West", "Yangon East"};

    vector<vector<string>> streets = {
        {"Parami Street", "Insein Road", "University Avenue", "Kabar Aye Pagoda Road"},
        {"Bo Gyoke Road", "Kyeemyindaing Road", "Hledan Road", "Shwegondine Road"},
        {"Bogyoke Aung San Road", "Anawrahta Road", "Merchant Road", "Pansodan Street"},
        {"Insein Road", "Pyay Road", "Kandawgyi Lake Road", "Aung Mingalar Road"},
        {"Nyaungbintha Road", "Kyeemyindaing Road", "Mingalar Taung Nyunt Road", "Thanlyin Road"},
        {"Hledan Road", "North Okkalapa Road", "Sanchaung Road", "Shwepyithar Road"},
        {"Insein Road", "Pyay Road", "Aung Mingalar Road", "Kandawgyi Lake Road"},
        {"Yankin Road", "Mayangone Road", "Tharketa Road", "Shwepyithar Road"},
        {"Aung Mingalar Road", "Thamine Road", "U Chit Maung Road", "Nyaungpintha Road"},
        {"Bahan Road", "Kyauktada Road", "Ahlone Road", "Dagon Road"},
        {"Kyeemyindaing Road", "Kyimyindaing Road", "Kandawgyi Lake Road", "Yankin Road"},
        {"Anawrahta Road", "Merchant Road", "Pansodan Street", "Bogyoke Aung San Road"},
        {"Hledan Road", "Sanchaung Road", "Shwegondine Road", "Thamine Road"},
        {"Insein Road", "Mayangone Road", "Thanlyin Road", "Kyeemyindaing Road"},
        {"Aung Mingalar Road", "Kandawgyi Lake Road", "Pyay Road", "Insein Road"},
        {"Bago Road", "Mingalar Taung Nyunt Road", "Kyeemyindaing Road", "Sanchaung Road"},
        {"North Okkalapa Road", "Yankin Road", "Insein Road", "Shwepyithar Road"},
        {"Kandawgyi Lake Road", "Shwepyithar Road", "Insein Road", "Mayangone Road"},
        {"Yankin Road", "Dagon Road", "Bahan Road", "Kyauktada Road"}};

    int townshipChoice, streetChoice;

    while (true)
    {
        displayTownships(townships);
        cout << "*********************************\n";
        cout << "*********************************\n";
        cout << "Enter the number of the township: ";
        cin >> townshipChoice;

        if (townshipChoice < 1 || townshipChoice > townships.size())
        {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        vector<string> selectedStreets = streets[townshipChoice - 1];
        displayStreets(selectedStreets);
        cout << "*********************************\n";
        cout << "*********************************\n";
        cout << "Enter the number of the street: ";
        cin >> streetChoice;

        if (streetChoice < 1 || streetChoice > selectedStreets.size())
        {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        string selectedStreet = selectedStreets[streetChoice - 1];
        string timePeriod = getCurrentTimePeriod();
        showTrafficInformation(selectedStreet, timePeriod);

        cout << "Press any key to go back...";
        getch();   // Use cin.get() if getch() is problematic
        control(); // Call to next function or menu
        break;     // Exit the loop after processing
    }
}

void features::manageTrafficLights()
{
    system("cls");

    vector<string> townships = {
        "Hlaing", "Sanchaung", "Downtown", "Insein", "Shwepyithar", "Thingangyun", "North Okkalapa",
        "South Okkalapa", "Mayangone", "Kyeemyindaing", "Dagon", "Bahan", "Ahlone", "Kyauktada",
        "Yangon North", "Yangon South", "Yankin", "Kalay", "Bago", "Yangon West", "Yangon East"};

    vector<string> streets = {
        "Parami Street", "Insein Road", "University Avenue", "Kabar Aye Pagoda Road", "Bo Gyoke Road", "Kyeemyindaing Road",
        "Hledan Road", "Shwegondine Road", "Bogyoke Aung San Road", "Anawrahta Road", "Merchant Road", "Pansodan Street",
        "Nyaungbintha Road", "Mingalar Taung Nyunt Road", "Thanlyin Road", "Sanchaung Road", "Shwepyithar Road",
        "Mayangone Road", "Tharketa Road", "U Chit Maung Road", "Dagon Road", "Kyauktada Road"};

    int townshipChoice, streetChoice;
    string lightStatus;

    while (true)
    {
        displayTownships(townships);
        cout << "*********************************\n";
        cout << "*********************************\n";
        cout << "Enter the number of the township: ";
        cin >> townshipChoice;

        if (townshipChoice < 1 || townshipChoice > townships.size())
        {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        vector<string> selectedStreets = streets; // Assuming all streets are valid in each township
        displayStreets(selectedStreets);
        cout << "*********************************\n";
        cout << "*********************************\n";
        cout << "Enter the number of the street: ";
        cin >> streetChoice;

        if (streetChoice < 1 || streetChoice > selectedStreets.size())
        {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        string selectedStreet = selectedStreets[streetChoice - 1];
        cout << "Enter the traffic light status (Green/Red): ";
        cin >> lightStatus;

        if (lightStatus != "Green" && lightStatus != "Red")
        {
            cout << "Invalid status. Please try again.\n";
            continue;
        }

        setTrafficLight(townships[townshipChoice - 1], selectedStreet, lightStatus);

        cout << "Traffic lights have been adjusted.\n";
        cout << "Press any key to return to the menu...";
        getch();   // Use cin.get() if getch() is problematic
        control(); // Call to next function or menu
        break;     // Exit the loop after processing
    }
}

void features::displayTownships(const vector<string> &townships)
{
    cout << "Select a Township:\n";
    for (int i = 0; i < townships.size(); i++)
    {
        cout << i + 1 << ". " << townships[i] << endl;
    }
}

void features::displayStreets(const vector<string> &streets)
{
    cout << "Select a Street:\n";
    for (int i = 0; i < streets.size(); i++)
    {
        cout << i + 1 << ". " << streets[i] << endl;
    }
}

void features::showTrafficInformation(const string &selectedStreet, const string &timePeriod)
{
    system("cls");
    cout << "Traffic Information for " << selectedStreet << " (" << timePeriod << "):\n";
    // Example traffic conditions based on time of day
    if (timePeriod == "Morning")
    {
        cout << "Status: Heavy Traffic\n";
        cout << "Recommendation: Avoid this street during peak hours.\n";
    }
    else if (timePeriod == "Afternoon")
    {
        cout << "Status: Moderate Traffic\n";
        cout << "Recommendation: Use alternative routes if possible.\n";
    }
    else if (timePeriod == "Evening")
    {
        cout << "Status: Heavy Traffic\n";
        cout << "Recommendation: Expect delays and plan accordingly.\n";
    }
    else
    {
        cout << "Status: Light Traffic\n";
        cout << "Recommendation: Safe to travel.\n";
    }
}

void features::viewTrafficJams()
{
    system("cls");
    cout << "Current Traffic Jams:" << endl;
    cout << "----------------------" << endl;

    string timePeriod = getCurrentTimePeriod();

    // Traffic jam conditions based on the time of day
    if (timePeriod == "Morning")
    {
        cout << "1. Intersection of Anawrahta Road & Shwedagon Pagoda Road: Severe" << endl;
        cout << "2. Roundabout near Mingaladon Airport: Heavy" << endl;
        cout << "3. Intersection of Pyay Road & Sanchaung Road: Moderate" << endl;
        cout << "4. Junction of Kabar Aye Pagoda Road & University Avenue: Severe" << endl;
        cout << "5. Intersection of Insein Road & Parami Street: Heavy" << endl;
    }
    else if (timePeriod == "Afternoon")
    {
        cout << "1. Intersection of Anawrahta Road & Shwedagon Pagoda Road: Moderate" << endl;
        cout << "2. Roundabout near Mingaladon Airport: Light" << endl;
        cout << "3. Intersection of Pyay Road & Sanchaung Road: Light" << endl;
        cout << "4. Junction of Kabar Aye Pagoda Road & University Avenue: Moderate" << endl;
        cout << "5. Intersection of Insein Road & Parami Street: Light" << endl;
    }
    else if (timePeriod == "Evening")
    {
        cout << "1. Intersection of Anawrahta Road & Shwedagon Pagoda Road: Heavy" << endl;
        cout << "2. Roundabout near Mingaladon Airport: Moderate" << endl;
        cout << "3. Intersection of Pyay Road & Sanchaung Road: Moderate" << endl;
        cout << "4. Junction of Kabar Aye Pagoda Road & University Avenue: Heavy" << endl;
        cout << "5. Intersection of Insein Road & Parami Street: Moderate" << endl;
    }
    else
    {
        cout << "1. Intersection of Anawrahta Road & Shwedagon Pagoda Road: Light" << endl;
        cout << "2. Roundabout near Mingaladon Airport: Light" << endl;
        cout << "3. Intersection of Pyay Road & Sanchaung Road: Light" << endl;
        cout << "4. Junction of Kabar Aye Pagoda Road & University Avenue: Light" << endl;
        cout << "5. Intersection of Insein Road & Parami Street: Light" << endl;
    }

    cout << endl;
    cout << "Press any key to return to go back...";
    getch();
    control();
}

void features::setTrafficLight(const string &township, const string &street, const string &trafficLightStatus)
{
    cout << "Setting traffic light at " << street << ", " << township << " to " << trafficLightStatus << ".\n";
    // Implement the logic to set the traffic light status
}

// function to get the current time period
string features::getCurrentTimePeriod()
{
    time_t now = time(0);
    tm *localtm = localtime(&now);
    int hour = localtm->tm_hour;

    if (hour >= 6 && hour < 10)
    {
        return "Morning"; // 6 AM to 10 AM
    }
    else if (hour >= 10 && hour < 15)
    {
        return "Afternoon"; // 10 AM to 3 PM
    }
    else if (hour >= 15 && hour < 19)
    {
        return "Evening"; // 3 PM to 7 PM
    }
    else
    {
        return "Night"; // 7 PM to 6 AM
    }
}

void features::helpline()
{
    system("cls");
    cout << "Emergency Helpline Numbers" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Police: 100" << endl;
    cout << "2. Ambulance: 108" << endl;
    cout << "3. Fire: 101" << endl;
    cout << endl;
    cout << "Press any key to return to the menu...";
    getch();
    control();
}

void features::control()
{
    system("cls");
    onlyDisplay d;
    gotoxy(65, 5);
    cout << "\xB2\xB2\xB2\xB2  Traffic Management  \xB2\xB2\xB2\xB2";
    gotoxy(65, 6);
    cout << "\xB2\xB2\xB2\xB2  ------------------  \xB2\xB2\xB2\xB2";
    gotoxy(55, 10);
    cout << "\xB2  1. View Traffic Conditions";
    gotoxy(55, 12);
    cout << "\xB2  2. Manage Traffic Lights";
    gotoxy(55, 14);
    cout << "\xB2  3. View Traffic Jams";
    gotoxy(55, 16);
    cout << "\xB2  4. Helpline";
    gotoxy(55, 18);
    cout << "\xB2  5. Exit\n";
    gotoxy(55, 20);
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        viewTrafficConditions(); // New feature
        break;
    case 2:
        manageTrafficLights(); // New feature
        break;
    case 3:
        viewTrafficJams(); // New feature
        break;
    case 4:
        helpline();
        break;
    case 5:
        d.menu();
        break;
    default:
        cout << "\n\tInvalid Option, try again!";
        getch();
        control();
        break;
    }
}

void onlyDisplay::authentication()
{
    system("cls");
    int i = 0, pass = 0;
    char c;
    gotoxy(65, 8);
    cout << "\xB2\xB2\xB2  City's Traffic and Vehicle Info Observer  \xB2\xB2\xB2";
    gotoxy(65, 10);
    cout << "\xB2\xB2\xB2  Authorized Login Only  \xB2\xB2\xB2";
    gotoxy(55, 14);
    cout << "\nEnter the Password : ";
    do
    {
        c = _getch();
        if (c >= '0' && c <= '9')
        {
            cout << "*";
            pass = pass * 10 + c - 48;
            i++;
        }
        if (c == 13)
            break;
    } while (i < 10);
    if (pass == PASS)
    {
        gotoxy(58, 17);
        cout << "\n\nPassword Matched!";
        gotoxy(58, 19);
        cout << "\n\nPress any key to proceed...";
        _getch();
        load();
    }
    else
    {
        cout << "\n\nWrong password, try again.";
        _getch();
        authentication();
    }
}

void onlyDisplay::load()
{
    system("cls");
    gotoxy(65, 10);
    cout << "Loading...\n\n";
    gotoxy(50, 13);
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 12000000; j++)
            ;
        cout << "\xDB";
    }
    menu();
}

void onlyDisplay::menu()
{
    system("cls");
    features f;
    gotoxy(65, 5);
    cout << "\xB2\xB2\xB2\xB2  MAIN MENU  \xB2\xB2\xB2\xB2";
     gotoxy(65, 6);
    cout << "\xB2\xB2\xB2\xB2  ********** \xB2\xB2\xB2\xB2";
    gotoxy(55, 10);
    cout << "\xB2  1. Vehicle Record Management";
    gotoxy(55, 12);
    cout << "\xB2  2. Traffic Management";
    gotoxy(55, 14);
    cout << "\xB2  3. Exit";
    gotoxy(55, 20);
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        f.record_veh();
        break;
    case 2:
        f.control();
        break;
    case 3:
        exit(0);
        break;
    default:
        cout << "\nInvalid Option, try again!";
        getch();
        menu();
        break;
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void date_time()
{
    time_t t;
    time(&t);
    tm *tPtr = localtime(&t);
    dd = tPtr->tm_mday;
    mm = (tPtr->tm_mon) + 1;
    yy = (tPtr->tm_year) + 1900;
    hr = tPtr->tm_hour;
    mint = tPtr->tm_min;
}

int main()
{
    onlyDisplay d;
    d.authentication();
    d.menu();
    return 0;
}
