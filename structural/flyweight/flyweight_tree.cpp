#include <iostream>
#include <memory>
#include <vector>

// The Flyweight interface defines the shared properties of Tree objects.
class Tree
{
public:
    virtual void render(int x, int y) = 0;
};

// ConcreteFlyweight represents the shared properties of a tree.
class TreeType : public Tree
{
public:
    std::string name;
    std::string texture;

public:
    TreeType(const std::string &name, const std::string &texture) : name(name), texture(texture)
    {
    }

    void render(int x, int y) override
    {
        std::cout << "Rendering " << name << " tree at (" << x << ", " << y << ") with texture: " << texture
                  << std::endl;
    }
};

// TreeFactory manages the creation and retrieval of TreeType objects (Flyweights).
class TreeFactory
{
private:
    std::vector<std::shared_ptr<TreeType>> treeTypes;

public:
    std::shared_ptr<TreeType> getTreeType(const std::string &name, const std::string &texture)
    {
        // Check if the TreeType with the given name already exists.
        for (const auto &treeType : treeTypes)
        {
            if (treeType->name == name)
            {
                return treeType;
            }
        }

        // If not, create a new TreeType and add it to the collection.
        auto newTreeType = std::make_shared<TreeType>(name, texture);
        treeTypes.push_back(newTreeType);
        return newTreeType;
    }
};

// Client code represents individual trees in the game.
class TreeObject
{
private:
    int x;
    int y;
    std::shared_ptr<TreeType> treeType;

public:
    TreeObject(int x, int y, std::shared_ptr<TreeType> treeType) : x(x), y(y), treeType(treeType)
    {
    }

    void render()
    {
        treeType->render(x, y);
    }
};

int main()
{
    // Create a TreeFactory to manage TreeTypes (Flyweights).
    TreeFactory treeFactory;

    // Create different types of trees (Flyweights).
    auto oakTree = treeFactory.getTreeType("Oak", "oak_texture.png");
    auto pineTree = treeFactory.getTreeType("Pine", "pine_texture.png");

    // Create individual TreeObjects with shared Flyweights.
    std::vector<std::shared_ptr<TreeObject>> trees;
    trees.push_back(std::make_shared<TreeObject>(10, 20, oakTree));
    trees.push_back(std::make_shared<TreeObject>(30, 40, pineTree));
    trees.push_back(std::make_shared<TreeObject>(50, 60, oakTree));

    // Render the trees, sharing textures efficiently.
    for (const auto &tree : trees)
    {
        tree->render();
    }

    return 0;
}
