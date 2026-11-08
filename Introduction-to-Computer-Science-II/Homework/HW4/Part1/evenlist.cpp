void removeEven(list<int>& li)
{
    list<int> :: iterator it;
    it = li.begin();
    while (it != li.end()) {
        if (*it % 2 == 0) {                             // if it is even, erase
            it = li.erase(it);
        }
        else {                                          // if it is odd, just it++
            it++;
        }
    }
}
