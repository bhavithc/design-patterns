#include <iostream>
#include <thread>
#include <vector>

class Singleton
{
public:
    const char* printName()
    {
        return m_pName;
    }

    static Singleton& instance()
    {
        static Singleton instance;
        return instance;
    }

protected:
    Singleton()
    {
        std::cout << "Instance created \n";
    }
private:
    const char* m_pName = "SingletonOld";
};

int main()
{

    auto create = [](){
        Singleton::instance();
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 1000; i++) {
        threads.push_back(std::thread(create));
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}