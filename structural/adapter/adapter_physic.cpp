#include <iostream>
#include <memory>
#include <string>

// Existing third-party physics engine with an incompatible interface
class ThirdPartyPhysicsEngine
{
public:
    ThirdPartyPhysicsEngine()
    {
    }

    void SimulatePhysics()
    {
        std::cout << "Simulating physics using the third-party engine." << std::endl;
    }

    void HandleCollision()
    {
        std::cout << "Handling collisions using the third-party engine." << std::endl;
    }
};

// Desired physics interface for the game engine
class GamePhysics
{
public:
    virtual void Simulate() = 0;
    virtual void HandleCollisions() = 0;
    virtual ~GamePhysics() = default;
};

// Adapter to make ThirdPartyPhysicsEngine compatible with GamePhysics
class PhysicsAdapter : public GamePhysics
{
public:
    PhysicsAdapter(std::shared_ptr<ThirdPartyPhysicsEngine> thirdPartyPhysics) : thirdPartyPhysics_(thirdPartyPhysics)
    {
    }

    void Simulate() override
    {
        thirdPartyPhysics_->SimulatePhysics();
    }

    void HandleCollisions() override
    {
        thirdPartyPhysics_->HandleCollision();
    }

private:
    std::shared_ptr<ThirdPartyPhysicsEngine> thirdPartyPhysics_;
};

// Game engine using the adapted physics engine
class GameEngine
{
public:
    GameEngine(std::shared_ptr<GamePhysics> physics) : physics_(physics)
    {
    }

    void RunGame()
    {
        physics_->Simulate();
        physics_->HandleCollisions();
        std::cout << "Game running with adapted physics." << std::endl;
    }

private:
    std::shared_ptr<GamePhysics> physics_;
};

int main()
{
    auto thirdPartyPhysics = std::make_shared<ThirdPartyPhysicsEngine>();
    auto adapter = std::make_shared<PhysicsAdapter>(thirdPartyPhysics);

    GameEngine game(adapter);
    game.RunGame();

    return 0;
}
