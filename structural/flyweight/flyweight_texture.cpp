#include <iostream>
#include <map>
#include <memory> // Include for std::shared_ptr
#include <string>

class Texture
{
public:
    virtual ~Texture() = default;
    virtual void render() = 0;
};

class WoodTexture : public Texture
{
public:
    void render() override
    {
        std::cout << "Rendering wood texture." << std::endl;
    }
};

class MetalTexture : public Texture
{
public:
    void render() override
    {
        std::cout << "Rendering metal texture." << std::endl;
    }
};

class GrassTexture : public Texture
{
public:
    void render() override
    {
        std::cout << "Rendering grass texture." << std::endl;
    }
};

class TextureFactory
{
private:
    std::map<std::string, std::shared_ptr<Texture>> textures;

public:
    std::shared_ptr<Texture> getTexture(std::string textureType)
    {
        if (textures.find(textureType) == textures.end())
        {
            if (textureType == "Wood")
            {
                textures[textureType] = std::make_shared<WoodTexture>();
            }
            else if (textureType == "Metal")
            {
                textures[textureType] = std::make_shared<MetalTexture>();
            }
            else if (textureType == "Grass")
            {
                textures[textureType] = std::make_shared<GrassTexture>();
            }
        }

        return textures[textureType];
    }
};

int main()
{
    TextureFactory factory;

    auto woodTexture = factory.getTexture("Wood");
    auto metalTexture = factory.getTexture("Metal");
    auto grassTexture = factory.getTexture("Grass");
    auto anotherWoodTexture = factory.getTexture("Wood");

    woodTexture->render();
    metalTexture->render();
    grassTexture->render();
    anotherWoodTexture->render();

    return 0;
}
