#include <iostream>
#include <string>

using namespace std;

class Game {
public:
    virtual void start() = 0;
    virtual void play() = 0;
    virtual void end() = 0;
    void run() {
        start();
        while (isPlaying()) {
            play();
        }
        end();
    }
    virtual bool isPlaying() { return true; }
};

class Chess : public Game {
public:
    void start() override {
        cout << "Starting a game of Chess" << endl;
    }
    void play() override {
        cout << "Playing Chess" << endl;
    }
    void end() override {
        cout << "Ending a game of Chess" << endl;
    }
};

class Checkers : public Game {
public:
    void start() override {
        cout << "Starting a game of Checkers" << endl;
    }
    void play() override {
        cout << "Playing Checkers" << endl;
    }
    void end() override {
        cout << "Ending a game of Checkers" << endl;
    }
};

int main() {
    Game* game = new Chess();
    game->run();

    cout << endl;

    game = new Checkers();
    game->run();

    return 0;
}
