#include <iostream>
#include <memory>
#include <string>

class GameAsset
{
private:
    std::string assetName;
    // Simulated loaded asset data
    std::shared_ptr<std::string> assetData;

public:
    GameAsset(const std::string &name) : assetName(name), assetData(nullptr)
    {
    }

    // Function to load the asset data, creating it if it doesn't exist yet
    std::shared_ptr<std::string> loadAsset()
    {
        if (!assetData)
        {
            // Simulate loading the asset data from a file or resource
            assetData = std::make_shared<std::string>("Data for asset: " + assetName);
            std::cout << "Loaded asset: " << assetName << std::endl;
        }
        return assetData;
    }
};

int main()
{
    // Create a game asset object
    GameAsset asset1("Texture1");

    // Load the asset, which will create the asset data
    std::shared_ptr<std::string> assetData1 = asset1.loadAsset();

    // Load the asset again, which won't create a new asset data
    std::shared_ptr<std::string> assetData2 = asset1.loadAsset();

    // Create another game asset object
    GameAsset asset2("Sound1");

    // Load the second asset, which will create its asset data
    std::shared_ptr<std::string> assetData3 = asset2.loadAsset();

    return 0;
}
