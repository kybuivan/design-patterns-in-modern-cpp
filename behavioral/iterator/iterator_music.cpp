#include <iostream>
#include <memory>
#include <string>
#include <vector>

// MusicTrack class representing individual music tracks
class MusicTrack
{
public:
    MusicTrack(const std::string &title, const std::string &artist, int duration)
        : title(title), artist(artist), duration(duration)
    {
    }

    std::string getTitle() const
    {
        return title;
    }

    std::string getArtist() const
    {
        return artist;
    }

    int getDuration() const
    {
        return duration;
    }

private:
    std::string title;
    std::string artist;
    int duration; // Duration in seconds
};

// Iterator interface
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual MusicTrack next() = 0;
};

// Concrete Iterator for a collection of music tracks
class MusicLibraryIterator : public Iterator
{
public:
    MusicLibraryIterator(std::vector<MusicTrack> &tracks) : tracks(tracks), position(0)
    {
    }

    bool hasNext() override
    {
        return position < tracks.size();
    }

    MusicTrack next() override
    {
        if (hasNext())
        {
            return tracks[position++];
        }
        else
        {
            throw std::out_of_range("No more tracks in the collection.");
        }
    }

private:
    std::vector<MusicTrack> &tracks;
    size_t position;
};

// Collection interface
class MusicLibrary
{
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0;
};

// Concrete Collection for a music library
class Playlist : public MusicLibrary
{
public:
    Playlist(const std::string &name) : name(name)
    {
    }

    std::shared_ptr<Iterator> createIterator() override
    {
        return std::make_shared<MusicLibraryIterator>(tracks);
    }

    void addTrack(const MusicTrack &track)
    {
        tracks.push_back(track);
    }

    std::string getName() const
    {
        return name;
    }

private:
    std::string name;
    std::vector<MusicTrack> tracks;
};

int main()
{
    // Create a playlist and add some music tracks
    Playlist playlist("My Favorites");
    playlist.addTrack(MusicTrack("Bohemian Rhapsody", "Queen", 354));
    playlist.addTrack(MusicTrack("Imagine", "John Lennon", 182));
    playlist.addTrack(MusicTrack("Hotel California", "Eagles", 391));
    playlist.addTrack(MusicTrack("Stairway to Heaven", "Led Zeppelin", 482));

    // Create an iterator for the playlist
    std::shared_ptr<Iterator> iterator = playlist.createIterator();

    // Traverse and print the music tracks using the iterator
    std::cout << "Playlist: " << playlist.getName() << std::endl;
    while (iterator->hasNext())
    {
        MusicTrack track = iterator->next();
        std::cout << "Title: " << track.getTitle() << ", Artist: " << track.getArtist()
                  << ", Duration: " << track.getDuration() << " seconds" << std::endl;
    }

    return 0;
}
