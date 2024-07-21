#include <iostream>
#include <string>

class FileManager 
{
public:
    void writeFile(const std::string& filePath, const std::string& content)
    {
        // Open file and write 
        log(Level::INFO, "Inside " + std::string(__FUNCTION__));
        log(Level::INFO, "Writing information to " + filePath);
        log(Level::INFO, "Content: " + content);
    }

    void readFile(const std::string& filePath) 
    {
        log(Level::INFO, "Reading the file " + filePath + "...");
    }

private:
    enum class Level {
        INFO, 
        WARN,
        ERROR,
    };

    void log(const Level level, const std::string& msg) 
    {
        switch (level)
        {
        case Level::INFO:
            std::cout << "[INFO]: ";
            break;
        case Level::WARN:
            std::cout << "[WARN]: ";
            break;
        case Level::ERROR:
            std::cout << "[ERROR]: ";
            break;
        default:
            std::cout << "[INFO]: ";
            break;
        }
        
        std::cout << msg << std::endl;
    }
};

int main()
{
    const std::string fileToProcess {"~/sample.txt"};
    FileManager fileManger;
    fileManger.writeFile(fileToProcess, "My message");
    fileManger.readFile(fileToProcess);
    return 0;
}