/*
Program Name: Hot Dog Stand
Date:         2022-3-30
Name:         Avinash Vadivelu
Module Purpose: This program reads in the characteristics of various hot dog stands at different locations from an input file, the transactions 
                made by each stand from another file, and the amount of hot dog each of the stands sold from a third file. After reading in all of this
                information, it is then used to convey the intial and final states of the different stands.
*/
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "HotDogStandsClass.h"
#include "TransactionsClass.h"
using namespace std;

const string GLOBAL_SOLD_FILE_NAME = "InfoGlobalSold.txt";
const string HOT_DOG_STANDS_FILE_NAME = "InfoHotDogStands.txt";
const string TRANSACTIONS_FILE_NAME = "InfoHotDogStandsTransactions.txt";

ostream& operator << (ostream& outputStream, const HotDogStandsClass& hotDogStandObj);
ostream& operator << (ostream& outputStream, const TransactionsClass& transactionObj);
void ReadInfromGlobalSoldFile(string globalSoldFile);
void ReadInFromHotDogStandsFile(string hotDogStandsFilName, HotDogStandsClass*& hotDogStandsAry, unsigned& hotDogStandsCount);
void ReadInFromTransactionsFile(string transactionsFile, TransactionsClass*& transactionsAry, unsigned& transactionsCount);
void displayStateOfStands(HotDogStandsClass*& hotDogStandsAry, unsigned& totHotDogStandsCount);
void processTransaction(TransactionsClass transactionObj, HotDogStandsClass& hotDogStandObj);
void processTransactions
(HotDogStandsClass*& hotDogStandsAry, unsigned totHotDogStands, TransactionsClass* transactionsAry, unsigned transactionsCount);
unsigned getMatchingHotDogStand
(HotDogStandsClass* hotDogStandsAry, unsigned totHotDogStands, TransactionsClass* transactionsAry,unsigned transactionsCount);
void updateGlobalSoldFile(string globalSoldFilName);
void updateHotDogStandsFile(string hotDogStandFilName, HotDogStandsClass* hotDogStandsAry, unsigned totalHotDogStands);

int main(){

cout << setprecision(2) << fixed << showpoint;

HotDogStandsClass *hotDogStandsAry = nullptr;
unsigned hotDogStandsCount;
TransactionsClass *transactionsAry = nullptr;
unsigned transactionsCount;

//calls each of the read functions that read all three input files
ReadInfromGlobalSoldFile(GLOBAL_SOLD_FILE_NAME);
ReadInFromHotDogStandsFile(HOT_DOG_STANDS_FILE_NAME, hotDogStandsAry, hotDogStandsCount);
ReadInFromTransactionsFile(TRANSACTIONS_FILE_NAME, transactionsAry, transactionsCount);

cout << "Initial states of stands:" << endl;
cout << "=========================" << endl << endl;
displayStateOfStands(hotDogStandsAry, hotDogStandsCount); 

cout << "Process Transactions:" << endl;
cout << "=====================" << endl << endl;
processTransactions(hotDogStandsAry, hotDogStandsCount, transactionsAry, transactionsCount);

cout << "Final states of stands:" << endl;
cout << "=======================" << endl << endl;
displayStateOfStands(hotDogStandsAry, hotDogStandsCount);

updateHotDogStandsFile(HOT_DOG_STANDS_FILE_NAME, hotDogStandsAry, hotDogStandsCount);
updateGlobalSoldFile(GLOBAL_SOLD_FILE_NAME);

cout << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();

return EXIT_SUCCESS;
}

//organizes information from hot dog stands file
ostream& operator << (ostream& outputStream, const HotDogStandsClass& hotDogStandObj)
{
    outputStream <<
    "Stand Id  : " << hotDogStandObj.getHotDogStandID() << endl <<
    "Address   : " << hotDogStandObj.getStandLocation() << endl <<
    "Price     : " << hotDogStandObj.getCostPerHotDog() << endl <<
    "Inventory : " << hotDogStandObj.getHotDogInventory() << endl <<
    "Store Sold: " << hotDogStandObj.getHotDogSoldCount() << " at $" << hotDogStandObj.getCostPerHotDog() << " ea." << endl;
    return outputStream;
}

//organizes information from transactions file
ostream& operator << (ostream& outputStream, const TransactionsClass& transactionObj)
{
    outputStream <<
    "Transaction Stand Id : " << transactionObj.getStandID() << endl <<
    "Transaction Id       : " << transactionObj.getTransactionID() << endl <<
    "Transaction Argument : " << transactionObj.getTransactionArgs() << endl;
    return outputStream;
}

void CheckFileStreamOpen(string globalSoldFileName, ifstream& inFile) {
    if (inFile.fail()) {
        cout << "File " << globalSoldFileName << " could not be opened" << endl;
        cout << "Please press enter key once or twice to continue..."; cin.ignore(); cin.get();
        exit(EXIT_FAILURE);
    }
}

void ReadInfromGlobalSoldFile(string globalSoldFile)
{
    ifstream inFile(globalSoldFile);
    CheckFileStreamOpen(globalSoldFile, inFile);
    inFile >> HotDogStandsClass::globalSoldCount; //populates global sold file with global sold count
    inFile.close();
}

void ReadInFromHotDogStandsFile(string hotDogStandsFilName, HotDogStandsClass*& hotDogStandsAry, unsigned& hotDogStandsCount)
{
    string lineFileBuffer, inputString;
    constexpr char COMMA_DELIMETER = ',';

    ifstream inFile(hotDogStandsFilName);
    CheckFileStreamOpen(hotDogStandsFilName, inFile);

    hotDogStandsCount = 0;
    while(getline(inFile, lineFileBuffer))
        ++hotDogStandsCount;

    hotDogStandsAry = new HotDogStandsClass[hotDogStandsCount]; //creates dynamic array for information from hot dog stands 

    inFile.clear(); inFile.seekg(0, ios::beg);
    
    for(unsigned x = 0; x < hotDogStandsCount; x++) //loops through dynamic array and reads each part of the hot dog stands' characteristics
    {
        getline(inFile, lineFileBuffer);
        istringstream isStringStream(lineFileBuffer);

        getline(isStringStream, inputString, COMMA_DELIMETER);
        hotDogStandsAry[x].setHotDogStandID((inputString));

        getline(isStringStream, inputString, COMMA_DELIMETER);
        hotDogStandsAry[x].setStandLocation((inputString));

        getline(isStringStream, inputString, COMMA_DELIMETER);
        hotDogStandsAry[x].setCostPerHotDog(stof(inputString));

        getline(isStringStream, inputString, COMMA_DELIMETER);
        isStringStream >> inputString;
        hotDogStandsAry[x].setHotDogInventory(static_cast<unsigned>(stoul(inputString)));

        getline(isStringStream, inputString, COMMA_DELIMETER);
        isStringStream >> inputString;
        hotDogStandsAry[x].setHotDogSoldCount(static_cast<unsigned>(stoul(inputString)));
    }
    inFile.close();
}

void ReadInFromTransactionsFile(string transactionsFile, TransactionsClass*& transactionsAry, unsigned& transactionsCount)
{
    string lineFileBuffer, inputString;
    constexpr char COMMA_DELIMETER = ',';

    ifstream inFile(transactionsFile);
    CheckFileStreamOpen(transactionsFile, inFile);

    transactionsCount = 0;
    while(getline(inFile, lineFileBuffer))
        ++transactionsCount;

    transactionsAry = new TransactionsClass[transactionsCount]; //creates dynamic array for information from transactions

    inFile.clear(); inFile.seekg(0, ios::beg);
    
    for(unsigned x = 0; x < transactionsCount; x++)//loops through dynamic area and reads the transactions' elements 
    {
        getline(inFile, lineFileBuffer);
        istringstream isStringStream(lineFileBuffer);

        getline(isStringStream, inputString, COMMA_DELIMETER);
        transactionsAry[x].setStandID((inputString));

        getline(isStringStream, inputString, COMMA_DELIMETER);
        transactionsAry[x].setTransactionID((inputString));

        getline(isStringStream, inputString, COMMA_DELIMETER);
        transactionsAry[x].setTransactionArgs(static_cast<unsigned>(stoul(inputString)));
    }
    inFile.close();
}

void displayStateOfStands(HotDogStandsClass*& hotDogStandsAry, unsigned& totHotDogStandsCount)
{
    for (unsigned i = 0; i < totHotDogStandsCount; i++) //displays information of each stand
        cout << hotDogStandsAry[i] << endl;

    cout << endl << "Global Sold : " << HotDogStandsClass::globalSoldCount << endl;
    cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();
    cout << endl << endl;
}

unsigned getMatchingHotDogStand
(HotDogStandsClass* hotDogStandsAry, unsigned totHotDogStands, TransactionsClass* transactionsAry,unsigned transactionsCount)
{
    for(unsigned i = 0; i < totHotDogStands; i++)
    { //finds elements that associate with each other between hot dog stands and transactions array
      if(hotDogStandsAry[i].getHotDogStandID() == transactionsAry[transactionsCount].getStandID())
      { 
        return(i);
      }  
    }
    return(0);    
}

void processTransaction(TransactionsClass transactionObj, HotDogStandsClass& hotDogStandObj)
{//checks if transaction ID of a transaction object fits a description and uses that object in a method from hot dog stands class 
    if(transactionObj.getTransactionID() == "stock inventory")
    {
        hotDogStandObj.stockInventory(transactionObj.getTransactionArgs());
    }
    else if(transactionObj.getTransactionID() == "buy")
    {
        hotDogStandObj.hotDogsBuy(transactionObj.getTransactionArgs());
    }
}

void processTransactions
(HotDogStandsClass*& hotDogStandsAry, unsigned totHotDogStands, TransactionsClass* transactionsAry, unsigned transactionsCount)
{
    for(unsigned transactionNo = 0; transactionNo < transactionsCount; transactionNo++)
    {//loops through each transactions
        unsigned index = getMatchingHotDogStand(hotDogStandsAry, totHotDogStands, transactionsAry, transactionNo); //variable i holds info from getMatching method
        cout << "================================" << endl << endl;
        cout << "Current Status of Hot Dog Stand:" << endl << endl;
        cout << hotDogStandsAry[index] << endl;
        cout << "Transaction:" << endl << endl;
        processTransaction(transactionsAry[transactionNo], hotDogStandsAry[index]);
        cout << transactionsAry[transactionNo] << endl;
        cout << "Status after Transaction:" << endl << endl;
        cout << hotDogStandsAry[index] << endl << endl;
        cout << "Global Sold : " << HotDogStandsClass::globalSoldCount << endl << endl;
        cout << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get(); 
    }
}

void updateHotDogStandsFile(string hotDogStandFilName, HotDogStandsClass* hotDogStandsAry, unsigned totalHotDogStands)
{
    ofstream outFile(hotDogStandFilName);

    for(unsigned i = 0; i < totalHotDogStands; i++) //loops through each element in hot dog file and writes updated information in the file
    {
        outFile <<
        hotDogStandsAry[i].getHotDogStandID()   << "," <<
        hotDogStandsAry[i].getStandLocation()   << "," <<
        hotDogStandsAry[i].getCostPerHotDog()   << "," <<
        hotDogStandsAry[i].getHotDogInventory() << "," <<
        hotDogStandsAry[i].getHotDogSoldCount() << "," << endl; 
    }
    outFile.close();
}

void updateGlobalSoldFile(string globalSoldFilName)
{
    ofstream outFile(globalSoldFilName);
    outFile << HotDogStandsClass::globalSoldCount << endl; //writes updated global sold count to a output file
    outFile.close();
}