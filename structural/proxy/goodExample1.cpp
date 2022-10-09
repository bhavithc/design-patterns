#include <iostream>
#include <string>
#include <memory>
#include <mutex>

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
    BookParser(std::shared_ptr<Book> pBook)
        : m_pBook(pBook)
    {
    }

    int getNrofPages() override
    {
        return m_pBook->nrOfPages();
    }

private:
    std::shared_ptr<Book> m_pBook;
};

class LazyBookParser : public IBookParser
{
public:
    LazyBookParser(const std::string& bookName)
        : m_bookName(bookName)
    {

    }

    int getNrofPages() override
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        if (m_pBook == nullptr) {
            std::cout << "Instance created now\n";
            m_pBook = std::make_shared<Book>();
            m_pBook->parseBook(m_bookName);
        } else {
            std::cout << "using existing instance \n";
            std::cout << "parse is not required \n";
        }

        BookParser bp(m_pBook); // Hold the instance of actual book parser
        return bp.getNrofPages();
    }
private:
    std::string m_bookName;
    std::shared_ptr<Book> m_pBook {nullptr};
    std::mutex m_mtx;
};

// Why can't we have a proxy which can control the access for the book and do some other stuffs 
// as well


// Examples for proxy
// control access
// Lazy init
// Remote call (RPC)

int main()
{
    LazyBookParser lbp("Love of physics");
    const auto pages = lbp.getNrofPages();
    std::cout << "Number of pages in books are " << pages << "\n"; 

    const auto pages2 = lbp.getNrofPages();
    std::cout << "Number of pages in books are " << pages2 << "\n"; 
    return 0;
}
