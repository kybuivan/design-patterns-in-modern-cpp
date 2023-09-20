#include <iostream>
#include <memory>
#include <string>

// Subject Interface
class Image
{
public:
    virtual void showImage() = 0;
};

// RealSubject
class HighResolutionImage : public Image
{
private:
    std::string imageFilePath;

public:
    HighResolutionImage(const std::string &filePath) : imageFilePath(filePath)
    {
        loadImage(imageFilePath);
    }

    void loadImage(const std::string &filePath)
    {
        // Load Image from disk into memory (heavy and costly operation)
        std::cout << "Loading image from " << filePath << std::endl;
    }

    void showImage() override
    {
        // Actual Image rendering logic
        std::cout << "Displaying high-resolution image" << std::endl;
    }
};

// Proxy
class ImageProxy : public Image
{
private:
    std::string imageFilePath;
    std::shared_ptr<Image> proxifiedImage;

public:
    ImageProxy(const std::string &filePath) : imageFilePath(filePath), proxifiedImage(nullptr)
    {
    }

    void showImage() override
    {
        // Create the Image Object only when the image is required to be shown
        if (!proxifiedImage)
        {
            proxifiedImage = std::make_shared<HighResolutionImage>(imageFilePath);
        }

        // Now call showImage on realSubject
        proxifiedImage->showImage();
    }
};

int main()
{
    // Create the 3 image proxies using smart pointers
    std::shared_ptr<Image> highResolutionImage1 = std::make_shared<ImageProxy>("sample/veryHighResPhoto1.jpeg");
    std::shared_ptr<Image> highResolutionImage2 = std::make_shared<ImageProxy>("sample/veryHighResPhoto2.jpeg");
    std::shared_ptr<Image> highResolutionImage3 = std::make_shared<ImageProxy>("sample/veryHighResPhoto3.jpeg");

    // Assume the user clicks on Image one item in a list
    // This would cause the program to call showImage() for that image only
    // Note that in this case only image one was loaded into memory
    highResolutionImage1->showImage();

    // Consider using the high-resolution image object directly
    std::shared_ptr<Image> highResolutionImageNoProxy1 = std::make_shared<HighResolutionImage>("sample/veryHighResPhoto1.jpeg");
    std::shared_ptr<Image> highResolutionImageNoProxy2 = std::make_shared<HighResolutionImage>("sample/veryHighResPhoto2.jpeg");
    std::shared_ptr<Image> highResolutionImageNoProxy3 = std::make_shared<HighResolutionImage>("sample/veryHighResPhoto3.jpeg");

    // Assume the user selects image two item from images list
    highResolutionImageNoProxy2->showImage();

    // Note that in this case all images have been loaded into memory
    // and not all have been actually displayed
    // This is a waste of memory resources

    return 0;
}
