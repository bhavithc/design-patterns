#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class FormatStrategy
{
public:
    virtual std::string format(const std::vector<std::string>& vec) = 0;
};

class HtmlFormatStrategy : public FormatStrategy
{
public:
    std::string format(const std::vector<std::string>& vec) override
    {
        std::stringstream ss;
        ss << "<ul>\n";
        for (const auto& item : vec) {
            ss << "    <li>" << item << "<li/>\n";
        }
        ss << "</ul>\n";

        return ss.str();
    }
};

class MarkDownStrategy : public FormatStrategy
{
public:
    std::string format(const std::vector<std::string>& vec) override
    {
        std::stringstream ss;
        for (const auto& item : vec) {
            ss << "- " << item << "\n";
        }

        return ss.str();
    }
};

class JsonStrategy : public FormatStrategy
{
public:
    std::string format(const std::vector<std::string>& vec) override
    {
        std::stringstream ss;
        ss << "{\n";
        ss << "    \"values\" : [ ";
        for (const auto& item : vec) {
            ss << item << ",";
        }
        ss << " ]\n";
        ss << "}\n";
        return ss.str();
    }
};

class ListProcessor
{
public:
    void append(const std::string& item)
    {
        m_list.emplace_back(item);
    }

    std::string format(FormatStrategy& strategy)
    {
        return strategy.format(m_list);
    }

private:
    std::vector<std::string> m_list = {};
};

int main()
{
    ListProcessor lp;
    lp.append("python");
    lp.append("c++");
    lp.append("Rust");

    HtmlFormatStrategy html;
    MarkDownStrategy ms;
    JsonStrategy js;
    std::cout << lp.format(html) << "\n";
    std::cout << lp.format(ms) << "\n";
    std::cout << lp.format(js) << "\n";

    return 0;
}