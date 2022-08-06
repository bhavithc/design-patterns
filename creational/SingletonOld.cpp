#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Singleton
{
public:
    const char* printName()
    {
        return m_pName;
    }

    static Singleton* instance()
    {
        // Commenting below line make multiple instances
        std::lock_guard<std::mutex> lock(m_mtx);
        if (Singleton::m_pInstance == nullptr) {
            Singleton::m_pInstance = new Singleton;
        }

        return Singleton::m_pInstance;
    }

protected:
    Singleton()
    {
        std::cout << "Instance created \n";
    }
private:
    static Singleton* m_pInstance;
    static std::mutex m_mtx;
    const char* m_pName = "SingletonOld";
};

Singleton* Singleton::m_pInstance = nullptr;
std::mutex Singleton::m_mtx;

int main()
{

    auto create = [](){
        Singleton::instance();
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 100; i++) {
        threads.push_back(std::thread(create));
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}
