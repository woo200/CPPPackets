#include "main.hpp"

int main(void)
{
    woo200::IntegerPacket part1;
    woo200::StringPacket part2;

    woo200::Packet packet = part1 / part2;

    std::cout << packet.get_size() << std::endl;


    return 0;
}