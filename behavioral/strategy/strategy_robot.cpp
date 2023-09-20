#include <iostream>
#include <string>

// Strategy Interface
class IBehaviour
{
public:
    virtual int moveCommand() = 0;
};

// Concrete Strategies
class AggressiveBehaviour : public IBehaviour
{
public:
    int moveCommand() override
    {
        std::cout << "\tAggressive Behaviour: if find another robot attack it" << std::endl;
        return 1;
    }
};

class DefensiveBehaviour : public IBehaviour
{
public:
    int moveCommand() override
    {
        std::cout << "\tDefensive Behaviour: if find another robot run from it" << std::endl;
        return -1;
    }
};

class NormalBehaviour : public IBehaviour
{
public:
    int moveCommand() override
    {
        std::cout << "\tNormal Behaviour: if find another robot ignore it" << std::endl;
        return 0;
    }
};

// Context Class
class Robot
{
private:
    IBehaviour *behaviour;
    std::string name;

public:
    Robot(const std::string &n) : name(n), behaviour(nullptr)
    {
    }

    void setBehaviour(IBehaviour *behaviour)
    {
        this->behaviour = behaviour;
    }

    IBehaviour *getBehaviour()
    {
        return behaviour;
    }

    void move()
    {
        std::cout << name << ": Based on current position, the behaviour object decides the next move:" << std::endl;
        int command = behaviour->moveCommand();
        // Send the command to mechanisms...
        std::cout << "\tThe result returned by the behaviour object is sent to the movement mechanisms for the robot '" << name << "'" << std::endl;
    }

    std::string getName()
    {
        return name;
    }

    void setName(const std::string &n)
    {
        name = n;
    }
};

int main()
{
    Robot r1("Big Robot");
    Robot r2("George v.2.1");
    Robot r3("R2");

    r1.setBehaviour(new AggressiveBehaviour());
    r2.setBehaviour(new DefensiveBehaviour());
    r3.setBehaviour(new NormalBehaviour());

    r1.move();
    r2.move();
    r3.move();

    std::cout << "\nNew behaviours:" << std::endl;
    std::cout << "\t'Big Robot' gets really scared," << std::endl;
    std::cout << "\t'George v.2.1' becomes really mad because it's always attacked by other robots," << std::endl;
    std::cout << "\tand R2 keeps its calm" << std::endl;

    r1.setBehaviour(new DefensiveBehaviour());
    r2.setBehaviour(new AggressiveBehaviour());

    r1.move();
    r2.move();
    r3.move();

    return 0;
}
