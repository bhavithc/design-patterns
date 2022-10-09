#include <iostream>
#include <string>

class IPlayer
{
public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void stop() = 0;
};

class AlsaDriver
{
public:
    void pausePulseAudio()
    {
        std::cout << "Pausing the pulse audio signal \n";
    }

    void playMp3Audio()
    {
        readFromMediaSource();
        std::cout << "Playing MP3 Audio \n";
    }

private:
    void readFromMediaSource()
    {
        std::cout << "Reading song from USB by default...\n";
    }
};

class Antenna
{
public:
    enum class Strength
    {
        Weak,
        Strong,
        NoSignal,
    };

    Strength getCurrentSignalStrength()
    {
        return Strength::Strong;
    }
};

class FMCircuit
{
public:
    void selectNextFrequency()
    {
        if (isSignalGood()) {
            std::cout << "Selecting the next frequency \n";
        }
    }

private:
    bool isSignalGood()
    {
        auto signalGood = false;
        auto strenght = antenna.getCurrentSignalStrength();
        if (strenght == Antenna::Strength::Strong) {
            signalGood = true;
        }
        return signalGood;
    }

    Antenna antenna;
};

class MusicPlayer : public IPlayer
{
public:
    void play() override
    {
        m_aslaDriver.playMp3Audio();
        std::cout << "[MUSIC] playing song ...\n";
    }

    void pause() override
    {
        m_aslaDriver.pausePulseAudio();
        std::cout << "[MUSIC] song paused !\n";
    }

    void next() override
    {
        std::cout << "[MUSIC] next song selected !\n";
    }

    void previous() override
    {
        std::cout << "[MUSIC] previous song selected !\n";
    }

    void stop() override
    {
        std::cout << "[MUSIC] song stopped !\n";
    }
private:
    AlsaDriver m_aslaDriver;
};

class FMPlayer : public IPlayer
{
public:
    void play() override
    {
        std::cout << "[FM RADIO] playing FM station !\n";
    }

    void pause() override
    {
        std::cout << "[FM RADIO] FM Radio stopped !\n";
    }

    void next() override
    {
        m_fmCircuit.selectNextFrequency();
        std::cout << "[FM RADIO] next station selected \n";
    }

    void previous() override
    {
        std::cout << "[FM RADIO] previous station selected \n";
    }

    void stop() override
    {
        std::cout << "[FM RADIO] FM Radio stopped !\n";
    }
private:
    FMCircuit m_fmCircuit;
};

class Media
{
public:
    void clickMode()
    {
        // Toggle the button
        if (m_fmSelected) {
            m_fmSelected = false;
            m_fmPlayer.stop();
            m_musicPlayer.play();
        } else {
            m_fmSelected = true;
            m_musicPlayer.stop();
            m_fmPlayer.play();
        }
    }

    void clickNext()
    {
        if (m_fmSelected) {
            m_fmPlayer.next();
        } else {
            m_musicPlayer.next();
        }
    }

    void clickPrevious()
    {
        if (m_fmSelected) {
            m_fmPlayer.previous();
        } else {
            m_musicPlayer.previous();
        }
    }

    void clickStop()
    {
        if (m_fmSelected) {
            m_fmPlayer.stop();
        } else {
            m_musicPlayer.stop();
        }
    }
private:
    bool m_fmSelected = false;
    MusicPlayer m_musicPlayer;
    FMPlayer m_fmPlayer;
};

int main()
{
    Media media;
    media.clickMode();
    media.clickNext();
    media.clickPrevious();
    media.clickStop();

    std::cout << "\n\nChanging the mode ....\n\n";
    // Change mode
    media.clickMode();
    media.clickNext();
    media.clickPrevious();
    media.clickStop();

    return 0;
}