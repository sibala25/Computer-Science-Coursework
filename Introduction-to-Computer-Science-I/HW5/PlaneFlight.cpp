//  Aashna Sibal
//  HW5
//  PlaneFlight.cpp

#include "PlaneFlight.h"
#include <string>

using namespace std;

// constructor
PlaneFlight::PlaneFlight(string passengerName, string fromCity, string toCity, double cost, double mileage) {
    setCost(cost);
    setMileage(mileage);
    setName(passengerName);
    setFromCity(fromCity);
    setToCity(toCity);
    
}

//    return type className::method name;
double PlaneFlight::getCost( ) {
    return mCost; // getting correct cost
}

void PlaneFlight::setCost( double cost ) {
    if (cost < 0) {                                // if the cost is a negative number, it is invalid
        mCost = -1;
    }
    else {
        mCost = cost;                              // valid cost
    }
}
    
double PlaneFlight::getMileage( ) {
    return mMileage; // getting mileage
}
void PlaneFlight::setMileage( double mileage ) {
    if (mileage <= 0) {                            // if the mileage is a 0 or a negative number, it is invalid
        mMileage = -1;
    }
    else {
        mMileage = mileage;                        // valid mileage
    }
}
    
string PlaneFlight::getName( ) {
    return mName;  // getting name
}
    
void PlaneFlight::setName( string name ) {
    if (name != "") {                              // name cannot be the empty string
        mName = name;
    }
}
    
string PlaneFlight::getFromCity( ) {
    return mFromCity; // getting departure city
}

void PlaneFlight::setFromCity( string from ) {
    if (from != "" && from != mToCity) {           // from cannot be the empty string and from city and to city cannot be the same
        mFromCity = from;
    }
}

string PlaneFlight::getToCity( ) {
    return mToCity; // getting destination
}

void PlaneFlight::setToCity( string to ) {
    if (to != "" && to != mFromCity) {            // to cannot be the empty string and to city and from city cannot be the same
        mToCity = to;
    }
}
    
