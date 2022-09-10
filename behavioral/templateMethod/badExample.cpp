#include <iostream>
#include <string>

class DataCollectorTcpCsv
{
public:
    void doCollect()
    {
        const auto data = readData();
        if (isValid(data)) {
            sendData(data);
            saveData();
        } else {
            std::cerr << "Data is invalid unable to send to server and save\n";
        }
    }
private:
    const char* readData()
    {
        std::cout << "Reading data from file system...\n";
        return "log information";
    }

    bool isValid(const std::string& data)
    {
        return data.size() > 0;
    }

    void sendData(const std::string& data)
    {
        std::cout << "Sending data ...\n";
        std::cout << "Data sent to server via tcp successfully \n";
    }

    void saveData()
    {
        std::cout << "Data saved successfully as CSV \n";
    }
};

class DataCollectorUdpCsv
{
public:
    void doCollect()
    {
        const auto data = readData();
        if (isValid(data)) {
            sendData(data);
            saveData();
        } else {
            std::cerr << "Data is invalid unable to send to server and save\n";
        }
    }
private:
    const char* readData()
    {
        std::cout << "Reading data from flash memory ...\n";
        return "log information";
    }

    bool isValid(const std::string& data)
    {
        return data.size() > 0;
    }

    void sendData(const std::string& data)
    {
        std::cout << "Sending data ...\n";
        std::cout << "Data sent to server via udp successfully \n";
    }

    void saveData()
    {
        std::cout << "Data saved successfully as CSV \n";
    }
};

class DataCollectorTcpJson
{
public:
    void doCollect()
    {
        const auto data = readData();
        if (isValid(data)) {
            sendData(data);
            saveData();
        } else {
            std::cerr << "Data is invalid unable to send to server and save\n";
        }
    }
private:
    const char* readData()
    {
        std::cout << "Reading data from SQL lite ...\n";
        return "log information";
    }

    bool isValid(const std::string& data)
    {
        return data.size() > 0;
    }

    void sendData(const std::string& data)
    {
        std::cout << "Sending data ...\n";
        std::cout << "Data sent to server via tcp successfully \n";
    }

    void saveData()
    {
        std::cout << "Data saved successfully as JSON \n";
    }
};

int main()
{
    DataCollectorTcpCsv dcTcpCsv;
    dcTcpCsv.doCollect();
    std::cout << "\n";

    DataCollectorTcpJson collectorJson;
    collectorJson.doCollect();
    std::cout << "\n";

    DataCollectorUdpCsv collectorUdpCsv;
    collectorUdpCsv.doCollect();
    std::cout << "\n";

    return 0;
}

