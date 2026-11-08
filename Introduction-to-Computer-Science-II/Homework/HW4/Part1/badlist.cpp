void removeBad(list<Restaurant*>& li)
{
    list<Restaurant*> :: iterator it;
    it = li.begin();
    while (it != li.end()) {
        if ((*it)->stars() <= 2) {
            delete (*it);
            it = li.erase(it);
        }
        else {
            it++;
        }
    }
}
