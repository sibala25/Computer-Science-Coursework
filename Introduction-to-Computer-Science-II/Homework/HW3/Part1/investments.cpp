class Investment;
class Painting;
class Stock;
class House;

class Investment {
    public:
        Investment(const string& name, int price);
        string name() const;
        int purchasePrice() const;
        virtual string description() const = 0;
        virtual bool fungible() const;
        virtual ~Investment();
    private:
        string m_name;
        int m_price;
};

Investment::Investment(const string& name, int price) : m_name(name),m_price(price) {}
string Investment::name() const { return m_name; }
int Investment::purchasePrice() const { return m_price; }
bool Investment::fungible() const { return false; }
Investment::~Investment() {}


class Painting : public Investment {
    public:
        Painting(const string& name, int price);
        string description() const;
        ~Painting();
};

Painting::Painting(const string& name, int price) : Investment(name,price) {}
string Painting::description() const { return "painting"; }
Painting::~Painting() {
    cout << "Destroying " << name() << ", a painting" << endl;
}

class Stock : public Investment {
    public:
        Stock(const string& name, int price, string nickname);
        string description() const;
        bool fungible() const;
        ~Stock();
    private:
        string m_shortname;
};

Stock::Stock(const string& name, int price, string nickname) : Investment(name,price), m_shortname(nickname) {}
string Stock::description() const { return "stock trading as " + m_shortname; }
bool Stock::fungible() const { return true; }
Stock::~Stock() {
    cout << "Destroying " << name() << ", a stock holding" << endl;
}

class House : public Investment {
    public:
        House(const string& name, int price);
        string description() const;
        ~House();
};

House::House(const string& name, int price) : Investment(name,price) {}
string House::description() const { return "house"; }
House::~House() {
    cout << "Destroying the house " << name() << endl;
}
