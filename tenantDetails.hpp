#ifndef TENANTDETAILS_HPP
#define TENANTDETAILS_HPP

#include <string>

using namespace std;

namespace tenantDetails {

    const int TABLE_SIZE = 100; // Size of the hash table

    class Tenant {
    public:
        int TenantID;
        string TenantIC, TenantName, TenantContact, TenantEmail, AccountNumber, BankName;
        string TenancyPeriod, TenancyEndDate, DepositStatus;
        float RentalAmount, PaymentDue;

        // Default constructor
        Tenant() : TenantID(0), TenantIC(""), TenantName(""), TenantContact(""), TenantEmail(""),
                   AccountNumber(""), BankName(""), RentalAmount(0), PaymentDue(0), DepositStatus("Not Paid") {}

        // Parameterized constructor
        Tenant(int id, const string& name, const string& ic, const string& contact, const string& email,
               const string& accNum, const string& bankName, float rentAmount, const string& period,
               const string& endDate, float paymentDue, const string& depositStatus)
            : TenantID(id), TenantIC(ic), TenantName(name), TenantContact(contact), TenantEmail(email),
              AccountNumber(accNum), BankName(bankName), RentalAmount(rentAmount), PaymentDue(paymentDue),
              TenancyPeriod(period), TenancyEndDate(endDate), DepositStatus(depositStatus) {}
    };

    class TenantManager {
    public:
        TenantManager();

        void AddTenant(int TenantID, const string& TenantName, const string& TenantIC, const string& TenantContact,
                       const string& TenantEmail, const string& AccountNumber, const string& BankName);
        void UpdateTenant(int TenantID, const string& field, const string& newUpdate);
        string GetTenantDetails(int TenantID);
        void RemoveTenant(int TenantID);
        bool DoesTenantExist(int TenantID) const;
        bool IsOccupied(int index) const;
        bool isEmpty() const;
        int hashFunction(int TenantID) const;

    private:
        Tenant tenants[TABLE_SIZE]; // Array to store tenants
        bool occupied[TABLE_SIZE]; // Array to track occupied slots
    };

}

#endif
