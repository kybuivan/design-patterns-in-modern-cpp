#include <fstream>
#include <iostream>
#include <string>

// Class that violates SRP by having multiple responsibilities
class FileManager
{
public:
    FileManager(const std::string &filename) : filename(filename)
    {
    }

    std::string read()
    {
        std::string content;
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                content += line + "\n";
            }
            file.close();
        }
        else
        {
            std::cout << "Error: Unable to open file." << std::endl;
        }
        return content;
    }

    void write(const std::string &content)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            file << content;
            file.close();
        }
        else
        {
            std::cout << "Error: Unable to open file for writing." << std::endl;
        }
    }

private:
    std::string filename;
};

int main()
{
    FileManager manager("example.txt");

    // This class violates SRP by handling both reading and writing operations.
    std::string fileContent = manager.read();
    std::cout << "File Content:\n" << fileContent;

    std::string newData = "This is new data.";
    manager.write(newData);
    std::cout << "File Content After Writing:\n" << manager.read();

    return 0;
}
