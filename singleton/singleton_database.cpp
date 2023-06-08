#include <iostream>
#include <mutex>
#include <string>

class Database
{
private:
    static Database *instance;
    static std::mutex mutex;

    std::string name;
    int version;

    Database(const std::string &name, int version) : name(name), version(version)
    {
    }

    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

public:
    static Database *getInstance(const std::string &name, int version)
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr)
        {
            instance = new Database(name, version);
        }
        return instance;
    }

    void query(const std::string &sql)
    {
        std::cout << "Executing SQL query: " << sql << " on database: " << name
                  << " version: " << version << std::endl;
    }

    ~Database()
    {
        std::cout << "Destroying database instance: " << name << " version: " << version
                  << std::endl;
    }
};

Database *Database::instance = nullptr;
std::mutex Database::mutex;

int main()
{
    Database *db1 = Database::getInstance("MyDB", 1);
    db1->query("SELECT * FROM users");

    Database *db2 = Database::getInstance("MyDB", 1);
    db2->query("UPDATE users SET name='John Doe' WHERE id=1");

    return 0;
}
