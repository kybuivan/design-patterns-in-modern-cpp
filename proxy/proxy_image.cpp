#include <iostream>
#include <string>

class Image
{
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

class RealImage : public Image
{
private:
    std::string file;

public:
    RealImage(std::string file) : file(file)
    {
        loadFromDisk(file);
    }

    void display()
    {
        std::cout << "Displaying " << file << std::endl;
    }

    void loadFromDisk(std::string file)
    {
        std::cout << "Loading " << file << " from disk" << std::endl;
    }
};

class ProxyImage : public Image
{
private:
    RealImage *realImage;
    std::string file;

public:
    ProxyImage(std::string file) : file(file)
    {
        realImage = nullptr;
    }

    void display()
    {
        if (!realImage)
        {
            realImage = new RealImage(file);
        }
        realImage->display();
    }
};

int main()
{
    Image *image = new ProxyImage("test.jpg");
    image->display();

    return 0;
}
