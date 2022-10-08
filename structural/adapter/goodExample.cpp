#include <iostream>
#include <string>
#include <memory>

class IXmlParser
{
public:
    virtual std::string parseXml(const std::string& xmlFile) = 0;
};

const std::string& dummyXml =         
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
        "<Agenda type=\"gardening\">\n"\
        " <Activity type=\"Watering\">\n"\
        "  <golf-course time=\"6:00\"/>\n"\
        "  <yard time=\"7:00\"/>\n"\
        " </Activity>\n"\
        " <Activity type=\"cooking\">\n"\
        "  <lunch time=\"12:00\"/>\n"\
        " </Activity>\n"\
        "</Agenda>\n";

/// Jackson parser library pseducode
class JacksonXmlParser
{
public:
    JacksonXmlParser(const std::string xmlFile)
        : m_xmlFile(xmlFile)
    {

    }

    std::string jacksonParseXml()
    {
        return dummyXml;
    }

private:
    std::string m_xmlFile = "";
};


class OpenXmlParser
{
public:
    std::string openParser(const std::string& xmlFile)
    {
        return dummyXml;
    }
};

class JacksonXmlAdapter : public IXmlParser
{
public:
    std::string parseXml(const std::string& xmlFile) override
    {
        JacksonXmlParser xmlParser(xmlFile);
        return xmlParser.jacksonParseXml();
    }
};

class OpenXmlParserAdapter : public IXmlParser
{
public:
    std::string parseXml(const std::string& xmlFile) override
    {
        OpenXmlParser xmlParser;
        return xmlParser.openParser(xmlFile);
    }
};


class Renderer
{
public:
    enum class Type
    {
        Jackson,
        OpenXml,
    };

    void renderXmlData(Type type)
    {
        std::shared_ptr<IXmlParser> pXmlparser = nullptr;
        std::string data("Invalid data");
        if (type == Type::Jackson) {
            std::cout << "Debug: Parsing xml using jackson parser ...\n\n"; 
            pXmlparser = std::make_shared<JacksonXmlAdapter>();
        } else {
            std::cout << "Debug: Parsing xml using open xml parser ...\n\n";
            pXmlparser = std::make_shared<OpenXmlParserAdapter>();
        }
        
        if (pXmlparser) {
            data = pXmlparser->parseXml("data.xml");
        }

        std::cout << data << "\n";
    }
};


int main(int argc, char** pArgv)
{
    Renderer::Type renderType = Renderer::Type::OpenXml;
    if (argc == 1) {
        std::cout << "Invalid usage: \n";
        std::cout << "Usage: " << pArgv[0] << " - <type>\nWhere type:\n0 - To parse using Jackson parser \n";
        std::cout << "1 - To parse using open xml parser \n";
        return EXIT_FAILURE;
    }

    const int type = std::atoi(pArgv[1]);
    if (type == 0) {
        renderType = Renderer::Type::Jackson;
    }

    Renderer renderer;
    renderer.renderXmlData(renderType);

    return 0;
}
