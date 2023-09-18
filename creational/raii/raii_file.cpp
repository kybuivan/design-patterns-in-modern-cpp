#include <fstream>
#include <iostream>
#include <string>

class FileRAII
{
private:
    std::ofstream fileStream;

public:
    FileRAII(const std::string &filename)
    {
        fileStream.open(filename);
        if (!fileStream.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    ~FileRAII()
    {
        if (fileStream.is_open())
        {
            fileStream.close();
            std::cout << "File closed." << std::endl;
        }
    }

    // You can add other file-related functions here, like writing or reading data
};

int main()
{
    try
    {
        FileRAII file("example.txt");

        // Perform file operations here

        // The file will be automatically closed when the 'file' object goes out of scope
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 'file' has gone out of scope, and the destructor has closed the file
    return 0;
}
