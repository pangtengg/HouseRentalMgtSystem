#include <iostream>
#include "tenantDetails.hpp"

using namespace std;
using namespace tenantDetails;

// Constructor
TenantManager::TenantManager() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        occupied[i] = false; // Initialize all slots as unoccupied
    }
}

// Hash function
int TenantManager::hashFunction(int TenantID) const {
    return TenantID % TABLE_SIZE;
}

// Check if a specific index is occupied
bool TenantManager::IsOccupied(int index) const {
    return occupied[index];
}

// Add new tenant
void TenantManager::AddTenant(int TenantID, const string& TenantName, const string& TenantIC, const string& TenantContact,
                              const string& TenantEmail, const string& AccountNumber, const string& BankName) {
    int index = hashFunction(TenantID);

    // Use linear probing to find the next available slot
    while (occupied[index]) {
        index = (index + 1) % TABLE_SIZE; // Wrap around if necessary
    }

    // Add the new tenant
    tenants[index] = Tenant(TenantID, TenantName, TenantIC, TenantContact, TenantEmail,
                            AccountNumber, BankName, 0.0f, "", "", 0.0f, "Not Paid");
    occupied[index] = true; // Mark this slot as occupied

    cout << "Tenant added successfully! Details will be stored at index: " << index << endl; // Indicate where the tenant was added
}

// Update a specific field of an existing tenant
void TenantManager::UpdateTenant(int TenantID, const string& field, const string& newUpdate) {
    int index = hashFunction(TenantID);

    // Use linear probing to find the tenant
    while (occupied[index]) {
        if (tenants[index].TenantID == TenantID) {
            if (field == "Name") tenants[index].TenantName = newUpdate;
            else if (field == "IC") tenants[index].TenantIC = newUpdate;
            else if (field == "Contact") tenants[index].TenantContact = newUpdate;
            else if (field == "Email") tenants[index].TenantEmail = newUpdate;
            else if (field == "AccountNumber") tenants[index].AccountNumber = newUpdate;
            else if (field == "BankName") tenants[index].BankName = newUpdate;
            else {
                cout << "Invalid field name!" << endl;
                return;
            }
            cout << "\nTenant information updated successfully!" << endl;
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Continue probing
    }
    cout << "Error: Tenant ID not found!" << endl;
}

// Get details of a tenant
string TenantManager::GetTenantDetails(int TenantID) {
    int index = hashFunction(TenantID);

    // Use linear probing to find the tenant
    while (occupied[index]) {
        if (tenants[index].TenantID == TenantID) {
            string tenantInfo;
            tenantInfo += "Tenant ID: " + to_string(tenants[index].TenantID) + "\n";
            tenantInfo += "Name: " + tenants[index].TenantName + "\n";
            tenantInfo += "IC: " + tenants[index].TenantIC + "\n";
            tenantInfo += "Contact: " + tenants[index].TenantContact + "\n";
            tenantInfo += "Email: " + tenants[index].TenantEmail + "\n";
            tenantInfo += "Account Number: " + tenants[index].AccountNumber + "\n";
            tenantInfo += "Bank Name: " + tenants[index].BankName + "\n";
            tenantInfo += "Rental Amount: " + to_string(tenants[index].RentalAmount) + "\n";
            tenantInfo += "Tenancy Period: " + tenants[index].TenancyPeriod + "\n";
            tenantInfo += "Tenancy End Date: " + tenants[index].TenancyEndDate + "\n";
            tenantInfo += "Deposit Status: " + tenants[index].DepositStatus + "\n";

            return tenantInfo;  // Return the formatted details string
        }
        index = (index + 1) % TABLE_SIZE; // Continue probing
    }
    return "Error: Tenant ID not found!";  // Return an error message if the tenant ID is not found
}

// Remove a tenant
void TenantManager::RemoveTenant(int TenantID) {
    int index = hashFunction(TenantID);

    // Use linear probing to find the tenant
    while (occupied[index]) {
        if (tenants[index].TenantID == TenantID) {
            occupied[index] = false; // Mark this slot as unoccupied
            cout << "\nTenant removed successfully!" << endl;
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Continue probing
    }
    cout << "Error: Tenant ID not found!" << endl;
}

// Check if a tenant exists
bool TenantManager::DoesTenantExist(int TenantID) const {
    int index = hashFunction(TenantID);

    // Use linear probing to find the tenant
    while (occupied[index]) {
        if (tenants[index].TenantID == TenantID) {
            return true;
        }
        index = (index + 1) % TABLE_SIZE; // Continue probing
    }
    return false;
}

// Check if the tenant manager is empty
bool TenantManager::isEmpty() const {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (occupied[i]) {
            return false;
        }
    }
    return true;
}
