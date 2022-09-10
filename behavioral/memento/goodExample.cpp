#include <iostream>
#include <string>

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
    Memento write(const std::string& content)
    {
        m_content += content;
        m_content += "\n";

        return {m_content};
    }

    void restore(const Memento& memento)
    {
        m_content = memento.m_content;
    }

    void print()
    {
        std::cout << m_content;
    }
private:
    std::string m_content = "";
};

int main()
{

    Document doc;
    auto m1 = doc.write("This is my first line");
    auto m2 = doc.write("This is second line");
    auto m3 = doc.write("This is third line");

    doc.print();
    std::cout << "Restored to m2 \n";
    doc.restore(m1);
    doc.print();
    return 0;
}