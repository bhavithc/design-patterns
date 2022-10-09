#include <iostream>
#include <string>
#include <memory>

class Book
{
public:
    std::string parseBook(const std::string& bookName)
    {
        std::cout << "Parsing \'" << bookName << "\'...\n";
        std::string s;
        s = "========================\n";
        s += "Book content\n";
        s += "Chapter1: Introduction to c++\n";
        s += "...\n";
        s += "========================\n";

        return s; 
    }

    int nrOfPages()
    {
        return 120;
    }
};

class IBookParser
{
public:
    virtual int getNrofPages() = 0; 
};

class BookParser : public IBookParser
{
public:
    BookParser(const std::string& bookName)
        : m_bookName(bookName)
    {
        m_pBook = std::make_shared<Book>();
    }

    int getNrofPages() override
    {
        m_pBook->parseBook(m_bookName);
        return m_pBook->nrOfPages();
    }
private:
    std::string m_bookName;
    std::shared_ptr<Book> m_pBook;
};

// Why can't we have a proxy which can control the access for the book and do some other stuffs 
// as well

int main()
{
    BookParser bp("For the love of physics");
    const auto pages = bp.getNrofPages();
    std::cout << "Number of pages in books are " << pages << "\n"; 

    return 0;
}
