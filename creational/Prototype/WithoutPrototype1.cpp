#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

struct MetaData
{
    MetaData(
        const std::string& songName,
        const std::string& singer,
        const std::string& musicDirector)
        : m_songName(songName)
        , m_singer(singer)
        , m_musicDirector(musicDirector)
    {

    }

    friend std::ostream& operator << (std::ostream& out, const MetaData& metaData)
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
    Playlist(const std::string& name, const MetaData& metaData)
        : m_name(name)
        , m_metaData(metaData)
    {
        
    }

    friend std::ostream& operator << (std::ostream& out, const Playlist& playList)
    {
        out << "[" << playList.m_name << "] ";
        out << playList.m_metaData;
        return out;
    }

    std::string m_name;
    MetaData m_metaData;
};

int main()
{
    // Since all meta data is same its tedious to create a MetaData of same type again and again
    Playlist p1{"Melody", MetaData{"Mungaru male", "Sonu nigam", "Jayanth"}};
    Playlist p2{"Melody", MetaData{"Sariyagi", "Sonu nigam", "Jayanth"}};
    Playlist p3{"Love", MetaData{"Mungaru male", "Sonu nigam", "Jayanth"}};

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
    std::cout << p3 << "\n";


    // Some way to tackle the above problem is 
    Playlist p4 {p2};
    p4.m_metaData.m_songName = "Araluthiru";
    std::cout << p4 << "\n";

    // What happen if melody type is made as pointer 
    // Refer: WithoutProxy2.cpp
    return 0;
}