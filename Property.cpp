#include <iostream>
#include <iomanip>
#include <string>
#include "Property.hpp"
#include "ownerDetails.hpp"
using namespace std;

Property::Property():nextPropertyID(1), currentSize(0)
{
    hashTable = new PropertyDetails[HASH_SIZE];
    initializeHashTable();
}

Property::~Property()
{
    delete[] hashTable;
}

void Property::initializeHashTable()
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i].isOccupied = false;
        hashTable[i].PropertyID = -1;  // -1 indicates empty slot
    }
}

void Property::hash(const PropertyDetails* storageArea, int size, int PropertyID, int& storeIndex, bool& found, int probeStopValue)
{
    int counter = 1;
    found = true;
    storeIndex = PropertyID % size;

    while(storageArea[storeIndex].PropertyID != probeStopValue && storageArea[storeIndex].isOccupied)
    {
        storeIndex = (storeIndex + 1) % size;
        counter++;
        if (counter > size)
        {
            found = false;
            break;
        }
    }
}

Property::PropertyDetails Property::createPropertyDetails(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus)
{
    Property::PropertyDetails newProperty;
    newProperty.PropertyID = PropertyID;
    newProperty.PropertyAddress = PropertyAddress;
    newProperty.UnitDetails = UnitDetails;
    newProperty.RentDeposit = RentDeposit;
    newProperty.RentAmt = RentAmt;
    newProperty.OccupancyStatus = OccupancyStatus;
    newProperty.isOccupied = true;

    return newProperty;
}

int Property::AddProperty(List& OwnerList, int OwnerID, int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus)
{
    if (currentSize >= HASH_SIZE)
    {
        cout << "Hash table is full." << endl;
        return -1;
    }

    // Associate the property with the owner
    List::OwnerPtr Owner = OwnerList.FindOwnerByID(OwnerID); // Changed to OwnerPtr
    if (!Owner)
    {
        cout << "Owner ID not found. Please add the owner first." << endl;
        return -1;
    }

    PropertyID = nextPropertyID;
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, -1);

    if (!found)
    {
        return -1;
    }

    hashTable[storeIndex] = createPropertyDetails(PropertyID, PropertyAddress, UnitDetails, RentDeposit, RentAmt, OccupancyStatus);
    currentSize++;
    nextPropertyID++;

    // Create a new PropertyPtr
    PropertyDetails* newProperty = new PropertyDetails(hashTable[storeIndex]);
    newProperty->next = Owner->propertyHead;  // Assign using the raw pointer inside PropertyPtr
    Owner->propertyHead = newProperty;           // Assign the PropertyPtr

    cout << "Property added successfully! Property ID: " << PropertyID << endl;
    return PropertyID;
}

bool Property::UpdateProperty(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if (!found || !hashTable[storeIndex].isOccupied)
    {
        return false;
    }

    hashTable[storeIndex].PropertyAddress = PropertyAddress;
    hashTable[storeIndex].UnitDetails = UnitDetails;
    hashTable[storeIndex].RentDeposit = RentDeposit;
    hashTable[storeIndex].RentAmt = RentAmt;
    hashTable[storeIndex].OccupancyStatus = OccupancyStatus;

    return true;
}

bool Property::UnitStatus(int PropertyID, const string& OccupancyStatus)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if(!found || !hashTable[storeIndex].isOccupied)
    {
        return false;
    }

    hashTable[storeIndex].OccupancyStatus = OccupancyStatus;
    return true;
}

const string Property::CheckVacancy(int PropertyID)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if(!found || !hashTable[storeIndex].isOccupied)
    {
        return "Property not found. Try again!";
    }

    return hashTable[storeIndex].OccupancyStatus;
}

const string Property::toLowerCase(const string& input) {
    string lower = input;
    for (char& c : lower)
        c = tolower(c);
    return lower;
}

void Property::VacantUnits(int* vacantUnits, int& count)
{
    count = 0;
    bool foundVacant = false;

    for(int i=0; i<HASH_SIZE; i++)
    {
        if(hashTable[i].isOccupied && toLowerCase(hashTable[i].OccupancyStatus) == "empty")
        {
            foundVacant = true;
            vacantUnits[count++] = hashTable[i].PropertyID;

            // Display detailed information for each vacant property
            cout << "\nProperty ID: " << hashTable[i].PropertyID << endl;
            cout << "Address: " << hashTable[i].PropertyAddress << endl;
            cout << "Unit Details: " << hashTable[i].UnitDetails << endl;
            cout << "Rent Deposit: RM" << fixed << setprecision(2) << hashTable[i].RentDeposit << endl;
            cout << "Monthly Rent: RM" << fixed << setprecision(2) << hashTable[i].RentAmt << endl;
            cout << "Status: " << hashTable[i].OccupancyStatus << endl;
        }
    }
    if(!foundVacant)
    {
        cout << "No vacant properties found." << endl;
    }
}

const string toLowerCase(const string& input)
{
    string lower = input;
    for (char& c : lower)
        c = tolower(c);
    return lower;
}

bool Property::RemoveProperty(int PropertyID)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if(!found || !hashTable[storeIndex].isOccupied)
    {
        return false;
    }

    hashTable[storeIndex].isOccupied = false;
    hashTable[storeIndex].PropertyID = -1;
    currentSize--;
    return true;
}
