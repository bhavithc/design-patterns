#include <iostream>
#include <string>

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

class Renderer
{
public:
    virtual void renderXmlData() = 0;
};

class JacksonRenderer : public Renderer
{
public:
    void renderXmlData() override
    {
        JacksonXmlParser jx("data.xml");
        const auto data = jx.jacksonParseXml();
        std::cout << data << "\n";
    }
};

class OpenXmlRenderer : public Renderer
{
public:
    void renderXmlData() override
    {
        OpenXmlParser openXmlParser;
        const auto data = openXmlParser.openParser("data.xml");
        std::cout << data << "\n";
    }
};

int main()
{
    JacksonRenderer jacksonRenderer;
    jacksonRenderer.renderXmlData();

    OpenXmlRenderer openXmlRenderer;
    openXmlRenderer.renderXmlData();

    return 0;
}