#include "HouseAvailabilityMenu.hpp"
#include "ownerDetails.hpp"  // Include the header file for List class
#include <iostream>

using namespace std;

HouseAvailabilityMenu::HouseAvailabilityMenu() {}

void HouseAvailabilityMenu::addNewProperty() {
    string address, details, status;
    float deposit, rent;

    // Create an instance of List which is now defined
    List ownerList;
    int ownerID = -1; // Dummy owner ID for example purposes

    cout << "Enter property address: ";
    cin >> address;

    cout << "Enter unit details (e.g., 2bed 2bath): ";
    cin >> details;

    cout << "Enter rent deposit amount: ";
    cin >> deposit;

    cout << "Enter monthly rent amount: ";
    cin >> rent;

    cout << "Enter occupancy status (empty/occupied): ";
    cin >> status;

    int id = propertyManager.AddProperty(ownerList, ownerID, -1, address, details, deposit, rent, status);
    if (id != -1) {
        cout << "Property added successfully! Property ID: " << id << endl;
    } else {
        cout << "Failed to add property. Storage might be full." << endl;
    }
}

// Rest of the code remains unchanged
