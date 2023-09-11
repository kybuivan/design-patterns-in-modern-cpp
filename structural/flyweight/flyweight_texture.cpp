#include <iostream>
#include <map>
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
    std::map<std::string, Texture *> textures;

public:
    Texture *getTexture(std::string textureType)
    {
        if (textures.find(textureType) == textures.end())
        {
            if (textureType == "Wood")
            {
                textures[textureType] = new WoodTexture();
            }
            else if (textureType == "Metal")
            {
                textures[textureType] = new MetalTexture();
            }
            else if (textureType == "Grass")
            {
                textures[textureType] = new GrassTexture();
            }
        }

        return textures[textureType];
    }
};

int main()
{
    TextureFactory factory;

    Texture *woodTexture = factory.getTexture("Wood");
    Texture *metalTexture = factory.getTexture("Metal");
    Texture *grassTexture = factory.getTexture("Grass");
    Texture *anotherWoodTexture = factory.getTexture("Wood");

    woodTexture->render();
    metalTexture->render();
    grassTexture->render();
    anotherWoodTexture->render();

    return 0;
}
