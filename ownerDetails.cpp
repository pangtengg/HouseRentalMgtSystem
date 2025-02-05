#include <cstring>
#include <iostream>
#include "ownerDetails.hpp"
#include "Property.hpp"
using namespace std;

List::List() {
    prevID = 0;
    head = nullptr;
    curr = nullptr;
    temp = nullptr;
}

List::~List() {
    curr = head;
    while (curr != nullptr) {
        temp = curr;
        curr = curr->next;

        Property::PropertyDetails* prop = temp->propertyHead;
        while (prop != nullptr) {
            Property::PropertyDetails* tempProp = prop;
            prop = prop->next;
            delete tempProp;
        }

        delete[] temp->OwnerName;
        delete[] temp->OwnerContact;
        delete[] temp->OwnerEmail;
        delete temp;
    }
}

void List::AddOwner(const char* OwnerName, const char* OwnerContact, const char* OwnerEmail) {
    OwnerPtr newOwner = new Owner;
    newOwner->OwnerID = getNextID();

    newOwner->OwnerName = new char[strlen(OwnerName) + 1];
    strcpy(newOwner->OwnerName, OwnerName);

    newOwner->OwnerContact = new char[strlen(OwnerContact) + 1];
    strcpy(newOwner->OwnerContact, OwnerContact);

    newOwner->OwnerEmail = new char[strlen(OwnerEmail) + 1];
    strcpy(newOwner->OwnerEmail, OwnerEmail);

    newOwner->propertyHead = nullptr;
    newOwner->next = nullptr;

    if (head == nullptr) {
        head = newOwner;
    } else {
        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newOwner;
    }
    cout << "\nOwner added successfully! " << endl;
    cout << "Name: " << OwnerName << endl;
    cout << "ID  : ";
    formattedID(newOwner->OwnerID);
    cout << endl;
}

void List::UpdateOwner(int OwnerID, const char* OwnerName, const char* OwnerContact, const char* OwnerEmail) {
    curr = head;
    while (curr != nullptr) {
        if (curr->OwnerID == OwnerID) {
            delete[] curr->OwnerName;
            delete[] curr->OwnerContact;
            delete[] curr->OwnerEmail;

            curr->OwnerName = new char[strlen(OwnerName) + 1];
            strcpy(curr->OwnerName, OwnerName);

            curr->OwnerContact = new char[strlen(OwnerContact) + 1];
            strcpy(curr->OwnerContact, OwnerContact);

            curr->OwnerEmail = new char[strlen(OwnerEmail) + 1];
            strcpy(curr->OwnerEmail, OwnerEmail);

            cout << "Owner details updated successfully." << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Owner ID: " << OwnerID << " not found." << endl;
}

void List::GetOwnerDetails() {
    if (head == nullptr) {
        cout << "No owners found in the system. " << endl;
        return;
    }
    curr = head;
    while (curr != nullptr) {
        cout << "Owner ID: ";
        formattedID(curr->OwnerID);
        cout << endl;
        cout << "Name       : " << curr->OwnerName << endl;
        cout << "Contact    : " << curr->OwnerContact << endl;
        cout << "Email      : " << curr->OwnerEmail << endl;

        Property::PropertyDetails* prop = curr->propertyHead;
        if (prop == nullptr) {
            cout << "Properties : None" << endl;
        } else {
            cout << "Properties :" << endl;
            while (prop != nullptr) {
                cout << "   - Property ID: " << prop->PropertyID << endl;
                prop = prop->next;
            }
        }
        cout << "\n----------------------------------------" << endl;
        curr = curr->next;
    }
}

void List::GetOwnerByID(int OwnerID) {
    curr = head;
    while (curr != nullptr) {
        if (curr->OwnerID == OwnerID) {
            cout << "Owner ID: " << curr->OwnerID << endl;
            cout << "Name    : " << curr->OwnerName << endl;
            cout << "Contact : " << curr->OwnerContact << endl;
            cout << "Email   : " << curr->OwnerEmail << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Owner ID: " << OwnerID << " not found." << endl;
}

void List::RemoveOwner(int OwnerID) {
    if (head == nullptr) {
        cout << "There are no owners in the system." << endl;
        return;
    }

    temp = head;
    curr = head;

    while (curr != nullptr && curr->OwnerID != OwnerID) {
        temp = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Owner ID: " << OwnerID << " not found." << endl;
        return;
    }

    if (curr == head) {
        head = head->next;
    } else {
        temp->next = curr->next;
    }

    cout << "\nRemoving owner:" << endl;
    cout << "Name: " << curr->OwnerName << endl;
    cout << "ID  : " << curr->OwnerID << endl;

    delete[] curr->OwnerName;
    delete[] curr->OwnerContact;
    delete[] curr->OwnerEmail;
    delete curr;

    cout << "Owner removed successfully." << endl;
}

void List::UpdatePropertyCount(int OwnerID, int countChange) {
    curr = head;
    while (curr != nullptr) {
        if (curr->OwnerID == OwnerID) {
            // Assuming there's a propertyCount member in the Owner struct
            curr->propertyCount += countChange;
            return;
        }
        curr = curr->next;
    }
    cout << "Owner ID: " << OwnerID << " not found." << endl;
}

bool List::IsOwnerExist(int OwnerID) {
    curr = head;
    while (curr != nullptr) {
        if (curr->OwnerID == OwnerID) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

List::OwnerPtr List::FindOwnerByID(int OwnerID) {
    OwnerPtr current = head;
    while (current != nullptr) {
        if (current->OwnerID == OwnerID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
