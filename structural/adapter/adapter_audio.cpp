#include <iostream>
#include <string>

// Existing audio library with an incompatible interface
class ThirdPartyAudio
{
public:
    ThirdPartyAudio(const std::string &audioFile) : audioFile_(audioFile)
    {
    }

    void PlayAudio()
    {
        std::cout << "Playing audio file: " << audioFile_ << std::endl;
    }

    void StopAudio()
    {
        std::cout << "Stopping audio file: " << audioFile_ << std::endl;
    }

private:
    std::string audioFile_;
};

// Desired audio interface for the game
class GameAudio
{
public:
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual ~GameAudio() = default;
};

// Adapter to make ThirdPartyAudio compatible with GameAudio
class AudioAdapter : public GameAudio
{
public:
    AudioAdapter(ThirdPartyAudio *thirdPartyAudio) : thirdPartyAudio_(thirdPartyAudio)
    {
    }

    void Play() override
    {
        thirdPartyAudio_->PlayAudio();
    }

    void Stop() override
    {
        thirdPartyAudio_->StopAudio();
    }

private:
    ThirdPartyAudio *thirdPartyAudio_;
};

// Client code
void PlayGameSound(GameAudio *audio)
{
    audio->Play();
}

int main()
{
    ThirdPartyAudio thirdPartyAudio("background_music.mp3");
    AudioAdapter adapter(&thirdPartyAudio);

    // Use the adapter to play game audio
    PlayGameSound(&adapter);

    return 0;
}
