#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP
#include <string>
using namespace std;

struct Deposit {
    int TenantID;
    double DepositAmount;
    string DepositStatus;
};

class DepositManager{
public:
    DepositManager();
    void AddDeposit();
    void ViewDeposits();
    void UpdateDeposit(int tenantID); // for owners
    void ViewTenantDeposit(int tenantID); // for tenants

private:
    static const int MAX_DEPOSITS = 100;
    Deposit deposits[MAX_DEPOSITS];
    int depositSize;
};

#endif

