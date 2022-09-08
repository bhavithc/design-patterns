#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Document generator (List generator)
// HTML
// MarkDown
// JSON

// Example1
// Sort using quick sort, bubble sort, sel sort etc.. -> Family of alogs
class ListFormatter
{
public:
    enum class FormatterType
    {
        Html,
        MarkDown,
    };

    void append(const std::string& item)
    {
        m_list.emplace_back(item);
    }

    std::string format(FormatterType type)
    {
        std::stringstream ss;
        switch (type)
        {
        case FormatterType::Html:
            ss << "<ul>\n";
            for (const auto& item : m_list) {
                ss << "    <li>" << item << "<li/>\n";
            }
            ss << "</ul>\n";
            break;
        
        case FormatterType::MarkDown:
            for (const auto& item : m_list) {
                ss << "- " << item << "\n";
            }
            break;

        default:
            for (const auto& item : m_list) {
                ss << item << ",";
            }
            ss << "\n";
            break;
        }

        return ss.str();
    }
private:
    std::vector<std::string> m_list = {};
};

int main()
{
    ListFormatter lf;
    lf.append("c++");
    lf.append("python");
    lf.append("Java");

    std::cout << lf.format(ListFormatter::FormatterType::Html) << "\n";
    std::cout << lf.format(ListFormatter::FormatterType::MarkDown) << "\n";

    return 0;
}