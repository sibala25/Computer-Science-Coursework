#include "HW7.hpp"
using namespace std;


int main() {

    Person p1(" Severus");
    Person p2("   Lorde");
    Person p3("Scabbers");
    Person p4("   Moony");
    Person p5(" Padfoot");

    // bffl's
    p4.addFriend(p5);
    p5.addFriend(p4);

    // don't be friends with rat man
    p4.addFriend(p3);
    p5.addFriend(p3);

    // don't be friends with snake man
    p3.addFriend(p2);

    // don't be friends with grease man
    p2.addFriend(p1);


    unordered_set<Person*> people = {&p1, &p2, &p3, &p4, &p5};
    cout << "Results:" << endl << endl;


    for (const Person* p : people) {
        if (p->hasFriends()) {
            cout << p->name << " thinks their friends are: ";
            p->printFriends();
        }
        else {
            cout << p->name << " doesn't think they have friends." << endl;
        }
    }
    cout << endl;


    for (Person* p1 : people) {
        for (Person* p2 : people) {
            deleteOneSidedFriendship(*p1, *p2);
        }
    }


    for (const Person* p : people) {
        if (p->hasFriends()) {
            cout << p->name << "\'s genuine friends are: ";
            p->printFriends();
        }
        else {
            cout << p->name << " has no genuine friends." << endl;
        }
    }
    cout << endl;


    return 0;
}
