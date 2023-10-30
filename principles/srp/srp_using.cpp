#include <fstream>
#include <iostream>
#include <string>

// Class responsible for reading a text file
class FileReader
{
public:
    explicit FileReader(const std::string &filename) : filename(filename)
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

private:
    std::string filename;
};

// Class responsible for writing files
class FileWriter
{
public:
    explicit FileWriter(const std::string &filename) : filename(filename)
    {
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
    FileReader reader("example.txt");
    std::string fileContent = reader.read();
    std::cout << "File Content:\n" << fileContent;

    FileWriter writer("example.txt");
    std::string newData = "This is new data.";
    writer.write(newData);
    std::cout << "File Content After Writing:\n" << reader.read();

    return 0;
}
