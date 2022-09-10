#include <iostream>
#include <vector>
#include <map>

class Document
{
public:
    void write(const std::string& content)
    {
        m_content += content;
        m_content += "\n";
    }

    void print()
    {
        std::cout << m_content << "\n";
    }
private:
    std::string m_content = "";
};

int main()
{
    std::map<int, Document> docs;
    Document doc;
    doc.write("Line 1");
    docs[0] = doc;

    doc.write("Line 2");
    docs[1] = doc;

    doc.write("Line 3");
    docs[2] = doc;

    doc.print();
    doc = docs[0];
    doc.print();

    doc = docs[2];
    doc.print();

    return 0;
}