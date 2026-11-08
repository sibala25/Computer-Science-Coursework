void removeBad(vector<Restaurant*>& v)
{
    vector<Restaurant*> :: iterator it;
    it = v.begin();
    while (it != v.end()) {
        if ((*it)->stars() <= 2) {
            delete (*it);
            it = v.erase(it);
        }
        else {
            it++;
        }
    }
}
