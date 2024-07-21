#include <iostream>
#include <string>
#include <fstream>

class Logger
{
public:
    enum class LogType {
        Console,
        File, 
    };

    void log(const LogType type, const std::string& msg)
    {
        switch (type)
        {
        case LogType::Console:
            std::cout << "Log: " << msg << "\n";
            break;
        case LogType::File:
        {
            std::ofstream logFile ("log.txt", std::ostream::app);
            logFile << "Log: " << msg << "\n";
            logFile.close();
        }
            break;
        default:
            std::cout << "I don't know how to log! \n";
            break;
        }
    }
};

int main()
{
    Logger logger;
    logger.log(Logger::LogType::Console, "Hello console");
    logger.log(Logger::LogType::File, "Hello file");
    return 0;
}