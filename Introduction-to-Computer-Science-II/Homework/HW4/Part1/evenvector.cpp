void removeEven(vector<int>& v)
{
    vector<int> :: iterator it;
    it = v.begin();
    while (it != v.end()) {
        if (*it % 2 == 0) {                             // if it is even, erase
            it = v.erase(it);
        }
        else {                                          // if it is odd, just it++
                it++;
        }
    }
}
