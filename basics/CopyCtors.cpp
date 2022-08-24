#include <iostream>
#include <string>
#include <cstring>

// Compile with -g option and run valgrind ./a.out
class Animal
{
public:
    Animal(const char* pName, int height, int weight)
        : m_height(height)
        , m_weight(weight)
    {
        if (pName) {
            m_pName = new char[strlen(pName)];
            m_pName = strncpy(m_pName, pName, strlen(pName));
        }
    }

    ~Animal()
    {
        if (m_pName) {
            delete[] m_pName;
        }
        m_pName = nullptr;
    }

    Animal(const Animal& other)
    {
        if (other.m_pName) {
            m_pName = new char[strlen(other.m_pName)];
            m_pName = strncpy(m_pName, other.m_pName, strlen(other.m_pName));
        }

        m_height = other.m_height;
        m_weight = other.m_weight;
    }

    friend std::ostream& operator<<(std::ostream& os, const Animal& animal)
    {
        if (animal.m_pName != nullptr) {
            os << animal.m_pName;
        } else {
            os << " ";
        }
        os << ": " << animal.m_height << " x " << animal.m_weight;
        return os;
    }

private:
    char* m_pName = nullptr;
    int m_height = 0;
    int m_weight = 0;
};

int main()
{
    Animal a("Lion", 20, 30);
    Animal b {a};
    std::cout << a << "\n";
    std::cout << b << "\n";
    return 0;
}