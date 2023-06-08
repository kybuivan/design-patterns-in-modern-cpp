#include <iostream>
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
    explicit DataDecorator(Data *data) : data_(data)
    {
    }

    void display() const override
    {
        data_->display();
    }

protected:
    Data *data_;
};

// Concrete Decorator class for Encryption
class Encryption : public DataDecorator
{
public:
    explicit Encryption(Data *data) : DataDecorator(data)
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
    explicit Compression(Data *data) : DataDecorator(data)
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
    Data *data = new FileData("sample.txt");
    data->display();

    Data *encrypted_data = new Encryption(data);
    encrypted_data->display();

    Data *compressed_data = new Compression(encrypted_data);
    compressed_data->display();

    return 0;
}
