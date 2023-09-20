#include <iostream>
#include <string>
#include <vector>

// Model (Music Library)
class MusicModel
{
private:
    std::vector<std::string> playlist; // List of tracks
    int currentTrackIndex;             // Index of the currently playing track

public:
    MusicModel() : currentTrackIndex(-1)
    {
    }

    void addTrack(const std::string &trackName)
    {
        playlist.push_back(trackName);
    }

    bool playTrack(int trackIndex)
    {
        if (trackIndex >= 0 && trackIndex < playlist.size())
        {
            currentTrackIndex = trackIndex;
            return true;
        }
        return false;
    }

    bool pauseTrack()
    {
        if (currentTrackIndex != -1)
        {
            return true;
        }
        return false;
    }

    bool skipTrack()
    {
        if (currentTrackIndex != -1)
        {
            ++currentTrackIndex;
            if (currentTrackIndex >= playlist.size())
            {
                currentTrackIndex = 0;
            }
            return true;
        }
        return false;
    }

    const std::vector<std::string> &getPlaylist() const
    {
        return playlist;
    }

    int getCurrentTrackIndex() const
    {
        return currentTrackIndex;
    }
};

// View (Music Player Display)
class MusicView
{
public:
    void displayPlaylist(const MusicModel &musicModel)
    {
        std::cout << "Current Playlist:\n";
        const std::vector<std::string> &playlist = musicModel.getPlaylist();
        for (size_t i = 0; i < playlist.size(); ++i)
        {
            std::cout << i + 1 << ". " << playlist[i];
            if (i == musicModel.getCurrentTrackIndex())
            {
                std::cout << " (Playing)";
            }
            std::cout << std::endl;
        }
    }
};

// Controller (Music Player Control)
class MusicController
{
private:
    MusicModel model;
    MusicView view;

public:
    void addTrackToPlaylist(const std::string &trackName)
    {
        model.addTrack(trackName);
    }

    void playTrack(int trackIndex)
    {
        if (model.playTrack(trackIndex))
        {
            view.displayPlaylist(model);
        }
    }

    void pauseTrack()
    {
        if (model.pauseTrack())
        {
            std::cout << "Paused the current track." << std::endl;
        }
    }

    void skipTrack()
    {
        if (model.skipTrack())
        {
            view.displayPlaylist(model);
        }
    }

    void displayPlaylist()
    {
        view.displayPlaylist(model);
    }
};

int main()
{
    MusicController controller;

    controller.addTrackToPlaylist("Track 1");
    controller.addTrackToPlaylist("Track 2");
    controller.addTrackToPlaylist("Track 3");

    controller.displayPlaylist();

    std::cout << "\nPlaying Track 2...\n";
    controller.playTrack(1);

    std::cout << "\nSkipping to the next track...\n";
    controller.skipTrack();

    std::cout << "\nPausing the current track...\n";
    controller.pauseTrack();

    return 0;
}
