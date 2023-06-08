#include <iostream>
#include <string>

class VideoFile
{
public:
    VideoFile(const std::string &filename) : filename_(filename)
    {
    }
    virtual ~VideoFile() = default;
    virtual void Play() const = 0;

protected:
    std::string filename_;
};

class Ogg : public VideoFile
{
public:
    Ogg(const std::string &filename) : VideoFile(filename)
    {
    }
    void Play() const override
    {
        std::cout << "Playing Ogg file: " << filename_ << std::endl;
    }
};

class CoderFactory
{
public:
    static VideoFile *CreateCoder(const std::string &filename)
    {
        if (filename.substr(filename.find_last_of(".") + 1) == "ogg")
        {
            return new Ogg(filename);
        }
        return nullptr;
    }
};

class VideoConverter
{
public:
    VideoConverter() = default;
    ~VideoConverter() = default;
    void Convert(const std::string &filename)
    {
        video_ = CoderFactory::CreateCoder(filename);
    }

private:
    VideoFile *video_;
};

class AudioMixer
{
public:
    AudioMixer() = default;
    ~AudioMixer() = default;
    void MixAudio(const std::string &filename)
    {
        std::cout << "Mixing audio of file: " << filename << std::endl;
    }
};

class Application
{
public:
    Application() = default;
    ~Application() = default;
    void ConvertAndMix(const std::string &filename)
    {
        VideoConverter vc;
        AudioMixer am;
        vc.Convert(filename);
        am.MixAudio(filename);
    }
};

int main()
{
    Application app;
    app.ConvertAndMix("video.ogg");
    return 0;
}
