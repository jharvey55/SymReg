#include <iostream>
#include <vector>

double bob()
{
    return 1.0f + 2.0f;
}

void sandbox1()
{
    double a = bob();
    std::cout << a << std::endl;
    double l = 4.0f;
    double r = 2.0f;
    double s = l/r;
    std::cout << s << std::endl;
}

void sandbox2()
{
    double epsilon =  4.94065645841247e-324;

    std::cout << epsilon << std::endl;    
    std::cout << (epsilon > 0) << std::endl;
    std::cout << (1.0f/epsilon) << std::endl;

}

void sandbox3() {
    // double epsilon = 4.94065645841247e-324;
    double epsilon = 1.0e-323;

    double a = 0.0f;
    double b = 1.0f / (a ? a : epsilon);

    std::cout << b << std::endl;
}

void print_container(const std::vector<int> &c) {
    for (int i: c)
        std::cout << i << " ";
    std::cout << '\n';
}

int main() {
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_container(c);
    c.erase(c.end() - 3, c.end());
    print_container(c);

    return 0;
}