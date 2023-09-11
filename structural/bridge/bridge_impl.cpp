#include <iostream>
#include <memory>
#include <string>

class Pimpl;

class Database
{
public:
    Database();
    ~Database();
    void connect(const std::string &url);
    void disconnect();
    void execute(const std::string &query);

private:
    std::unique_ptr<Pimpl> pimpl;
};

class Pimpl
{
public:
    Pimpl()
    {
        std::cout << "Pimpl constructor" << std::endl;
    }
    ~Pimpl()
    {
        std::cout << "Pimpl destructor" << std::endl;
    }
    void connect(const std::string &url)
    {
        std::cout << "Connecting to " << url << std::endl;
    }
    void disconnect()
    {
        std::cout << "Disconnecting" << std::endl;
    }
    void execute(const std::string &query)
    {
        std::cout << "Executing " << query << std::endl;
    }
};

Database::Database() : pimpl(std::make_unique<Pimpl>())
{
}
Database::~Database() = default;

void Database::connect(const std::string &url)
{
    pimpl->connect(url);
}

void Database::disconnect()
{
    pimpl->disconnect();
}

void Database::execute(const std::string &query)
{
    pimpl->execute(query);
}

int main()
{
    Database db;
    db.connect("localhost");
    db.execute("SELECT * FROM users");
    db.disconnect();
    return 0;
}
