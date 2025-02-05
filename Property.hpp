#ifndef PROPERTY_HPP
#define PROPERTY_HPP
#include <string>

using namespace std;

const int HASH_SIZE = 100; // Size of the hash table

class List;

class Property
{
    public:
        struct PropertyDetails
        {
            int PropertyID;
            string PropertyAddress;
            string UnitDetails;
            float RentDeposit;
            float RentAmt;
            string OccupancyStatus;
            bool isOccupied;
            PropertyDetails* next;

            PropertyDetails() : PropertyID(-1), RentDeposit(0), RentAmt(0), isOccupied(false), next(nullptr){}
        };

        typedef PropertyDetails* PropertyPtr;

        //struct Owner{
        //    Owner* OwnerPtr;
        //};

        //typedef PropertyDetails* PropertyPtr;
        //typedef Owner* OwnerPtr;

        Property();
        ~Property();

        int AddProperty(List& OwnerList, int OwnerID, int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus);
        bool UpdateProperty(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus);
        bool UnitStatus(int PropertyID, const string& OccupancyStatus);
        const string CheckVacancy(int PropertyID);
        void VacantUnits(int* vacantUnits, int& count);
        bool RemoveProperty(int PropertyID);
        const string toLowerCase(const string& input);

    private:
        PropertyDetails* hashTable;
        int nextPropertyID;
        int currentSize;

        void hash(const PropertyDetails* storageArea, int size, int PropertyID, int& storeIndex, bool& found, int probeStopValue);
        void initializeHashTable();
        Property::PropertyDetails createPropertyDetails(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus);
        //void displayArray(const PropertyDetails* array, int size);
};

#endif
