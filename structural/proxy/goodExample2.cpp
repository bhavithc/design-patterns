#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>

class IUserDatabase
{
public:
    virtual void readAllUserNames() const = 0;
    virtual void readAllpassword() const = 0;
};

// Control access
namespace AmazonServer
{
class UserDatabase : public IUserDatabase
{
public:
    UserDatabase()
    {
        m_users.push_back({"Bhavith C", "bhfg@1241", "admin"});
        m_users.push_back({"Srinivas", "sri#4^&^*%^", "dev"});
        m_users.push_back({"Vishal", "&$^%*&TFU", "dev"});
        m_users.push_back({"Mahesh", "JRGH^#%$T&^", "test"});
        m_users.push_back({"Karthik", "fdf@1241", "test"});
    }

    void connect()
    {
        m_connected = true;
    }

    void disConnect()
    {
        m_connected = false;
    }

    void readAllUserNames() const override
    {
        if (!m_connected) {
            std::cerr << "Database not connected unable to read the usernames \n";
            return;
        }
        std::cout << "\n";
        std::cout << "|---------------------|\n";
        std::cout << "|     USER INFO       |\n";
        std::cout << "|---------------------|\n";
        std::cout << "|" << std::setw(5)
                    << std::setw(10) << "username" 
                    << "|" << std::setw(10) << "User type"
                    << "|\n";
        std::cout << "|---------------------|\n";
        for (const auto& user : m_users) {
            std::cout << "|" << std::setw(5)
                      << std::setw(10) << user.username 
                      << "|" << std::setw(10) << user.userType 
                      << "|\n";
        }
        std::cout << "|---------------------|\n\n";
    }

    void readAllpassword() const override
    {
        if (!m_connected) {
            std::cerr << "Database not connected unable to read the credentials \n";
            return;
        }
        std::cout << "\n";
        std::cout << "|-------------------------------------|\n";
        std::cout << "|                 CRED INFO           |\n";
        std::cout << "|-------------------------------------|\n";
        std::cout << "|" << std::setw(5)
                    << std::setw(10) << "username" 
                    << "|" << std::setw(10) << "User type"
                    << "|" << std::setw(15) << "password"
                    << "|\n";
        std::cout << "|-------------------------------------|\n";
        for (const auto& user : m_users) {
            std::cout << "|" << std::setw(5)
                      << std::setw(10) << user.username 
                      << "|" << std::setw(10) << user.userType 
                      << "|" << std::setw(15) << user.password
                      << "|\n";
        }
        std::cout << "|-------------------------------------|\n\n";
    }

private:
    struct Users
    {
        std::string username;
        std::string password;
        std::string userType;
    };

    std::vector<Users> m_users;
    bool m_connected {false};
};
}

// Sarrogate of the actual server user db
class ProxyUserDatabase : public IUserDatabase
{
public:
    enum class UserType
    {
        Admin,
        Regular,
    };

    ProxyUserDatabase(UserType userType)
        : m_userType(userType)
    {
        std::cout << "Connecting to amazon server...\n";
        amazonUserDb.connect();
        std::cout << "Connected!\n";
    }

    ~ProxyUserDatabase()
    {
        std::cout << "Disconnecting from amazon server...\n";
        amazonUserDb.disConnect();
        std::cout << "Disconnected!\n";
    }

    void readAllpassword() const override
    {
        // Additional check is done here this is access control
        if (m_userType == UserType::Admin) {
            amazonUserDb.readAllpassword();
        } else {
            std::cerr << "You don't have permission to read the credentials \n";
        }
    }

    void readAllUserNames() const override
    {
        amazonUserDb.readAllUserNames();
    }
private:
    AmazonServer::UserDatabase amazonUserDb; // Contains actual instance
    UserType m_userType;
};


int main()
{
    // Regular one which connects to the server
    // AmazonServer::UserDatabase db;
    // db.connect();
    // db.readAllUserNames();
    // db.readAllpassword();

    // db.disconnect(); // if we forget this, then dangle connection

    // Using proxy which has advantage of validating the stuffs
    ProxyUserDatabase pdb(ProxyUserDatabase::UserType::Admin);
    pdb.readAllpassword();
    pdb.readAllUserNames();

    return 0;
}