#include <iostream>
#include <string>
#include <cstring>

// Compile with -g option and run valgrind ./a.out
class Animal
{
public:
    Animal(const char* pName, int height, int weight, int* pLen)
        : m_height(height)
        , m_weight(weight)
    {
        if (pName) {
            m_pName = new char[1, strlen(pName) + 1]();
            m_pName = strncpy(m_pName, pName, strlen(pName));
        }

        if (pLen) {
            m_pLength = new int;
            *m_pLength = *pLen;
        }
    }

    ~Animal()
    {
        if (m_pName) {
            delete[] m_pName;
        }

        if (m_pLength) {
            delete m_pLength;
        }

        m_pLength = nullptr;
        m_pName = nullptr;
    }

    Animal(const Animal& other)
    {
        if (other.m_pName) {
            m_pName = new char[1, strlen(other.m_pName) + 1]();
            m_pName = strncpy(m_pName, other.m_pName, strlen(other.m_pName));
        }

        if (other.m_pLength) {
            m_pLength = new int;
            *m_pLength = *other.m_pLength;
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
        os << ": " << animal.m_height << " x " << animal.m_weight << " - " << (animal.m_pLength ? *animal.m_pLength : 0);
        return os;
    }

private:
    char* m_pName = nullptr;
    int m_height = 0;
    int m_weight = 0;
    int* m_pLength = nullptr;
};

int main()
{
    int* p = new int(10);

    Animal a("Lion", 20, 30, p);
    Animal b {a};

    std::cout << a << "\n";
    std::cout << b << "\n";

    delete p;
    return 0;
}