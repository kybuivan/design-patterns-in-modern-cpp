#include <fstream>
#include <iostream>
#include <string>

// Class responsible for reading a text file
class TextFileReader
{
public:
    explicit TextFileReader(const std::string &filename) : filename(filename)
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

int main()
{
    TextFileReader reader("example.txt");
    std::string fileContent = reader.read();

    std::cout << "File Content:\n" << fileContent;

    return 0;
}
