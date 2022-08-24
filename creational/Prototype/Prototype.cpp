#include <iostream>
#include <string>
#include <sstream>
#include <memory>

struct MetaData
{
    // Ctor
    MetaData(
        const std::string &songName,
        const std::string &singer,
        const std::string &musicDirector)
        : m_songName(songName)
        , m_singer(singer)
        , m_musicDirector(musicDirector)
    {
    }

    // Copy ctor
    MetaData(const MetaData &other)
        : m_songName(other.m_songName)
        , m_singer(other.m_singer)
        , m_musicDirector(other.m_musicDirector)
    {
    }

    // Overload assignment operator
    void operator=(const MetaData &other)
    {
        m_songName = other.m_songName;
        m_singer = other.m_singer;
        m_musicDirector = other.m_musicDirector;
    }

    friend std::ostream &operator<<(std::ostream &out, const MetaData &metaData)
    {
        out << "Song: " << metaData.m_songName
            << ", Singer: " << metaData.m_singer
            << ", Director: " << metaData.m_musicDirector;
        return out;
    }

    std::string m_songName = "";
    std::string m_singer = "";
    std::string m_musicDirector = "";
};

struct Playlist
{
    Playlist(const std::string &name, MetaData *pMetaData)
        : m_name(name)
        , m_pMetaData(pMetaData)
    {
    }

    // Use Move ctor instead of copy ctor since we used unique ptr
    Playlist(Playlist&& other)
        : m_name(other.m_name)
        , m_pMetaData(std::move(other.m_pMetaData))
    {
    }

    // Overload assignment operator with move semantic
    Playlist& operator=(Playlist& other)
    {
        m_name = other.m_name;
        
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Playlist &playList)
    {
        out << "[" << playList.m_name << "] ";
        out << *playList.m_pMetaData;
        return out;
    }

    std::string m_name;
    MetaData* m_pMetaData;
};

int main()
{
    auto pMetaData = new MetaData{"Mungaru male", "Sonu nigam", "Jayanth"};

    Playlist p1{"Melody", pMetaData};
    Playlist p2{p1};
    // Update p2 song
    p2.m_pMetaData->m_songName = "Sariyagi";
    std::cout << p1 << "\n";
    std::cout << p2 << "\n";

    return 0;
}