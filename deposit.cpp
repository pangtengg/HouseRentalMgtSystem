#include <iostream>
#include <string>
#include "deposit.hpp"

using namespace std;

DepositManager::DepositManager() : depositSize(0) {}

void DepositManager::AddDeposit() {
    if (depositSize >= MAX_DEPOSITS) {
        cout << "Array is full, cannot add more deposit records." << endl;
        return;
    }

    Deposit newDeposit;
    cout << "Enter Tenant ID          : ";
    cin >> newDeposit.TenantID;
    cout << "Enter Deposit Amount (RM): ";
    cin >> newDeposit.DepositAmount;
    cout << "Enter Deposit Status: ";
    cin >> newDeposit.DepositStatus;
    deposits[depositSize++] = newDeposit;
    cout << "Deposit added successfully." << endl;
}

void DepositManager::ViewDeposits() {
    if (depositSize == 0) {
        cout << "No deposit records to display." << endl;
        return;
    }

    cout << "Deposit Records: " << endl;
    for(int i = 0; i < depositSize; i++) {
        cout << "Tenant ID     : " << deposits[i].TenantID << endl;
        cout << "Deposit Amount: RM " << deposits[i].DepositAmount << endl;
        cout << "Deposit Status: " << deposits[i].DepositStatus << endl;
        cout << "----------------------------" << endl;
    }
}

void DepositManager::UpdateDeposit(int tenantID) {
    for (int i = 0; i < depositSize; ++i) {
        if (deposits[i].TenantID == tenantID) {
            cout << "Enter new Deposit Amount: ";
            cin >> deposits[i].DepositAmount;
            cout << "Enter new Deposit Status: ";
            cin >> deposits[i].DepositStatus;
            cout << "Deposit updated successfully!" << endl;
            return;
        }
    }
    cout << "Deposit for Tenant ID " << tenantID << " not found." << endl;
}

void DepositManager::ViewTenantDeposit(int tenantID) {
    cout << "Enter Tenant ID to view deposit record: ";
    cin >> tenantID;

    bool found = false;
    for (int i = 0; i < depositSize; ++i) {
        if (deposits[i].TenantID == tenantID) {
            cout << "Your Deposit Record:\n";
            cout << "Amount: " << deposits[i].DepositAmount
                 << ", Status: " << deposits[i].DepositStatus << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "No deposit record found for Tenant ID " << tenantID << "." << endl;
    }
}
