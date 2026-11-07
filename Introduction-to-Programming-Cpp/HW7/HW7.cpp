#include "HW7.hpp"

void Person::addFriend(const Person& p) {friends.insert(&p);}
void Person::delFriend(const Person& p) {friends.erase(&p);}

void Person::printFriends() const {
    for (const Person* p : friends) {
        std::cout << p->name << " ";
    }
    std::cout << std::endl;
}

bool Person::hasFriends() const {if(!friends.empty()) {return true;} else { return false; }}
bool Person::isFriendsWith(const Person& other) const {if (friends.count(&other)>0) {return true;} else {return false;}}

void deleteOneSidedFriendship(Person& p1, Person& p2) {
    if (p1.isFriendsWith(p2) && !p2.isFriendsWith(p1)) {
        p1.delFriend(p2);
    }
    else if (p2.isFriendsWith(p1) && !p1.isFriendsWith(p2)) {
        p2.delFriend(p1);
    }
}
