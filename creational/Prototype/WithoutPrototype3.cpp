#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
// let change the metadata to pointer type
struct MetaData
{
    MetaData(
        const std::string &songName,
        const std::string &singer,
        const std::string &musicDirector)
        : m_songName(songName), m_singer(singer), m_musicDirector(musicDirector)
    {
    }

    MetaData(const MetaData &other)
        : m_songName(other.m_songName), m_singer(other.m_singer), m_musicDirector(other.m_musicDirector)
    {
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
        : m_name(name), m_pMetaData(pMetaData)
    {
    }

    Playlist(const Playlist &other)
        : m_name(other.m_name)
    {
        // way1
        // if (other.m_pMetaData) {
        //     m_pMetaData = new MetaData{
        //         other.m_pMetaData->m_songName,
        //         other.m_pMetaData->m_singer,
        //         other.m_pMetaData->m_musicDirector};
        // }

        // Way2
        if (other.m_pMetaData)
        {
            // Who deletes this ? Who owns the ownership? -> Big memory leak
            m_pMetaData = new MetaData(*other.m_pMetaData);
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const Playlist &playList)
    {
        out << "[" << playList.m_name << "] ";
        out << *playList.m_pMetaData;
        return out;
    }

    std::string m_name;
    MetaData *m_pMetaData;
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

    // Now p1 and p2 can work independently, offcourse we have to take care of the ownerships

    // What if we want to give one prototype to customer or API user
    // Option1: Declare a global variable, from that people can copy the object and make necessary changes
    // they want, Like move p1 to global variable. But we are exposing the constructor

    // Option2: let hide how the prototype is constructored using Prototype factory
    // Refer: Proxy.cpp -> Actual Proxy pattern with factory
    
    return 0;
}