/*
Program Name: Hot Dog Stand
Date:         2022-3-30
Name:         Avinash Vadivelu
Module Purpose: This program reads in the characteristics of various hot dog stands at different locations from an input file, the transactions 
                made by each stand from another file, and the amount of hot dog each of the stands sold from a third file. After reading in all of this
                information, it is then used to convey the intial and final states of the different stands.
*/

#ifndef HOTDOG_STAND_CLASS_CPP
#define HOTDOG_STAND_CLASS_CPP
#include "HotDogStandsClass.h"
using namespace std;

    unsigned HotDogStandsClass::globalSoldCount = 0;

    void HotDogStandsClass::hotDogsBuy(unsigned n)
    {
        if(hotDogInventory == 0)
        {
            cout << "There are no more hot dogs left to be sold, so please come at a later time" << endl << endl;
            return;
        }
        else if(hotDogInventory < n)
        {
            cout << "There is only " << hotDogInventory << " hot dogs, so retry your buy" << endl;
            cout << (hotDogInventory > 1 ? "s left*" : "left *") << endl << endl;
            return;
        }
        hotDogInventory = hotDogInventory - n;
        hotDogSoldCount = hotDogSoldCount + n;
        HotDogStandsClass::globalSoldCount += n;
    }

    #endif

