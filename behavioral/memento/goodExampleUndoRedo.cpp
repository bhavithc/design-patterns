#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Memento
{
public:
    Memento(const std::string& content)
        : m_content(content)
    {

    }
private:
    std::string m_content;
    friend class Document;
};

class Document
{
public:
    Document()
    {
        auto m = std::make_shared<Memento>(m_content);
        m_changes.emplace_back(m);
        m_currentIndex = 0;
    }
    std::shared_ptr<Memento> write(const std::string& content)
    {
        m_content += content;
        m_content += "\n";

        auto pMemento = std::make_shared<Memento>(m_content);
        m_changes.emplace_back(pMemento);
        m_currentIndex++;

        return pMemento;
    }

    // m1 1     <- 0
    // m2 1 2   <- 1
    // m3 1 2 3 <- 2
    // m3 1 2 3 <- 3
    // m3 1 2 3 <- 
    void restore(const std::shared_ptr<Memento>& pMemento)
    {
        if (pMemento) {
            m_content = pMemento->m_content;
            m_changes.emplace_back(pMemento);
            m_currentIndex = m_changes.size() - 1;
        }
    }

    std::shared_ptr<Memento> undo()
    {
        if (m_currentIndex > 0) {
            m_currentIndex--;
            auto pMemento = m_changes[m_currentIndex];
            m_content = pMemento->m_content;
            return pMemento;
        }

        return {};
    }

    std::shared_ptr<Memento> redo()
    {
        if (m_currentIndex + 1 < m_changes.size()) {
            m_currentIndex++;
            auto pMemento = m_changes[m_currentIndex];
            m_content = pMemento->m_content;
            return pMemento;
        }

        return {};
    }

    void print()
    {
        std::cout << "\n---------------\n";
        std::cout << m_content;
    }

private:
    std::string m_content = "";
    std::vector<std::shared_ptr<Memento>> m_changes;
    int m_currentIndex = 0;
};

int main()
{

    Document doc;
    auto m1 = doc.write("This is my first line");
    auto m2 = doc.write("This is second line");
    auto m3 = doc.write("This is third line");

    doc.print();

    std::cout << "Undo\n";
    doc.undo();
    doc.print();
    std::cout << "Redo\n";
    std::cout << doc.redo() << "\n";
    std::cout << doc.redo() << "\n";
    doc.print();

    // std::cout << "Restored to m2 \n";
    // doc.restore(m1);
    // doc.print();
    return 0;
}