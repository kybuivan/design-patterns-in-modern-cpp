#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abstract Data class
class Data
{
public:
    virtual ~Data() = default;
    virtual void display() const = 0;
};

// Concrete Data class
class FileData : public Data
{
public:
    explicit FileData(const std::string &file_name) : file_name_(file_name)
    {
    }

    void display() const override
    {
        std::cout << "File Data: " << file_name_ << std::endl;
    }

private:
    std::string file_name_;
};

// Abstract Decorator class
class DataDecorator : public Data
{
public:
    explicit DataDecorator(std::shared_ptr<Data> data) : data_(data)
    {
    }

    void display() const override
    {
        data_->display();
    }

protected:
    std::shared_ptr<Data> data_;
};

// Concrete Decorator class for Encryption
class Encryption : public DataDecorator
{
public:
    explicit Encryption(std::shared_ptr<Data> data) : DataDecorator(data)
    {
    }

    void display() const override
    {
        std::cout << "Encrypted ";
        data_->display();
    }
};

// Concrete Decorator class for Compression
class Compression : public DataDecorator
{
public:
    explicit Compression(std::shared_ptr<Data> data) : DataDecorator(data)
    {
    }

    void display() const override
    {
        std::cout << "Compressed ";
        data_->display();
    }
};

// Client code
int main()
{
    std::shared_ptr<Data> data = std::make_shared<FileData>("sample.txt");
    data->display();

    std::shared_ptr<Data> encrypted_data = std::make_shared<Encryption>(data);
    encrypted_data->display();

    std::shared_ptr<Data> compressed_data = std::make_shared<Compression>(encrypted_data);
    compressed_data->display();

    return 0;
}
