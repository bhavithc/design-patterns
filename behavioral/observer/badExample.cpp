#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m_mtx;

class OddEvenGenerator
{
public:
    void generate(int limit)
    {
        for (int i = 0; i < limit; i++) {

            std::lock_guard<std::mutex> lock(m_mtx);
            if (i % 2 == 0) {
                std::cout << i << " is even number\n";
            } else {
                std::cout << i << " is odd number \n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            m_nr = i;
        }
    }

    int getCurrentNr() const
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_nr;
    }

private:
    int m_nr = 0;
};

class MonitorNumbers
{
public:

    ~MonitorNumbers()
    {
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }


    void monitor()
    {
        const auto nr = 10;
        m_thread = std::thread([this](){
            m_oddEvenGenerator.generate(nr);
        });
    
        for (int i = 0; i < 10; i++) {
            m_oddEvenGenerator.getCurrentNr();
        }
    }


    void doSomething()
    {
        for (int i = 0; i < 10; i++) {
            std::cout << "Doing something ... \n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

private:
    std::thread m_thread;
    OddEvenGenerator m_oddEvenGenerator;
};

int main()
{
    MonitorNumbers mn;
    mn.monitor();
    mn.doSomething();

    return 0;
}