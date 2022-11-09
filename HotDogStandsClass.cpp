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

