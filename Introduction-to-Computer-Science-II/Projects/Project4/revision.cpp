//  Project4

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

// nodes of hashmap
struct info {
    string sequence;
    int offset;
    info* next;
};

// hashmap class
class HashTable {
public:
    // constructor
    HashTable();
    
    // destructor
    ~HashTable();

    // mapping fn
    unsigned int mapFn(const string& seq);
    
    // insertion
    void insert(const string& seq, int offset);
    
    // search; also gives offset
    bool contains(const string& seq, vector<int>& offset);
    
private:
    // vector of linked lists
    vector<info*> table;
    // check this
    static const int size = 11161;          // prime number to reduce collisions


    
};

// constructor
HashTable::HashTable() {
    table.resize(size);
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

// destructor
HashTable::~HashTable() {
    for (int i = 0; i < size; i++) {
        info* curr = table[i];
        while (curr != nullptr) {
            info* next = curr->next;
            delete curr;
            curr = next;
        }
        table[i] = nullptr;
    }
}

// mapping fn
unsigned int HashTable::mapFn(const string& seq) {
    hash<string> str_hash;
    unsigned int hashVal = str_hash(seq);                   // hash string sequence
    unsigned int bucketNum = hashVal % size;                // assign a bucket number and return it
    return bucketNum;
}

// insertion
void HashTable::insert(const string& seq, int offset) {
    int bucket = mapFn(seq);
    info *newGuy = new info{seq, offset, nullptr};          // create a new info node to insert
    
    if (table[bucket] == nullptr) {                         // if the bucket it goes in is empty, just add it
        table[bucket] = newGuy;
    } 
    else {
        info* curr = table[bucket];                         // if bucket !empty, traverse to end of list and insert new node
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newGuy;
    }
}

// search
bool HashTable::contains(const string& seq, vector<int>& offset) {
    int bucket = mapFn(seq);
    if (table[bucket] == nullptr) {                         // if bucket empty, sequence is not in it
        return false;
    }
    else {
        info* curr = table[bucket];
        bool returnIfFound = false;
        while (curr != nullptr) {                           // traverse through list and add each offset where the seq is found into vector
            if (curr->sequence == seq) {
                offset.push_back(curr->offset);
                returnIfFound = true;
            }
            curr = curr->next;
        }
        return returnIfFound;                               // returns true if the sequence is found at least once
    }
}

void pickDelim(const string& substring, char &delim);
void addOutput(ostream& frevision, const string& substring, char &delim);
void createRevision(istream& fold, istream& fnew, ostream& frevision);
bool getInt(istream& inf, int& n);
bool getCommand(istream& inf, char& cmd, char& delim, int& length, int& offset);
bool revise(istream& fold, istream& frevision, ostream& fnew);

// function to pick a delimiter for substring if given one is in it
void pickDelim(const string& substring, char &delim) {
    char orig = delim;                                                   // store original delim
    while (substring.find(delim) != string::npos && delim <= '~') {      // while current delim is in string or we tried all printable ones
        delim++;
        if (delim == '~') {                                              // if we went through all, set as orig delim and break
            delim = '!';
            break;
        }
    }
    if (delim == orig) {                                                 // have to use non-printable ASCII chars
        for (char c = 1; c < ' '; c++) {
            if (substring.find(c) == string::npos) {                     // once you find one not in the string, use it as the delimiter and break
                delim = c;                                               // otherwise, leaves it as original '!'
                break;
            }
        }
    }
}

// function for adding "add" instructions when original delim is invalid
void addOutput(ostream& frevision, const string& substring, char &delim) {
    char ogDelim = delim;                                                      // store original delim (since passed by ref)
    pickDelim(substring, delim);                                               // pick delim for this substring
    if (delim != '!') {
        frevision << "+" << delim << substring << delim;                       // if a delimiter was found, just use it and add instruction
    } else {                                                                   // if a valid delim was not found, split substring
        size_t half = substring.length() / 2;
        string one = substring.substr(0,half);
        string two = substring.substr(half);
        
        addOutput(frevision, one, delim);                                      // and try to find a valid delim for each of those
        addOutput(frevision, two, delim);
    }
    delim = ogDelim;                                                           // restore delim for future calls
}


void createRevision(istream& fold, istream& fnew, ostream& frevision) {
    char s;
    string oldfile;
    while (fold.get(s)) {                                   // reading old file into string
        oldfile += s;
    }
    
    char t;
    string newfile;
    while (fnew.get(t)) {                                   // reading new file into string
        newfile += t;
    }
    
    HashTable oldTable;
    int substrLen = 8;                                      // length of sequences to search and hash
                       
    for (int i = 0; i < oldfile.length() - substrLen; i++) {
        string seq = oldfile.substr(i, substrLen);          // insert sequences from old file into hashtable
        oldTable.insert(seq,i);
    }
        
    char delim = '!';                                       // default delim
   
    int j = 0;                                              // offset tracker in new file

    while (j < newfile.length()) {
        string seq = newfile.substr(j, substrLen);          // starting with the first 8-length new sequence, search for them in old file
        vector<int> offsets;
        int bestOffset = -1;
        int bestMatchLen = 0;

        bool found = oldTable.contains(seq, offsets);
        if (found) {                                        // if sequence found, we need to make a copy instruction
            for (int offset : offsets) {
                int matchLen = substrLen;
                
                // generate length of each matching sequence that was found using offset vector
                while (j + matchLen < newfile.length() && oldfile[offset+matchLen] == newfile[j+matchLen]) {
                    matchLen++;
                }
                if (matchLen > bestMatchLen) {              // find which offset gives the best/longest match length for top efficiency
                    bestMatchLen = matchLen;
                    bestOffset = offset;
                }
            }
        }
        if (bestMatchLen >= substrLen) {
            frevision << "#" << bestOffset << "," << bestMatchLen;      // add copy instruction
            j += bestMatchLen;
        }
        else {                                                          // if not found, must generate add instruction
            int start = j;
            while (j < newfile.length() && !oldTable.contains(newfile.substr(j, substrLen),offsets)) {     // calculate how much of string is new
                j++;                                                                                       // and therefore needs to be added
            }
            string substring = newfile.substr(start, j - start);
                         
            if (substring.find(delim) != string::npos) {                  // if delim is in substring, call fn to find another
                addOutput(frevision, substring, delim);
            } else {
                frevision << "+" << delim << substring << delim;          // if it is valid, add add instruction to revision file
            }
        }
        
        // once there are 7 or less characters left in the new string, just add them as an add instruction
        // (because better efficiency in terms of size and harder to find in table)
        if (newfile.length()-j-1 < substrLen) {
            if (newfile.substr(j).find(delim) != string::npos) {          // if delim in substring, call fn to find another
                addOutput(frevision, newfile.substr(j), delim);
            }
            else {                                                        // otherwise use '!'
                frevision << "+" << delim << newfile.substr(j) << delim;
            }
            break;                                                        // end of newfile string so break
        }
        
    }
}

bool getInt(istream& inf, int& n)                                                       // from spec
    {
        char ch;
        if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
            return false;
        inf.unget();
        inf >> n;
        return true;
    }

bool getCommand(istream& inf, char& cmd, char& delim, int& length, int& offset)         // from spec
    {
        if (!inf.get(cmd))
        {
            cmd = 'x';  // signals end of file
            return true;
        }
        switch (cmd)
        {
          case '+':
            return inf.get(delim).good();
          case '#':
            {
                char ch;
                return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
            }
          case '\r':
          case '\n':
            return true;
        }
        return false;
    }

bool revise(istream& fold, istream& frevision, ostream& fnew) {
    char s;                                                                             // read oldfile into string
    string oldfile;
    while (fold.get(s)) {
        oldfile += s;
    }
    
    // defining parameters to pass by reference
    char cmd;
    char delim;
    int length;
    int offset;
    
    while (getCommand(frevision, cmd, delim, length, offset)) {                        // go through revise file string
        if (cmd == '+') {                                                              // add everything from add instruction to new file
            char c;                                                                    // until delim is found again
            while (frevision.get(c) && c != delim) {
                fnew << c;
            }
        }
        else if (cmd == '#') {
            if (offset < 0 || length <= 0 || offset+length > oldfile.length()) {       // ensure copy instruction has valid offset and length
                return false;
            }
            else {
                fnew << oldfile.substr(offset, length);                                // if it does, copy substring from old file
            }
        }
        else if (cmd == 'x') {                                                         // end of string reached, return true
            return true;
        }
        else {
            return false;                                                              // invalid command found
        }
    }

    return false;
}


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;

bool runtest(string oldName, string newName, string revisionName, string newName2)
{
    if (revisionName == oldName  ||  revisionName == newName  ||
        newName2 == oldName  ||  newName2 == revisionName  ||
            newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream revisionFile(revisionName, ios::binary);
    if (!revisionFile)
    {
        cerr << "Cannot create " << revisionName << endl;
        return false;
    }
    createRevision(oldFile, newFile, revisionFile);
    revisionFile.close();

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream revisionFile2(revisionName, ios::binary);
    if (!revisionFile2)
    {
        cerr << "Cannot read the " << revisionName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(revise(oldFile, revisionFile2, newFile2));
    newFile2.close();

    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {
        cerr << newName2 << " is not identical to " << newName
                 << "; test FAILED" << endl;
        return false;
    }
    return true;
}

int main()
{
    assert(runtest("/Users/aashnasibal/Downloads/CS32/Project4/Project4/warandpeace1.txt",
                   "/Users/aashnasibal/Downloads/CS32/Project4/Project4/warandpeace2.txt",
                   "/Users/aashnasibal/Downloads/CS32/Project4/Project4/myrevisionfile.txt",
                   "/Users/aashnasibal/Downloads/CS32/Project4/Project4/mynewfile2.txt"));
    cerr << "Test PASSED" << endl;
}
