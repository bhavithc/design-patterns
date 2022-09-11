#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

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

class Chain
{
public:
    virtual void validate(const Email& email) = 0;
    virtual void setNextChain(std::shared_ptr<Chain> pNextChain) = 0;
};

class SpamValidator : public Chain
{
public:
    void validate(const Email& email)
    {
        if (email.body().find("buy") != std::string::npos) {
            std::cout << "Given email is a Spam\n";
        } else {
            if (m_pNextChain) {
                m_pNextChain->validate(email);
            } else {
                std::cerr << "Give email seems normal, because next validator is not set !\n";
            }
        }
    }

    void setNextChain(std::shared_ptr<Chain> pNextChain)
    {
        this->m_pNextChain = pNextChain;
    }
private:
    std::shared_ptr<Chain> m_pNextChain = {};
};

class RequestValidator : public Chain
{
public:
    void validate(const Email& email)
    {
        if (email.body().find("request") != std::string::npos) {
            std::cout << "Given email is a Request\n";
        } else {
            if (m_pNextChain) {
                m_pNextChain->validate(email);
            } else {
                std::cerr << "Give email seems normal, because next validator is not set !\n";
            }
        }
    }

    void setNextChain(std::shared_ptr<Chain> pNextChain)
    {
        this->m_pNextChain = pNextChain;
    }
private:
    std::shared_ptr<Chain> m_pNextChain = {};
};

class ComplaintValidator : public Chain
{
public:
    void validate(const Email& email)
    {
        if (email.body().find("sorry") != std::string::npos) {
            std::cout << "Given email is a Complaint\n";
        } else {
            if (m_pNextChain) {
                m_pNextChain->validate(email);
            } else {
                std::cerr << "Give email seems normal, because next validator is not set !\n";
            }
        }
    }

    void setNextChain(std::shared_ptr<Chain> pNextChain)
    {
        this->m_pNextChain = pNextChain;
    }
private:
    std::shared_ptr<Chain> m_pNextChain = {};
};

class PraiseValidator : public Chain
{
public:
    void validate(const Email& email)
    {
        if (email.body().find("happy") != std::string::npos) {
            std::cout << "Given email is a Praise\n";
        } else {
            std::cout << "Given email is a normal email\n";
        }
    }

    void setNextChain(std::shared_ptr<Chain> pNextChain)
    {
        this->m_pNextChain = pNextChain;
    }
private:
    std::shared_ptr<Chain> m_pNextChain = {};
};


class EmailValidator
{
public:
    EmailValidator()
        : m_pSpamValidator(std::make_shared<SpamValidator>())
        , m_pComplaintValidator(std::make_shared<ComplaintValidator>())
        , m_pRequestValidator(std::make_shared<RequestValidator>())
        , m_pPraiseValidator(std::make_shared<PraiseValidator>())
    {
        buildChain();
    }

    void validate(const Email& email) 
    {
        if (m_pSpamValidator) {
            m_pSpamValidator->validate(email);
        }
    }
private:

    void buildChain()
    {
        m_pSpamValidator->setNextChain(m_pRequestValidator);
        m_pRequestValidator->setNextChain(m_pComplaintValidator);
        m_pComplaintValidator->setNextChain(m_pPraiseValidator);
    }

    std::shared_ptr<SpamValidator> m_pSpamValidator;
    std::shared_ptr<RequestValidator> m_pRequestValidator;
    std::shared_ptr<ComplaintValidator> m_pComplaintValidator;
    std::shared_ptr<PraiseValidator> m_pPraiseValidator;
};


int main()
{
    Email e1("bhavithc@gmail.com", "Please buy", "If you miss the chance you never get it again, buy it now!", "Bhavith C");
    Email e2("bhavithc@gmail.com", "Happy about producet", "We are very much happy with you product", "Bhavith C");
    Email e3("bhavithc@gmail.com", "Its not working", "We are sorry to say this it is not working", "Bhavith C");
    Email e4("bhavithc@gmail.com", "Request to update my data", "We request you to update the data in your data base", "Bhavith C");

    EmailValidator emailValidator;
    e1.showEmail();
    emailValidator.validate(e1);
    std::cout << "----------------\n\n";

    e2.showEmail();
    emailValidator.validate(e2);
    std::cout << "----------------\n\n";

    e3.showEmail();
    emailValidator.validate(e3);
    std::cout << "----------------\n\n";

    e4.showEmail();
    emailValidator.validate(e4);
    std::cout << "----------------\n\n";

    return 0;
}