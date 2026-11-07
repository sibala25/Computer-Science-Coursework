#ifndef HW7_hpp
#define HW7_hpp

#include <iostream>
#include <string>
#include <unordered_set>

class Person {
public:
    std::string name;
    Person(const std::string& _name) : name(_name), friends() {}

    void addFriend(const Person& p);
    void delFriend(const Person& p);

    void printFriends() const;

    bool hasFriends()                       const;
    bool isFriendsWith(const Person& other) const;

private:
    std::unordered_set<const Person*> friends;
};

void deleteOneSidedFriendship(Person& p1, Person& p2);

#endif /* HW7_hpp */
