
// Aashna Sibal
// Project 2
// UID: [student ID redacted]

#include <iostream>

using namespace std;

int main() {
    // defining variables according to expected data types
    string state, month;
    double amount;
    int day, year;
    
    // getting user info
    
    // getline for states since they can be > 1 word long
    cout << "State Name: ";
    getline(cin,state);
    
    // clearing any potential errors to continue input
    cin.clear();
    cout << "Purchase amount: ";
    cin >> amount;
    
    // ignore new line character left by last cin
    // getline for cases where the month is accidentally longer than a word, and since it is a string
    cin.clear();
    cin.ignore(10000,'\n');
    cout << "Provide the month: ";
    getline(cin,month);
    
    cin.clear();
    cout << "Provide the day: ";
    cin >> day;
    
    cin.clear();
    cin.ignore(10000,'\n');
    cout << "Provide the year: ";
    cin >> year;

    
    // initializing tax rate variables
    // since many rates are 0.0, defined the variable and assigned it as 0.0
    double stateRate = 0.00;
    double localRate = 0.00;
    double levy = 0.00;
    
    // if the state tax rate is not 0 for a state, then there is a corresponding if statement below to change that variable
    // otherwise it stays as 0
    if (state == "Alabama"||
        state == "Georgia"||
        state == "Hawaii"||
        state == "New York"||
        state == "Wyoming")
    {
        stateRate = 4.00;
    }
    
    if (state == "Arizona")
    {
        stateRate = 5.60;
    }
    
    if (state == "Arkansas"||
        state == "Kansas"||
        state == "Washington")
    {
        stateRate = 6.50;
    }
    
    if (state == "California")
    {
        stateRate = 7.25;
    }
    
    if (state == "Colorado")
    {
        stateRate = 2.90;
    }
    
    if (state == "Connecticut")
    {
        stateRate = 6.35;
    }
    
    if (state == "Florida"||
        state == "Idaho"||
        state == "Iowa"||
        state == "Kentucky"||
        state == "Maryland"||
        state == "Michigan"||
        state == "Pennsylvania"||
        state == "South Carolina"||
        state == "Vermont"||
        state == "West Virginia")
    {
        stateRate = 6.00;
    }
    
    if (state == "Illinois"||
        state == "Massachusetts"||
        state == "Texas")
    {
        stateRate = 6.25;
    }
    
    if (state == "Indiana"||
        state == "Mississippi"||
        state == "Rhode Island"||
        state == "Tennessee")
    {
        stateRate = 7.00;
    }
    
    if (state == "Louisiana")
    {
        stateRate = 4.45;
    }
    
    if (state == "Maine"||
        state == "Nebraska")
    {
        stateRate = 5.50;
    }
    
    if (state == "Minnesota")
    {
        stateRate = 6.88;
    }
    
    if (state == "Missouri")
    {
        stateRate = 4.23;
    }
    
    if (state == "Nevada")
    {
        stateRate = 6.85;
    }
    
    if (state == "New Jersey")
    {
        stateRate = 6.63;
    }
    
    if (state == "New Mexico")
    {
        stateRate = 5.13;
    }
    
    if (state == "North Carolina")
    {
        stateRate = 4.75;
    }
    
    if (state == "North Dakota"||
        state == "Wisconsin")
    {
        stateRate = 5.00;
    }
    
    if (state == "Ohio")
    {
        stateRate = 5.75;
    }
    
    if (state == "Oklahoma"||
        state == "South Dakota")
    {
        stateRate = 4.50;
    }
    
    if (state == "Utah")
    {
        stateRate = 5.95;
    }
    
    if (state == "Virginia")
    {
        stateRate = 5.30;
    }

    // if the local tax rate is not 0 for a state, then there is a corresponding if statement below to change that variable
    // otherwise it stays as 0
    if (state == "Alabama")
    {
        localRate = 5.14;
    }
    
    if (state == "Alaska"||
        state == "South Carolina")
    {
        localRate = 1.43;
    }
    
    if (state == "Arizona")
    {
        localRate = 2.77;
    }
    
    if (state == "Arkansas")
    {
        localRate = 2.93;
    }
    
    if (state == "California")
    {
        localRate = 1.31;
    }
    
    if (state == "Colorado")
    {
        localRate = 4.73;
    }

    if (state == "Florida")
    {
        localRate = 1.05;
    }
    
    if (state == "Georgia")
    {
        localRate = 3.29;
    }
    
    if (state == "Hawaii")
    {
        localRate = 0.41;
    }
    
    if (state == "Idaho")
    {
        localRate = 0.03;
    }
    
    if (state == "Illinois")
    {
        localRate = 2.49;
    }
    
    if (state == "Iowa")
    {
        localRate = 0.82;
    }
    
    if (state == "Kansas")
    {
        localRate = 2.17;
    }
    
    if (state == "Louisiana")
    {
        localRate = 5.00;
    }
    
    if (state == "Minnesota")
    {
        localRate = 0.55;
    }
    
    if (state == "Mississippi")
    {
        localRate = 0.07;
    }
    
    if (state == "Missouri")
    {
        localRate = 3.90;
    }
    
    if (state == "Nebraska")
    {
        localRate = 1.35;
    }
    
    if (state == "Nevada")
    {
        localRate = 1.29;
    }
    
    if (state == "New Jersey")
    {
        localRate = -0.03;
    }
    
    if (state == "New Mexico")
    {
        localRate = 2.69;
    }
    
    if (state == "New York")
    {
        localRate = 4.49;
    }
    
    if (state == "North Carolina")
    {
        localRate = 2.22;
    }
    
    if (state == "North Dakota")
    {
        localRate = 1.85;
    }
    
    if (state == "Ohio")
    {
        localRate = 1.42;
    }
    
    if (state == "Oklahoma")
    {
        localRate = 4.42;
    }
    
   if (state == "Pennsylvania")
    {
        localRate = 0.34;
    }
    
    if (state == "South Dakota")
    {
        localRate = 1.90;
    }
    
    if (state == "Tennessee")
    {
        localRate = 2.47;
    }
    
    if (state == "Texas")
    {
        localRate = 1.94;
    }
    
    if (state == "Utah")
    {
        localRate = 0.99;
    }
    
    if (state == "Vermont")
    {
        localRate = 0.18;
    }
    
    if (state == "Virginia")
    {
        localRate = 0.35;
    }
    
    if (state == "Washington")
    {
        localRate = 2.67;
    }
    
    if (state == "West Virgnia")
    {
        localRate = 0.39;
    }
    
    if (state == "Wisconsin")
    {
        localRate = 0.44;
        
    }
    
    if (state == "Wyoming")
    {
        localRate = 1.36;
    }
    
    // if the levy tax value is not 0 for a state, then there is a corresponding if statement below to change that variable
    // otherwise it stays as 0
    if (state == "California"||
        state == "Virginia")
    {
        levy = 1.00;
    }
    
    if (state == "Utah")
    {
        levy = 1.25;
    }
    
    // if the state is not capitalized properly, spelled wrong, or not a real state, then output an error statement
    if (state != "Alabama" &&
        state != "Alaska" &&
        state != "Arizona" &&
        state != "Arkansas" &&
        state != "California" &&
        state != "Colorado" &&
        state != "Connecticut" &&
        state != "Delaware" &&
        state != "Florida" &&
        state != "Georgia" &&
        state != "Hawaii" &&
        state != "Idaho" &&
        state != "Illinois" &&
        state != "Indian" &&
        state != "Iowa" &&
        state != "Kansas" &&
        state != "Kentucky" &&
        state != "Louisiana" &&
        state != "Maine" &&
        state != "Maryland" &&
        state != "Massachusetts" &&
        state != "Michigan" &&
        state != "Minnesota" &&
        state != "Mississippi"&&
        state != "Missouri" &&
        state != "Montana" &&
        state != "Nebraska" &&
        state != "Nevada" &&
        state != "New Hampshire" &&
        state != "New Jersey" &&
        state != "New Mexico" &&
        state != "New York" &&
        state != "North Carolina" &&
        state != "North Dakota" &&
        state != "Ohio" &&
        state != "Oklahoma" &&
        state != "Oregon" &&
        state != "Pennsylvania" &&
        state != "Rhode Island" &&
        state != "South Carolina" &&
        state != "Tennessee" &&
        state != "Texas" &&
        state != "Utah" &&
        state != "Vermont" &&
        state != "Virginia" &&
        state != "Washington" &&
        state != "West Virginia" &&
        state != "Wisconsin" &&
        state != "Wyoming")
    {
        cout << "Invalid state!" << endl;
    }
    
    // using else if for following statements because we only want to return the first error
    // if the state is valid but the amount is not a number or it is less than or equal to 0, output an error statement
    else if (amount <= 0)
    {
        cout << "Invalid amount!" << endl;
    }
    
    //  if the state and amount are valid but the month is wrong type, not capitalized, spelled wrong, or not a month, output an error statement
    else if (month != "January" &&
            month != "February" &&
            month != "March" &&
            month != "April" &&
            month != "May" &&
            month != "June" &&
            month != "July" &&
            month != "August" &&
            month != "September" &&
            month != "October" &&
            month != "November" &&
            month != "December")
    {
        cout << "Invalid month!" << endl;
    }
    
    // if the state, amount, and month are valid but the day is not a number, less than 1, or greater than 31, output an error statement
    else if (day < 1 || day > 31)
    {
        cout << "Invalid day!" << endl;
    }
    
    // if the state, amount, month, and day are valid but the year is not a number, less than 1, or greater than 2025, output an error statement
    else if (year < 1 || year > 2025)
    {
        cout << "Invalid year!" << endl;
    }
    // if all the inputs are valid, then calculate the total they have to pay
    else
    {
        // variable that will represent total amount due
        double total;
        total = amount * (1+((stateRate + localRate + levy)/100));
        
        // if it is a free tax day, total is purchase amount as there is no tax
        if (state == "Alabama" &&
            month == "July" &&
            (day == 15 ||
             day == 16 ||
             day == 17))
        {
            total = amount;
        }
        
        if (state == "Arkansas" &&
            month == "August" &&
            (day == 6 ||
             day == 7 ))
        {
            total = amount;
        }
        
        if (state == "Connecticut" &&
            month == "August" &&
            (day == 21 ||
             day == 22 ||
             day == 23 ||
             day == 24 ||
             day == 25 ||
             day == 26 ||
             day == 27))
        {
            total = amount;
        }
        
        if (state == "Iowa" &&
            month == "August" &&
            (day == 5 ||
             day == 6 ))
        {
            total = amount;
        }
        
        if (state == "Maryland" &&
            month == "August" &&
            (day == 14 ||
             day == 15 ||
             day == 16 ||
             day == 17 ||
             day == 18 ||
             day == 19 ||
             day == 20))
        {
            total = amount;
        }
        
        if (state == "Massachusetts" &&
            month == "August" &&
            (day == 14 ||
             day == 15))
        {
            total = amount;
        }
        
        if (state == "Mississippi" &&
            month == "July" &&
            (day == 29 ||
             day == 30))
        {
            total = amount;
        }
        
        if (state == "Missouri" &&
            month == "April" &&
            (day == 19 ||
             day == 20 ||
             day == 21 ||
             day == 22 ||
             day == 23 ||
             day == 24 ||
             day == 25 ))
        {
            total = amount;
        }
        
        if ((state == "Nevada"||
             state == "Ohio"||
             state == "South Carolina"||
             state == "Texas"||
             state == "West Virginia") &&
             month == "August" &&
            (day == 5 ||
             day == 6 ||
             day == 7 ))
        {
            total = amount;
        }
        
        if (state == "Oklahoma" &&
            month == "August" &&
            (day == 6 ||
             day == 7 ||
             day == 8 ))
        {
            total = amount;
        }
        
        if (state == "Tennessee" &&
            month == "July" &&
            (day == 29 ||
             day == 30 ||
             day == 31 ))
        {
            total = amount;
        }
        
        // once the total is calculated output the total with two decimal places
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);
        cout << "Please pay a total of $" << total << endl;
    }
    return 0;
}
