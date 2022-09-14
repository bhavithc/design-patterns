#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

class IConnectionMonitorObserver;

// This can also be more generic using Templates, but problem is to manage state is difficult we cannot use for custom classes
class ISubjectTcpConnection
{
public:
    enum class ConnectionState
    {
        Connecting,
        Connected,
        Disconnecting,
        Disconnected,
    };

    static const char* connectionStateToStr(ConnectionState state)
    {
        if (state == ConnectionState::Connected) {
            return "Connected";
        }

        if (state == ConnectionState::Connecting) {
            return "Connecting";
        }

        if (state == ConnectionState::Disconnected) {
            return "Disconnected";
        }

        if (state == ConnectionState::Disconnecting) {
            return "Disconnecting";
        }

        return "Unknown";
    }

    struct EventArgs
    {
        ConnectionState connectionState;
        std::string serverName;
    };

    virtual void attach(std::shared_ptr<IConnectionMonitorObserver> pObserver) = 0;
    virtual void dettach(std::shared_ptr<IConnectionMonitorObserver> pObserver) = 0;
    virtual void notify(const ISubjectTcpConnection::EventArgs& eventArgs) = 0;
};

class TcpConnection : public ISubjectTcpConnection
{
public:
    void attach(std::shared_ptr<IConnectionMonitorObserver> pObserver) override;
    void dettach(std::shared_ptr<IConnectionMonitorObserver> pObserver) override;
    void notify(const ISubjectTcpConnection::EventArgs& eventArgs) override;

    void startServer()
    {
        EventArgs eventArgs;
        eventArgs.serverName = "Tcp server";
        eventArgs.connectionState = ISubjectTcpConnection::ConnectionState::Connecting;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        notify(eventArgs);

        eventArgs.connectionState = ISubjectTcpConnection::ConnectionState::Connected;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        notify(eventArgs);

        eventArgs.connectionState = ISubjectTcpConnection::ConnectionState::Disconnecting;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        notify(eventArgs);

        eventArgs.connectionState = ISubjectTcpConnection::ConnectionState::Disconnected;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        notify(eventArgs);
    }

    std::string getIpAddress() const 
    {
        return m_ipAddress;
    }

    int getPortNr() const 
    {
        return m_portNr;
    }

private:
    std::string m_ipAddress = "10.48.57.47";
    int m_portNr = 8080;
    std::vector<std::shared_ptr<IConnectionMonitorObserver>> m_connectionMonitors = {};
};

class IConnectionMonitorObserver
{
public:
    virtual void connectionChanged(const ISubjectTcpConnection::EventArgs& eventArgs) = 0;
};

class WhatsApp : public IConnectionMonitorObserver
{
public:
    void connectionChanged(const ISubjectTcpConnection::EventArgs& eventArgs) override;
};

class Telegram : public IConnectionMonitorObserver
{
public:
    void connectionChanged(const ISubjectTcpConnection::EventArgs& eventArgs) override;
};


void TcpConnection::attach(std::shared_ptr<IConnectionMonitorObserver> pObserver)
{
    m_connectionMonitors.push_back(pObserver);
}

void TcpConnection::dettach(std::shared_ptr<IConnectionMonitorObserver> pObserver)
{
    m_connectionMonitors.erase(
        std::remove(m_connectionMonitors.begin(), m_connectionMonitors.end(), pObserver), 
        m_connectionMonitors.end());
}

void TcpConnection::notify(const ISubjectTcpConnection::EventArgs& eventArgs)
{
    for (auto& connectionMonitor : m_connectionMonitors) {
        connectionMonitor->connectionChanged(eventArgs);
    }
}

void WhatsApp::connectionChanged(const ISubjectTcpConnection::EventArgs& eventArgs)
{
    std::cout   << "[Whatspp] " 
                << " " << eventArgs.serverName << " "
                << ISubjectTcpConnection::connectionStateToStr(eventArgs.connectionState) << " !\n";
}

void Telegram::connectionChanged(const ISubjectTcpConnection::EventArgs& eventArgs)
{
    std::cout   << "[Telgram] " 
                << " " << eventArgs.serverName << " "
                << ISubjectTcpConnection::connectionStateToStr(eventArgs.connectionState) << " !\n";
    
    // Dangerous -> Never call any wait function this block all other events
    // In order to mitigate this one we need to run events in threads that is still more overhead 
    //std::this_thread::sleep_for(std::chrono::seconds(1));
}


int main()
{
    std::shared_ptr<WhatsApp> pWhatsApp = std::make_shared<WhatsApp>();
    std::shared_ptr<Telegram> pTelegram = std::make_shared<Telegram>();

    TcpConnection tcpConnection;
    tcpConnection.attach(pWhatsApp);
    tcpConnection.attach(pTelegram);

    tcpConnection.startServer();
    return 0;
}

