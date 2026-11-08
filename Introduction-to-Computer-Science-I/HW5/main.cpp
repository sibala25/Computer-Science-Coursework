#include "PlaneFlight.h"
#include "FrequentFlyerAccount.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;
int main()
{
PlaneFlight f1( "Howard", "Los Angeles", "Las Vegas", 79.00, 295 );
PlaneFlight f2( "Pixie", "Los Angeles", "New York City", 699.00, 3150 );
FrequentFlyerAccount a1( "Howard" );
FrequentFlyerAccount a2( "Pixie" );
bool result = false;
switch (n)
{
case 1:
assert( f1.getName() == "Howard" );
assert( f1.getFromCity () == "Los Angeles" );
assert( f1.getToCity() == "Las Vegas" );
assert( std::to_string( f1.getCost() ) == "79.000000" );
assert( std::to_string( f1.getMileage() ) == "295.000000" );
break;
case 2:
f2.setName( "You" );
f2.setCost( 129.00 );
f2.setFromCity( "Burbank" );
f2.setToCity( "Pheonix" );
f2.setMileage( 500 );
assert( f2.getName() == "You" );
assert( f2.getFromCity () == "Burbank" );
assert( f2.getToCity() == "Pheonix" );
assert( std::to_string( f2.getCost() ) == "129.000000" );
assert( std::to_string( f2.getMileage() ) == "500.000000" );
break;
case 3:
f2.setName( "" );
f2.setCost( -100.50 );
f2.setFromCity( "" );
f2.setToCity( "" );
f2.setMileage( -230 );
assert( f2.getName() == "Pixie" );
assert( f2.getFromCity () == "Los Angeles" );
assert( f2.getToCity() == "New York City" );
assert( std::to_string( f2.getCost() ) == "-1.000000" );
assert( std::to_string( f2.getMileage() ) == "-1.000000" );
break;
case 4:
assert( a1.getName() == "Howard" );
assert( std::to_string( a1.getBalance() ) == "0.000000" );
assert( a1.canEarnFreeFlight( 1000 ) == false );
break;
case 5:
assert( a1.getName() == "Howard" );
assert( std::to_string( a1.getBalance() ) == "0.000000" );
assert( a1.canEarnFreeFlight( 1000 ) == false );
a1.addFlightToAccount( f1 ); // name matches
a1.addFlightToAccount( f2 ) ; // name does not match
assert( a1.getName() == "Howard" );
assert( std::to_string( a1.getBalance() ) == "295.000000" );
assert( a1.canEarnFreeFlight( 200 ) == true );
assert( a1.canEarnFreeFlight( 300 ) == false );
break;
case 6:
assert( a2.getName() == "Pixie" );
assert( std::to_string( a2.getBalance() ) == "0.000000" );
assert( a2.canEarnFreeFlight( 1000 ) == false );
a2.addFlightToAccount( f1 ); // name does not matches
a2.addFlightToAccount( f2 ) ; // name matches
assert( a2.getName() == "Pixie" );
assert( std::to_string( a2.getBalance() ) == "3150.000000" );
assert( a2.canEarnFreeFlight( 3100 ) == true );
assert( a2.canEarnFreeFlight( 3200 ) == false );
break;
case 7:
assert( a2.getName() == "Pixie" );
assert( std::to_string( a2.getBalance() ) == "0.000000" );
assert( a2.canEarnFreeFlight( 1000 ) == false );
a2.addFlightToAccount( f1 ); // name does not matches
a2.addFlightToAccount( f2 ) ; // name matches
assert( a2.getName() == "Pixie" );
assert( std::to_string( a2.getBalance() ) == "3150.000000" );
assert( a2.canEarnFreeFlight( 3100 ) == true );
assert( a2.canEarnFreeFlight( 3200 ) == false );
result = a2.freeFlight( "Las Vegas", "Los Angeles", 295, f1 );
assert( result == true );
assert( std::to_string( a2.getBalance( ) ) == "2855.000000" );
assert( f1.getName() == "Pixie" );
assert( f1.getFromCity () == "Las Vegas" );
assert( f1.getToCity() == "Los Angeles" );
assert( std::to_string( f1.getCost() ) == "0.000000" );
assert( std::to_string( f1.getMileage() ) == "295.000000" );
break;
case 8:
assert( a1.getName() == "Howard" );
assert( std::to_string( a1.getBalance() ) == "0.000000" );
assert( a1.canEarnFreeFlight( 1000 ) == false );
a1.addFlightToAccount( f1 ); // name matches
a1.addFlightToAccount( f1 ) ; // name does not match
assert( std::to_string( a1.getBalance() ) == "590.000000" );
result = a1.freeFlight( "New York", "Los Angeles", 3150, f1 );
assert( result == false );
// nothing in f1 should have changed...
assert( f1.getName() == "Howard" );
assert( f1.getFromCity () == "Los Angeles" );
assert( f1.getToCity() == "Las Vegas" );
assert( std::to_string( f1.getCost() ) == "79.000000" );
assert( std::to_string( f1.getMileage() ) == "295.000000" );
assert( std::to_string( a1.getBalance() ) == "590.000000" );
break;
case 9:
assert( a2.getName() == "Pixie" );
assert( std::to_string( a2.getBalance() ) == "0.000000" );
assert( a2.canEarnFreeFlight( 1000 ) == false );
a2.addFlightToAccount( f1 ); // name does not matches
a2.addFlightToAccount( f2 ) ; // name matches
assert( a2.getName() == "Pixie" );
assert( std::to_string( a2.getBalance() ) == "3150.000000" );
assert( a2.canEarnFreeFlight( 3100 ) == true );
assert( a2.canEarnFreeFlight( 3200 ) == false );
result = a2.freeFlight( "Las Vegas", "Los Angeles", 295, f1 );
assert( result == true );
assert( std::to_string( a2.getBalance( ) ) == "2855.000000" );
assert( f1.getName() == "Pixie" );
assert( f1.getFromCity () == "Las Vegas" );
assert( f1.getToCity() == "Los Angeles" );
assert( std::to_string( f1.getCost() ) == "0.000000" );
assert( std::to_string( f1.getMileage() ) == "295.000000" );
// free flights do not earn account credit...
a2.addFlightToAccount( f1 );
assert( std::to_string( a2.getBalance( ) ) == "2855.000000" );
break;
default:
cout << "Bad argument" << endl;
break;
}
return( 0 );
}
