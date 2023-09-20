#include <iostream>
#include <memory>
#include <unordered_map>

// Abstract Prototype: MapSite
class MapSite
{
public:
    virtual std::shared_ptr<MapSite> Clone() = 0;
    virtual void Enter() = 0;
};

// Concrete Prototypes: Room, Door, Wall, Passage
class Room : public MapSite
{
public:
    std::shared_ptr<MapSite> Clone() override
    {
        return std::make_shared<Room>(*this);
    }

    void Enter() override
    {
        std::cout << "You entered a room." << std::endl;
    }
};

class Door : public MapSite
{
public:
    std::shared_ptr<MapSite> Clone() override
    {
        return std::make_shared<Door>(*this);
    }

    void Enter() override
    {
        std::cout << "You passed through a door." << std::endl;
    }
};

class Wall : public MapSite
{
public:
    std::shared_ptr<MapSite> Clone() override
    {
        return std::make_shared<Wall>(*this);
    }

    void Enter() override
    {
        std::cout << "You hit a wall." << std::endl;
    }
};

class Passage : public MapSite
{
public:
    std::shared_ptr<MapSite> Clone() override
    {
        return std::make_shared<Passage>(*this);
    }

    void Enter() override
    {
        std::cout << "You moved through a passage." << std::endl;
    }
};

// Client: CreateMaze
class MazeGame
{
public:
    MazeGame()
    {
        // Initialize prototypical objects
        prototypeRoom = std::make_shared<Room>();
        prototypeDoor = std::make_shared<Door>();
        prototypeWall = std::make_shared<Wall>();
        prototypePassage = std::make_shared<Passage>();
    }

    std::shared_ptr<MapSite> CreateMaze()
    {
        // Create maze using prototypical objects
        std::shared_ptr<MapSite> maze = prototypeRoom->Clone();

        std::shared_ptr<MapSite> room1 = prototypeRoom->Clone();
        std::shared_ptr<MapSite> room2 = prototypeRoom->Clone();
        std::shared_ptr<MapSite> door = prototypeDoor->Clone();
        std::shared_ptr<MapSite> passage = prototypePassage->Clone();

        // Customize and assemble the maze
        maze->Enter(); // Entering the maze

        // Add rooms, doors, walls, and passages as needed
        room1->Enter();
        room2->Enter();
        door->Enter();
        passage->Enter();

        // ... Customize the maze further ...

        return maze;
    }

private:
    std::shared_ptr<Room> prototypeRoom;
    std::shared_ptr<Door> prototypeDoor;
    std::shared_ptr<Wall> prototypeWall;
    std::shared_ptr<Passage> prototypePassage;
};

int main()
{
    MazeGame mazeGame;
    std::shared_ptr<MapSite> maze = mazeGame.CreateMaze();

    return 0;
}
