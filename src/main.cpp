#include "main.hpp"

int main(void)
{
    std::string data = "Hello World!";
    std::string data2 = "Hello World!(2)";
    woo200::IntegerPacket part1(data);
    woo200::IntegerPacket part2(data2);

    std::cout << (part1/part2).get_data() << std::endl;

    return 0;
}