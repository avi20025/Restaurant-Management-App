
#ifndef HOTDOG_STAND_CLASS_H
#define HOTDOG_STAND_CLASS_H
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

class HotDogStandsClass 
{
    private:
    string hotDogStandID, standLocation;
    float costPerHotDog;
    unsigned hotDogInventory, hotDogSoldCount;

    public:
    HotDogStandsClass() = default;
    static unsigned globalSoldCount;

    const string& getHotDogStandID() const
    {
        return hotDogStandID;
    }

    void setHotDogStandID(const string& hotDogStandID)
    {
        this->hotDogStandID = hotDogStandID;
    }

    const string& getStandLocation() const
    {
        return standLocation;
    }
     
    void setStandLocation(const string& standLocation)
    {
        this->standLocation = standLocation;
    }

    float getCostPerHotDog() const
    {
        return costPerHotDog;
    }

    void setCostPerHotDog(float costPerHotDog)
    {
        this->costPerHotDog = costPerHotDog;
    }

    unsigned getHotDogSoldCount() const
    {
        return hotDogSoldCount;
    }

    void setHotDogSoldCount(unsigned hotDogSoldCount)
    {
        this->hotDogSoldCount = hotDogSoldCount;
    }

    unsigned getHotDogInventory() const
    {
        return hotDogInventory;
    }

    void setHotDogInventory(unsigned hotDogInventory)
    {
        this->hotDogInventory = hotDogInventory;
    }

    void stockInventory(unsigned n)
    {
        hotDogInventory += n;
    }
    
    void hotDogsBuy(unsigned n);
   
};

#endif