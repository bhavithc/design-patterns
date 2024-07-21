#include <iostream>
#include <string>
#include <fstream>

class ILogger
{
public:
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

class ConsoleLogger : public ILogger 
{
public:
    void log(const std::string& message)
    {
        std::cout << "Log: " << message << "\n";
    }
};

class FileLogger : public ILogger 
{
public:
    FileLogger (const std::string& logFile)
        : m_fileStream {logFile, std::ofstream::app}
    {
        
    }

    ~FileLogger()
    {
        if (m_fileStream.is_open()) {
            m_fileStream.close();
        }
    }

    void log(const std::string& message)
    {
        if (m_fileStream.is_open()) {
            m_fileStream << "Log: " << message << "\n";
        }
    }
private:
    std::ofstream m_fileStream;
};


class Application
{
public:
    Application(ILogger& logger)
        : m_logger {logger}
    {
    }

    void print(const int start, const int end)
    {
        m_logger.log("Inside " + std::string(__FUNCTION__) 
            + " start: " + std::to_string(start) 
            + " end: " + std::to_string(end) + " - in");

        if (start < 0) {
            m_logger.log("ERROR: start cannot be less than zero!");
            return;
        }

        if (end < start) {
            m_logger.log("ERROR: end cannot be less than start!");
            return;
        }

        m_logger.log("----------------------");
        for (int i = start; i < end; i++) {
            m_logger.log("Print " + std::to_string(i));
        }
        m_logger.log("----------------------");

        m_logger.log("Inside " + std::string(__FUNCTION__) + " - out");
    }

private:
    ILogger& m_logger;
};


int main()
{
    ConsoleLogger consoleLogger;
    FileLogger fileLogger {"application.log"}; 
    Application app{consoleLogger};
    app.print(0, 10);
    return 0;
}