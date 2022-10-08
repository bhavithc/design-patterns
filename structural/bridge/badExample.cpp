#include <string>
#include <iostream>

// Requirement
// long form, short form - views
// spotify, apple car play - resource
// Build classes which handles all these

class MediaApi
{
public:
    virtual std::string title() = 0;
    virtual std::string artist() = 0;
};

class Spotify : public MediaApi
{
public:
    std::string title() override
    {
        return "Spotify - Title";
    }

    std::string artist() override
    {
        return "Spotify - Artist";
    }
};

class Apple : public MediaApi
{
public:
    std::string title() override
    {
        return "Apple - Title";
    }

    std::string artist() override
    {
        return "Apple - Artist";
    }
};

class View
{
public:
    virtual void show() = 0;
};

class LongFormSpotify : public View
{
public:
    void show() override
    {
        std::cout << "============Spotify long================\n";
        std::cout << "Title: " << spotify.title() << "\n";
        std::cout << "Artist: " << spotify.artist() << "\n";
        std::cout << "========================================\n";
    }
private:
    Spotify spotify;
};

class ShortFormSpotify : public View
{
public:
    void show() override
    {
        std::cout << "============Spotify short================\n";
        std::cout << "Title: " << spotify.title() << "\n";
        std::cout << "=========================================\n";
    }
private:
    Spotify spotify;
};

class ShortFormApple : public View
{
public:
    void show() override
    {
        std::cout << "============Apple short================\n";
        std::cout << "Title: " << apple.title() << "\n";
        std::cout << "=========================================\n";
    }
private:
    Apple apple;
};

class LongFormApple : public View
{
public:
    void show() override
    {
        std::cout << "============Apple long================\n";
        std::cout << "Title: " << apple.title() << "\n";
        std::cout << "Artist: " << apple.artist() << "\n";
        std::cout << "========================================\n";
    }
private:
    Apple apple;
};

int main()
{
    LongFormApple la;
    la.show();

    LongFormSpotify ls;
    ls.show();

    ShortFormSpotify ss;
    ss.show();

    ShortFormApple sa;
    sa.show();

    return 0;
}