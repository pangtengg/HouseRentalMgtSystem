#ifndef ownerDetails_h
#define ownerDetails_h

#include <iostream>
#include <iomanip>
#include "Property.hpp"  // Ensure this header file is included

using namespace std;

class Property;  // Forward declaration of Property

class List {
private:
    struct Owner {
        int OwnerID;
        char* OwnerName;
        char* OwnerContact;
        char* OwnerEmail;
        int propertyCount;
        Owner* next;
        Property::PropertyDetails* propertyHead;  // Use Property::PropertyDetails here

        Owner() : OwnerID(0), OwnerName(nullptr), OwnerContact(nullptr), OwnerEmail(nullptr), next(nullptr), propertyHead(nullptr) {}
    };

public:
    typedef Owner* OwnerPtr;  // Move this to the public section
    OwnerPtr head;
    OwnerPtr curr;
    OwnerPtr temp;
    int prevID;

    void formattedID(int id) const {
        cout << setw(5) << setfill('0') << id;
    }

    int getNextID() {
        int nextID = prevID + 1;

        if (nextID > 99999) {
            nextID = 1;  // Reset to 1
        }

        curr = head;
        while (curr != NULL) {
            if (curr->OwnerID == nextID) {
                nextID++;
                if (nextID > 99999) nextID = 1;
                curr = head;
                continue;
            }
            curr = curr->next;
        }
        prevID = nextID;
        return nextID;
    }

    List();
    ~List();

    typedef Owner* ownerPtr;

    void AddOwner(const char* OwnerName, const char* OwnerContact, const char* OwnerEmail);
    void UpdateOwner(int OwnerID, const char* OwnerName, const char* OwnerContact, const char* OwnerEmail);
    void GetOwnerDetails();
    void GetOwnerByID(int OwnerID);
    void RemoveOwner(int OwnerID);
    bool IsOwnerExist(int OwnerID);
    void UpdatePropertyCount(int OwnerID, int countChange);
    OwnerPtr FindOwnerByID(int OwnerID);
};

#endif // header_h
