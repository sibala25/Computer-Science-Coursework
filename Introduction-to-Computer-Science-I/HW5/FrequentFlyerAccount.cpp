//  Aashna Sibal
//  HW5
//  FrequentFlyerAccount.cpp

#include "FrequentFlyerAccount.h"
#include <string>

using namespace std;

// constructor
FrequentFlyerAccount::FrequentFlyerAccount(string name) {
    mName = name;
    mBalance = 0; // balance should start at 0 miles
}

// return type className::method name;
double FrequentFlyerAccount::getBalance( ) {
    return mBalance; // getting correct current balance
}

string FrequentFlyerAccount::getName( ) {
    return mName; // getting correct current name
}

bool FrequentFlyerAccount::addFlightToAccount( PlaneFlight flight ){
    if (mName == flight.getName()) { // if the passenger name matches the account name
        mBalance += flight.getMileage(); // add miles to their balance
        return true;
    }
    else {
        return false; // names do not match
    }
}

bool FrequentFlyerAccount::canEarnFreeFlight( double mileage ) {
    return (mileage <= mBalance);     // if person's balance is = or > than the flight mileage, they can earn a free flight so true, else false
}

bool FrequentFlyerAccount::freeFlight( string from, string to, double mileage, PlaneFlight& flight ) {
    if (canEarnFreeFlight(mileage)) { // if eligible for a free flight
        mBalance -= mileage;          // subtract the miles they are redeeming from balance
        flight.setMileage(mileage);   // replacing flight info for this new flight
        flight.setCost(0);            // free flight since using miles
        flight.setFromCity(from);
        flight.setToCity(to);
        flight.setName(mName);
        return true;
    }
    else {
        return false;                 // not enough miles for the free flight
    }
}

