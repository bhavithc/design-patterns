#include <iostream>
#include <string>

class DataCollector
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
protected:
    virtual const char* readData() = 0;

    virtual bool isValid(const std::string& data) = 0;

    virtual void sendData(const std::string& data) = 0;

    virtual void saveData() = 0;
};

class EcuDataCollector : public DataCollector
{
private:
    const char* readData() override
    {
        std::cout << "Reading the data from ECU ...\n";
        return "ECU: TMP: 1 0 ";
    }

    bool isValid(const std::string& data) override
    {
        return data.size() > 0;
    }

    void sendData(const std::string& data) override
    {
        std::cout << "Sending data over CAN ...\n";
        std::cout << data << " sent successfully \n";
    }

    void saveData() override
    {
       std::cout << "Data save to flash memory !\n"; 
    }
};

class AppDataCollector : public DataCollector
{
private:
    const char* readData() override
    {
        std::cout << "Reading data from SQL lite ...\n";
        return "App1: temp 38.4, pressure 78";
    }

    bool isValid(const std::string& data) override
    {
        return data.size() > 0;
    }

    void sendData(const std::string& data) override
    {
        std::cout << "Converting data to http request ...\n";
        std::cout << "Data sent to cloud successfully \n";
    }

    void saveData() override
    {
        std::cout << "Data saved successfully in JSON format \n";
    }
};

int main()
{
    EcuDataCollector edc;
    edc.doCollect();
    std::cout << "----------\n";

    AppDataCollector adc;
    adc.doCollect();

    return 0;
}

