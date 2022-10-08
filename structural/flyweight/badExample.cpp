#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Draw rectangle
// Intrensic: Color
// Extrensic: Size


class Rectangle
{
public:
    Rectangle(std::string color, int length, int breadth)
        : m_color(color)
        , m_length(length)
        , m_breadth(breadth)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    void draw()
    {
        std::cout << "Rectangle drawn with color : " 
                  << m_color << ", size: " 
                  << m_length << "x" << m_breadth << "\n";
    }
private:
    std::string m_color;
    int m_length;
    int m_breadth;
};

int main()
{
    std::string colors[] = {"red", "green", "orange", "white", "green", "yellow", "white", "pink", "green"};

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 1000; i++) {

        int randomColor = 9 * (rand() / (RAND_MAX + 1.0));
        int randomLen = 1000 * (rand() / (RAND_MAX + 1.0));
        int randomBreadth = 500 * (rand() / (RAND_MAX + 1.0));
        Rectangle rec(colors[randomColor], randomLen, randomBreadth);
        rec.draw();
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Takes lot of time
    std::cout << "Time difference = " 
             << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() 
             << "[µs]" << std::endl;
    return 0;
}