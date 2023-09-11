#include <iostream>
#include <memory>
#include <string>

class LightSwitch;

struct State
{
    virtual ~State() = default;

    virtual void on(LightSwitch *ls)
    {
        std::cout << "Light is already on\n";
    }
    virtual void off(LightSwitch *ls)
    {
        std::cout << "Light is already off\n";
    }
};

struct OnState : State
{
    OnState()
    {
        std::cout << "Light turned on\n";
    }

    void off(LightSwitch *ls) override;
};

struct OffState : State
{
    OffState()
    {
        std::cout << "Light turned off\n";
    }

    void on(LightSwitch *ls) override;
};

class LightSwitch
{
    std::unique_ptr<State> state;

public:
    LightSwitch() : state(std::make_unique<OffState>())
    {
    }
    void set_state(State *state)
    {
        this->state.reset(state);
    }
    void on()
    {
        state->on(this);
    }
    void off()
    {
        state->off(this);
    }
};

void OnState::off(LightSwitch *ls)
{
    std::cout << "Switching light off...\n";
    ls->set_state(new OffState());
}

void OffState::on(LightSwitch *ls)
{
    std::cout << "Switching light on...\n";
    ls->set_state(new OnState());
}

int main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();

    return 0;
}
