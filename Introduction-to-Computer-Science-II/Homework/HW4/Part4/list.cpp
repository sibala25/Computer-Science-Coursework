void listAll(const File* f, string path)  // two-parameter overload
{
    if (f == nullptr) {
        return;
    }
    
    
    path = path + "/" + f->name();
    cout << path << endl;
    
    if (f->files() == nullptr) {
        return;
    }
    
    for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++) {
        listAll((*it), path);
    }
}
