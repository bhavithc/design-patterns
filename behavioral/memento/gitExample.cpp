#include <iostream>
#include <random>
#include <tuple>
#include <vector>
#include <string>

class Tag // This is Memento
{
    Tag(const std::vector<std::tuple<int, std::string>>& changes)
    {
        m_changes = changes;
    }

private:
    std::vector<std::tuple<int, std::string>> m_changes;

    friend class Git;
};

class Git
{
public:
    Tag commit(const std::string& msg)
    {
        const auto commitId = std::rand();
        m_changes.emplace_back(std::make_tuple(commitId, msg));

        return {m_changes};
    }

    void checkout(const Tag& tag)
    {
        m_changes = tag.m_changes;
    }

    void log()
    {
        for (const auto& change : m_changes) {
            std::cout << std::get<0>(change) << ": " << std::get<1>(change)  << "\n";
        }
    }

private:
    std::vector<std::tuple<int, std::string>> m_changes;
};

int main()
{
    Git git;
    auto t1 = git.commit("bugfix: Fix null pointer exception");
    auto t2 = git.commit("feature: Add request handler");
    auto t3 = git.commit("feature: Add respone handler");
    auto t4 = git.commit("feature: Multiple client support");
    git.log();

    std::cout << "---------------\n";
    git.checkout(t3);
    git.log();

    return 0;
}