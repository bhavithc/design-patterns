#include <iostream>
#include <vector>
#include <algorithm>

class IObserver;

class IObservable
{
public:
    enum class Type
    {
        Even,
        Odd,
    };

    virtual void registerObserver(IObserver* observer) = 0;
    virtual void unregisterObserver(IObserver* observer) = 0;
    virtual void notify(Type type, int nr) = 0;
};

class OddEvenGenerator : public IObservable
{
public:
    void generate(int limit);
    void registerObserver(IObserver* observer) override;
    void unregisterObserver(IObserver* observer) override;
    void notify(Type type, int nr) override;

private:
    std::vector<IObserver*> m_observers;
};

class IObserver
{
public:
    virtual void nrChanged(OddEvenGenerator::Type type, int value) = 0;
};


class Observer : public IObserver
{
public:
    void nrChanged(OddEvenGenerator::Type type, int value) override;
};


void OddEvenGenerator::generate(int limit)
{
    for (int i = 0; i < limit; i++) {
        if (i % 2 == 0) {
            notify(Type::Even, i);
        } else {
            notify(Type::Odd, i);
        }
    }
}

void OddEvenGenerator::registerObserver(IObserver* observer)
{
    m_observers.push_back(observer);
}

void OddEvenGenerator::unregisterObserver(IObserver* observer)
{
    m_observers.erase(
        std::remove(m_observers.begin(), m_observers.end(), observer),
        m_observers.end());
}

void OddEvenGenerator::notify(Type type, int nr)
{
    for (auto* observer : m_observers) {
        observer->nrChanged(type, nr);
    }
}

void Observer::nrChanged(OddEvenGenerator::Type type, int value)
{
    if (type == OddEvenGenerator::Type::Even) {
        std::cout << value << " is even number \n";
    } else {
        std::cout << value << " is odd number \n";
    }
}


int main()
{
    Observer o;
    OddEvenGenerator oeg;
    oeg.registerObserver(&o);
    oeg.generate(10);
    oeg.unregisterObserver(&o);
    return 0;
}
