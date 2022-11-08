

#ifndef TRANSACTIONS_CLASS_H
#define TRANSACTIONS_CLASS_H
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class TransactionsClass
{
    private:
    string standID;
    string transactionID;
    unsigned transactionArgs;

    public:
    const string& getStandID() const
    {
        return standID;
    }

    void setStandID(string standID)
    {
        this->standID = standID;
    }

    const string& getTransactionID() const
    {
        return transactionID;
    }

    void setTransactionID(string transactionID)
    {
        this->transactionID = transactionID;
    }

    unsigned getTransactionArgs() const
    {
        return transactionArgs;
    }

    void setTransactionArgs(unsigned transactionArgs)
    {
        this->transactionArgs = transactionArgs;
    }
};

#endif