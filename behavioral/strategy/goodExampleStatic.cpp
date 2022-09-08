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

template <typename T>
class ListProcessor
{
public:
    void append(const std::string& item)
    {
        m_list.emplace_back(item);
    }

    std::string format()
    {
        return m_strategy.format(m_list);
    }

private:
    std::vector<std::string> m_list = {};
    T m_strategy;
};

int main()
{
    ListProcessor<HtmlFormatStrategy> lp;
    lp.append("python");
    lp.append("c++");
    lp.append("Rust");
    std::cout << lp.format() << "\n";

    ListProcessor<JsonStrategy> jp;
    jp.append("python");
    jp.append("c++");
    jp.append("Rust");
    std::cout << jp.format() << "\n";

    ListProcessor<MarkDownStrategy> mp;
    mp.append("python");
    mp.append("c++");
    mp.append("Rust");
    std::cout << mp.format() << "\n";

    return 0;
}