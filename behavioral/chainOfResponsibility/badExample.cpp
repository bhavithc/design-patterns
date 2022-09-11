#include <iostream>
#include <string>
#include <algorithm>

class Email
{
public:
    Email(const std::string& from, const std::string& subj, const std::string body, const std::string signature)
        : m_from(from)
        , m_subj(subj)
        , m_body(body)
        , m_sign(signature)
    {
        formatEmail();
    }

    void formatEmail()
    {
        m_email += "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        m_email += "\tFrom: " + m_from + "\n";
        m_email += "\t------------------\n";
        m_email += "\tSub: " + m_subj + "\n";
        m_email += "\t------------------\n"; 
        m_email += "\tContent:\n";      
        m_email += "\t    " + m_body + "\n";
        m_email += "\n\t------------------\n";
        m_email += "\t" + m_sign + "\n";
        m_email += "\t------------------\n";
    }

    void showEmail()
    {
        std::cout << m_email;
    }

    std::string email() const 
    {
        return m_email;
    }
    std::string from() const 
    {
        return m_from;
    }

    std::string subject() const 
    {
        return m_subj;
    }

    std::string body() const
    {
        return m_body;
    }

    std::string signature() const
    {
        return m_sign;
    }

private:
    std::string m_email = "";
    std::string m_from = "";
    std::string m_subj = "";
    std::string m_body = "";
    std::string m_sign = "";
};

class AIEmailValidator
{
public:
    enum class EmailType
    {
        Spam,
        Complaint,
        Request,
        Praise,
        Normal,
    };

    const char* emailTypeToStr(EmailType emailType) 
    {
        if (emailType == EmailType::Spam) {
            return "Spam";
        }

        if (emailType == EmailType::Request) {
            return "Request";
        }

        if (emailType == EmailType::Praise) {
            return "Praise";
        }

        if (emailType == EmailType::Normal) {
            return "Normal";
        }

        if (emailType == EmailType::Complaint) {
            return "Complaint";
        }

        return "";
    }

    EmailType validate(const Email& email) 
    {
        std::string body = email.body();

        if (body.find("buy") != std::string::npos) {
            return EmailType::Spam;
        } else if (body.find("sorry") != std::string::npos) {
            return EmailType::Complaint;
        } else if (body.find("request") != std::string::npos) {
            return EmailType::Request;
        } else if (body.find("happy") != std::string::npos) {
            return EmailType::Praise;
        }

        return EmailType::Normal;
    }
};

int main()
{
    Email e1("bhavithc@gmail.com", "Please buy", "If you miss the chance you never get it again, buy it now!", "Bhavith C");
    Email e2("bhavithc@gmail.com", "Happy about producet", "We are very much happy with you product", "Bhavith C");
    Email e3("bhavithc@gmail.com", "Its not working", "We are sorry to say this it is not working", "Bhavith C");
    Email e4("bhavithc@gmail.com", "Request to update my data", "We request you to update the data in your data base", "Bhavith C");

    AIEmailValidator emailValidator;
    auto emailType = emailValidator.validate(e1);
    e1.showEmail();
    std::cout << "^^^^^^^\n";
    std::cout << "Above email is " << emailValidator.emailTypeToStr(emailType) << "\n";
    std::cout << "-------\n\n";

    emailType = emailValidator.validate(e2);
    e2.showEmail();
    std::cout << "^^^^^^^\n";
    std::cout << "Above email is " << emailValidator.emailTypeToStr(emailType) << "\n";
    std::cout << "-------\n\n";

    emailType = emailValidator.validate(e3);
    e3.showEmail();
    std::cout << "^^^^^^^\n";
    std::cout << "Above email is " << emailValidator.emailTypeToStr(emailType) << "\n";
    std::cout << "-------\n\n";

    emailType = emailValidator.validate(e4);
    e4.showEmail();
    std::cout << "^^^^^^^\n";
    std::cout << "Above email is " << emailValidator.emailTypeToStr(emailType) << "\n";
    std::cout << "-------\n\n";

    return 0;
}