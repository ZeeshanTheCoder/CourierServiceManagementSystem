#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

// =============== Structures =============== //

struct User {
    string username;
    string email;
    string password;
    string role; // "user", "admin", "courier"
};

struct Parcel {
    string sender;
    string receiver;
    string address;
    string contact;
    float weight;
    string deliveryType;
    string courierAssigned;
    string status;
    string bookingTime;
    float charges;
};

// =============== Vector =============== //

vector<User> users;
vector<Parcel> parcels;

// =============== Function Declaration =============== //


// -------- File I/O for Users --------
void saveUsersToFile();

void loadUsersFromFile();

// -------- File I/O for Parcels --------
void saveParcelsToFile();

void loadParcelsFromFile();

// -------- User Registration & Login --------
bool isUserExists(const string& username, const string& email, const string& role);

void registerUser(const string& role);

int loginUser(const string& role);

// -------- Parcel Functions --------

// For Users
void bookParcel(const string& senderUsername);

void trackParcel();

void viewMyParcels(const string& username);

void cancelParcel(const string& username);

void exportUserParcelsToCSV(const string& username);

// For Admin
void viewAllParcels();

void updateStatus();

void assignCourier();

void exportToCSV();


void viewAllUsersAndCouriers();

// For Couriers
void viewAssignedParcels(const string& courierName);

void courierUpdateStatus(const string& courierName);

void viewDeliveryHistory(const string& courierName);

void exportCourierParcelsToCSV(const string& courierName);

// -------- Main Program --------
int main() {
    loadUsersFromFile();
    loadParcelsFromFile();

    bool adminExists = false;
    for (const auto& user : users) {
        if (user.username == "admin" && user.password == "admin" && user.role == "admin") {
            adminExists = true;
            break;
        }
    }
    if (!adminExists) {
        users.push_back({ "admin", "admin@system.com", "admin", "admin" });
        saveUsersToFile();
    }

    int mainChoice;
    do {
        cout << "\n=================================\n";
        cout << "Courier Service Management System\n";
        cout << "=================================\n";
        cout << "1. User\n2. Admin\n3. Courier\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        int userIndex = -1;

        switch (mainChoice) {
        case 1: {
            int authChoice;
            cout << "1. Register\n2. Login\nChoose: ";
            cin >> authChoice;
            if (authChoice == 1) registerUser("user");
            else if (authChoice == 2) {
                userIndex = loginUser("user");
                if (userIndex != -1) {
                    int userChoice;
                    do {
                        cout << "\n--- USER MENU ---\n";
                        cout << "1. Book a Parcel\n2. Track Parcel\n3. View My Parcels\n4. Cancel Parcel\n5. Export Parcel Data to CSV\n0. Logout\n";
                        cout << "-------------------------\n";

                        cin >> userChoice;
                        switch (userChoice) {
                        case 1: bookParcel(users[userIndex].username); break;
                        case 2: trackParcel(); break;
                        case 3: viewMyParcels(users[userIndex].username); break;
                        case 4: cancelParcel(users[userIndex].username); break;
                        case 5: exportUserParcelsToCSV(users[userIndex].username); break;
                        case 0: cout << "Logout Successful" << endl; break;
                        default: cout << "Invalid Choice. Try again" << endl;  break;
                        }
                    } while (userChoice != 0);
                }
            }
            break;
        }
        case 2: {
            userIndex = loginUser("admin");
            if (userIndex != -1) {
                int adminChoice;
                do {
                    cout << "\n--- ADMIN MENU ---\n";
                    cout << "1. View All Parcels\n2. Update Parcel Status\n3. Assign Courier\n4. Export to CSV\n5. View Users & Couriers\n0. Logout\n";
                    cout << "-------------------------\n";

                    cin >> adminChoice;
                    switch (adminChoice) {
                    case 1: viewAllParcels(); break;
                    case 2: updateStatus(); break;
                    case 3: assignCourier(); break;
                    case 4: exportToCSV(); break;
                    case 5: viewAllUsersAndCouriers(); break;
                    case 0: cout << "Logout Successful" << endl; break;
                    default: cout << "Invalid Choice. Try again" << endl; break;
                    }
                } while (adminChoice != 0);
            }
            break;
        }
        case 3: {
            int authChoice;
            cout << "1. Register\n2. Login\nChoose: ";
            cin >> authChoice;
            if (authChoice == 1) registerUser("courier");
            else if (authChoice == 2) {
                userIndex = loginUser("courier");
                if (userIndex != -1) {
                    string courierName = users[userIndex].username;
                    int courierChoice;
                    do {
                        cout << "\n--- COURIER MENU ---\n";
                        cout << "1. View Assigned Parcels\n2. Update Parcel Status\n3. View Delivery History\n4. Export Parcel Data to CSV\n0. Logout\n";
                        cout << "-------------------------\n";

                        cin >> courierChoice;
                        switch (courierChoice) {
                        case 1: viewAssignedParcels(courierName); break;
                        case 2: courierUpdateStatus(courierName); break;
                        case 3: viewDeliveryHistory(courierName); break;
                        case 4: exportCourierParcelsToCSV(courierName); break;
                        case 0: cout << "Logout Successful" << endl; break;
                        default: cout << "Invalid Choice. Try again" << endl; break;
                        }
                    } while (courierChoice != 0);
                }
            }
            break;
        }
        case 0:
            cout << "-------------------------\n";

            cout << "Thank you for using the system!\n";
            cout << "-------------------------\n";
            break;
        default:
            cout << "-------------------------\n";
            cout << "Invalid choice. Try again.\n";

            cout << "-------------------------\n";
        }


    } while (mainChoice != 0);

    return 0;
}
 
// =============== Function Definition =============== //

// -------- File I/O for Users --------
void saveUsersToFile() {
    ofstream file("users.txt");
    for (const auto& user : users) {
        file << user.username << "\n"
            << user.email << "\n"
            << user.password << "\n"
            << user.role << "\n";
    }
    file.close();
}

void loadUsersFromFile() {
    ifstream file("users.txt");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        User u;
        u.username = line;
        getline(file, u.email);
        getline(file, u.password);
        getline(file, u.role);
        users.push_back(u);
    }
    file.close();
}

// -------- File I/O for Parcels --------
void saveParcelsToFile() {
    ofstream file("parcels.txt");
    for (const auto& p : parcels) {
        file << p.sender << "\n"
            << p.receiver << "\n"
            << p.address << "\n"
            << p.contact << "\n"
            << p.weight << "\n"
            << p.deliveryType << "\n"
            << p.courierAssigned << "\n"
            << p.status << "\n"
            << p.bookingTime << "\n"
            << p.charges << "\n";
    }
    file.close();
}

void loadParcelsFromFile() {
    ifstream file("parcels.txt");
    if (!file) return;

    Parcel p;
    while (getline(file, p.sender)) {
        getline(file, p.receiver);
        getline(file, p.address);
        getline(file, p.contact);
        file >> p.weight;
        file.ignore();
        getline(file, p.deliveryType);
        getline(file, p.courierAssigned);
        getline(file, p.status);
        getline(file, p.bookingTime);
        file >> p.charges;
        file.ignore(); // consume newline after charges
        parcels.push_back(p);
    }

    file.close();
}


// -------- User Registration & Login --------
bool isUserExists(const string& username, const string& email, const string& role) {
    for (const auto& user : users) {
        if (user.username == username && user.role == role) {
            cout << "Username already registered with this role!\n";
            return true;
        }
        if (user.email == email) {
            cout << "Email already registered!\n";
            return true;
        }
    }
    return false;
}

void registerUser(const string& role) {
    string username, email, password;
    cout << "Enter Username: "; cin >> username;
    cout << "Enter Email: "; cin >> email;
    cout << "Enter Password: "; cin >> password;
    cout << "-------------------------\n";

    if (isUserExists(username, email, role)) return;

    users.push_back({ username, email, password, role });
    saveUsersToFile();
    cout << "Registered successfully as " << role << "!\n";
}

int loginUser(const string& role) {
    string username, password;
    cout << "Enter Username: "; cin >> username;
    cout << "Enter Password: "; cin >> password;
    cout << "-------------------------\n";


    for (int i = 0; i < users.size(); i++) {
        if (users[i].username == username && users[i].password == password && users[i].role == role) {
            cout << "Login successful. Welcome, " << username << "!\n";
            return i;
        }
    }
    cout << "Invalid credentials or role mismatch.\n";
    return -1;
}

// -------- Parcel Functions --------

// For Users
void bookParcel(const string& senderUsername) {
    Parcel p;
    p.sender = senderUsername;
    cout << "Enter Receiver Name: ";
    cin >> p.receiver;
    cout << "Enter Receiver Address: ";
    cin.ignore();
    getline(cin, p.address);
    cout << "Enter Contact Number: ";
    cin >> p.contact;
    cout << "Enter Parcel Weight (kg): ";
    cin >> p.weight;
    cout << "Enter Delivery Type (Normal/Express): ";
    cin >> p.deliveryType;

    while (p.deliveryType != "Normal" && p.deliveryType != "Express") {
        cout << "Invalid choice! Please enter 'Normal' or 'Express': ";
        cin >> p.deliveryType;
    }

    p.courierAssigned = "Unassigned";
    p.status = "Pending";

    float rate = (p.deliveryType == "Express") ? 100.0 : 50.0;
    p.charges = p.weight * rate;


    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);

    stringstream ss;
    ss << put_time(&localtm, "%Y-%m-%d %H:%M:%S");
    p.bookingTime = ss.str();

    parcels.push_back(p);
    cout << "-------------------------\n";

    cout << "Parcel booked successfully!\n";
    cout << "Tracking ID: " << parcels.size() + 1000 << "\n";
    saveParcelsToFile();
    cout << "-------------------------\n";

}

void trackParcel() {
    int id;
    cout << "Enter Tracking ID: ";
    cin >> id;
    int index = id - 1001;
    cout << "-------------------------\n";

    if (index >= 0 && index < parcels.size()) {
        cout << "Tracking ID: " << id << "\n";
        cout << "Receiver: " << parcels[index].receiver << "\n";
        cout << "Status: " << parcels[index].status << "\n";
        cout << "Charges: " << parcels[index].charges << "\n";
        cout << "Booking Time: " << parcels[index].bookingTime << "\n";
        cout << "Courier: " << parcels[index].courierAssigned << "\n";
    }
    else {
        cout << "Invalid Tracking ID!\n";
    }
    cout << "-------------------------\n";
}

void viewMyParcels(const string& username) {
    bool found = false;
    for (int i = 0; i < parcels.size(); i++) {
            cout << "-------------------------\n";
        if (parcels[i].sender == username) {
            cout << "Tracking ID: " << i + 1001 << "\n";
            cout << "Receiver: " << parcels[i].receiver << "\n";
            cout << "Address: " << parcels[i].address << "\n";
            cout << "Contact: " << parcels[i].contact << "\n";
            cout << "Weight: " << parcels[i].weight << " kg\n";
            cout << "Delivery Type: " << parcels[i].deliveryType << "\n";
            cout << "Courier Assigned: " << parcels[i].courierAssigned << "\n";
            cout << "Status: " << parcels[i].status << "\n";
            cout << "Booking Time: " << parcels[i].bookingTime << "\n";
            cout << "Charges: Rs. " << parcels[i].charges << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "-------------------------\n";
        cout << "No parcels booked by you.\n";

    }
    cout << "-------------------------\n";

}

void cancelParcel(const string& username) {
    int id;
    cout << "Enter Tracking ID to cancel: ";
    cin >> id;
    int index = id - 1001;

    if (index >= 0 && index < parcels.size()) {
        if (parcels[index].sender == username) {
            if (parcels[index].status == "Pending") {
                parcels[index].status = "Canceled";
                cout << "-------------------------\n";
                cout << "Parcel canceled successfully.\n";
                saveParcelsToFile();
            }
            else {
                cout << "-------------------------\n";
                cout << "You can only cancel parcels with status 'Pending'.\n";
            }
        }
        else {
            cout << "-------------------------\n";
            cout << "This parcel does not belong to you!\n";
        }
    }
    else {
        cout << "-------------------------\n";
        cout << "Invalid Tracking ID!\n";
    }
    cout << "-------------------------\n";

}

void exportUserParcelsToCSV(const string& username) {
    ofstream file(username + ".csv"); // file banegi username.csv
    file << "Receiver,Address,Contact,Weight,Delivery Type,Courier Assigned,Status,Booking Time,Charges\n";

    bool found = false;
    for (const auto& p : parcels) {
        if (p.sender == username) {
            file << "\"" << p.receiver << "\","
                << "\"" << p.address << "\","
                << p.contact << ","
                << p.weight << ","
                << p.deliveryType << ","
                << p.courierAssigned << ","
                << p.status << ","
                << "\"" << p.bookingTime << "\","
                << p.charges << "\n";
            found = true;
        }
    }


    file.close();

    cout << "-------------------------\n";

    if (found) {
        cout << "Your parcel records exported to '" << username << ".csv' successfully!\n";
    }
    else {
        cout << "No parcels found to export.\n";
    }
    cout << "-------------------------\n";

}

// For Admin

void viewAllParcels() {
    if (parcels.size() != 0) {
        for (int i = 0; i < parcels.size(); i++) {
            cout << "Tracking ID: " << i + 1001 << "\n";
            cout << "Sender: " << parcels[i].sender << "\n";
            cout << "Receiver: " << parcels[i].receiver << "\n";
            cout << "Address: " << parcels[i].address << "\n";
            cout << "Contact: " << parcels[i].contact << "\n";
            cout << "Weight: " << parcels[i].weight << " kg\n";
            cout << "Delivery Type: " << parcels[i].deliveryType << "\n";
            cout << "Status: " << parcels[i].status << "\n";
            cout << "Booking Time: " << parcels[i].bookingTime << "\n";
            cout << "Courier: " << parcels[i].courierAssigned << "\n";
            cout << "Charges: Rs. " << parcels[i].charges << "\n";
            cout << "---------------------------\n";
        }
    }
    else {
        cout << "No Parcel Found" << endl;
    }
}

void updateStatus() {
    int id;
    cout << "Enter Tracking ID to update: ";
    cin >> id;
    int index = id - 1001;

    if (index >= 0 && index < parcels.size()) {
        cout << "Enter New Status (In Transit/Out for Delivery/Delivered): ";
        cin.ignore();
        getline(cin, parcels[index].status);

        while (parcels[index].status != "In Transit" && parcels[index].status != "Delivered" && parcels[index].status != "Out for Delivery") {
            cout << "Invalid choice! Please enter 'In Transit' or 'Out for Delivery' or 'Delivered': ";
            getline(cin, parcels[index].status);
        }

        cout << "-------------------------\n";
        cout << "Status updated successfully!\n";
        saveParcelsToFile();
    }
    else {
        cout << "-------------------------\n";
        cout << "Invalid Tracking ID!\n";
    }

    cout << "-------------------------\n";

}

void assignCourier() {
    int id;
    cout << "Enter Tracking ID: ";
    cin >> id;
    int index = id - 1001;

    if (index >= 0 && index < parcels.size()) {
        cout << "Enter Courier Name to Assign: ";
        string courierName;
        cin >> courierName;

        bool courierFound = false;
        for (const auto& user : users) {
            if (user.username == courierName && user.role == "courier") {
                courierFound = true;
                break;
            }
        }

        if (courierFound) {
            cout << "-------------------------\n";
            parcels[index].courierAssigned = courierName;
            cout << "Courier assigned successfully!\n";
            saveParcelsToFile();
        }
        else {
            cout << "-------------------------\n";
            cout << "Error: No courier found with the username '" << courierName << "'. Assignment failed.\n";
        }

    }
    else {
        cout << "-------------------------\n";
        cout << "Invalid Tracking ID!\n";
    }
    cout << "-------------------------\n";

}

void exportToCSV() {
    ofstream file("parcels.csv");
    file << "Tracking ID,Sender,Receiver,Address,Contact,Weight,Delivery Type,Courier,Status,Booking Time,Charges\n";

    for (int i = 0; i < parcels.size(); ++i) {
        const auto& p = parcels[i];
        int trackingID = i + 1001;

        file << trackingID << ","
            << "\"" << p.sender << "\","
            << "\"" << p.receiver << "\","
            << "\"" << p.address << "\","
            << "\"" << p.contact << "\","
            << p.weight << ","
            << "\"" << p.deliveryType << "\","
            << "\"" << p.courierAssigned << "\","
            << "\"" << p.status << "\","
            << "\"" << p.bookingTime << "\","
            << p.charges << "\n";
    }

    file.close();
    cout << "-------------------------\n";
    cout << "CSV file 'parcels.csv' generated successfully!\n";
    cout << "-------------------------\n";

}


void viewAllUsersAndCouriers() {
    int userCount = 0, courierCount = 0;

    cout << "-------------------------\n";


    cout << "\n--- Registered Users ---\n";
    for (const auto& user : users) {
        if (user.role == "user") {
            cout << "Username: " << user.username << ", Email: " << user.email << "\n";
            userCount++;
        }
    }

    cout << "\n--- Registered Couriers ---\n";
    for (const auto& user : users) {
        if (user.role == "courier") {
            cout << "Username: " << user.username << ", Email: " << user.email << "\n";
            courierCount++;
        }
    }

    cout << "\nTotal Users: " << userCount << "\n";
    cout << "Total Couriers: " << courierCount << "\n\n";

    cout << "-------------------------\n";

}

// For Couriers

void viewAssignedParcels(const string& courierName) {
    bool found = false;
    cout << "-------------------------\n";

    for (int i = 0; i < parcels.size(); i++) {
        if (parcels[i].courierAssigned == courierName) {
            cout << "Tracking ID: " << i + 1001 << "\n";
            cout << "Sender: " << parcels[i].sender << "\n";
            cout << "Receiver: " << parcels[i].receiver << "\n";
            cout << "Status: " << parcels[i].status << "\n";
            cout << "Charges: " << parcels[i].charges << "\n";
            found = true;
            cout << "-------------------------\n";
        }
    }
    if (!found) {
        cout << "No parcels assigned to you.\n\n";
        cout << "-------------------------\n";
    }
}

void courierUpdateStatus(const string& courierName) {
    int id;
    cout << "Enter Tracking ID to update: ";
    cin >> id;
    int index = id - 1001;

    if (index >= 0 && index < parcels.size()) {
        if (parcels[index].courierAssigned == courierName) {
            cout << "Enter New Status (In Transit/Out for Delivery/Delivered): ";
            cin.ignore();
            getline(cin, parcels[index].status);

            while (parcels[index].status != "In Transit" &&
                parcels[index].status != "Out for Delivery" &&
                parcels[index].status != "Delivered") {
                cout << "Invalid status! Please enter one of the following:\n";
                cout << "In Transit / Out for Delivery / Delivered\n";
                getline(cin, parcels[index].status);
            }

            cout << "-------------------------\n";
            cout << "Status updated successfully!\n";
            saveParcelsToFile();
        }
        else {
            cout << "-------------------------\n";
            cout << "Parcel not assigned to you!\n";
        }
    }
    else {
        cout << "-------------------------\n";
        cout << "Invalid Tracking ID!\n";
    }
    cout << "-------------------------\n";

}

void viewDeliveryHistory(const string& courierName) {
    bool found = false;
    cout << "\n--- Delivery History for " << courierName << " ---\n";
    cout << "-------------------------\n";
    for (int i = 0; i < parcels.size(); i++) {
        if (parcels[i].courierAssigned == courierName) {
            cout << "Tracking ID: " << i + 1001 << "\n";
            cout << "Receiver: " << parcels[i].receiver << "\n";
            cout << "Address: " << parcels[i].address << "\n";
            cout << "Status: " << parcels[i].status << "\n";
            cout << "Booking Time: " << parcels[i].bookingTime << "\n";
            cout << "Delivery Type: " << parcels[i].deliveryType << "\n";
            cout << "Charges: " << parcels[i].charges << "\n";
            cout << "-------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No delivery history found.\n";
        cout << "-------------------------\n";
    }

}

void exportCourierParcelsToCSV(const string& courierName) {
    ofstream file(courierName + ".csv");
    file << "Tracking ID,Receiver,Address,Delivery Type,Charges,Status\n";

    bool found = false;
    for (int i = 0; i < parcels.size(); i++) {
        if (parcels[i].courierAssigned == courierName) {
            file << i + 1001 << ","
                << "\"" << parcels[i].receiver << "\","
                << "\"" << parcels[i].address << "\","
                << "\"" << parcels[i].deliveryType << "\","
                << "\"" << parcels[i].charges << "\","
                << "\"" << parcels[i].status << "\"\n";
            found = true;
        }
    }

    file.close();
    cout << "-------------------------\n";

    if (found)
        cout << "CSV file '" << courierName << ".csv' generated successfully!\n";
    else
        cout << "No assigned parcels found. CSV not generated.\n";

    cout << "-------------------------\n";

}