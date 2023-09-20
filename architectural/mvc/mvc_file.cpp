#include <iostream>
#include <string>
#include <vector>

// Model (File System Structure)
class FileExplorerModel
{
public:
    struct FileSystemItem
    {
        std::string name;
        bool isDirectory;
        // Additional attributes like size, permissions, etc. can be added here

        FileSystemItem(const std::string &_name, bool _isDirectory) : name(_name), isDirectory(_isDirectory)
        {
        }
    };

private:
    std::vector<FileSystemItem> fileSystem;

public:
    FileExplorerModel()
    {
        // Initialize the file system with some example directories and files
        fileSystem.push_back(FileSystemItem("Folder1", true));
        fileSystem.push_back(FileSystemItem("Folder2", true));
        fileSystem.push_back(FileSystemItem("File1.txt", false));
        fileSystem.push_back(FileSystemItem("File2.txt", false));
    }

    // Methods to perform file operations (create, delete, copy, etc.) can be added here

    const std::vector<FileSystemItem> &getFileSystem() const
    {
        return fileSystem;
    }
};

// View (File System Structure Display)
class FileExplorerView
{
public:
    void displayFileSystem(const std::vector<FileExplorerModel::FileSystemItem> &fileSystem)
    {
        std::cout << "File System Structure:\n";
        for (const auto &item : fileSystem)
        {
            if (item.isDirectory)
            {
                std::cout << "[Folder] ";
            }
            else
            {
                std::cout << "[File] ";
            }
            std::cout << item.name << "\n";
        }
    }
};

// Controller (File Operations)
class FileExplorerController
{
private:
    FileExplorerModel model;
    FileExplorerView view;

public:
    // Methods to handle file operations can be added here

    void displayFileSystem()
    {
        view.displayFileSystem(model.getFileSystem());
    }
};

int main()
{
    FileExplorerController controller;

    controller.displayFileSystem();

    // Implement file operations and user interactions here

    return 0;
}
