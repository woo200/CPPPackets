#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    woo200::IntegerPacket packet(5);
    woo200::StringPacket packet2("Hello World!");

    woo200::Packet finalPacket = packet / packet2;

    woo200::ClientSocket socket;
    if (socket.connect(80, "127.0.0.1") < 0)
        exit_error("E: Failed to connect to server");
    socket.send((void*)finalPacket.get_data().c_str(), finalPacket.get_size());

    finalPacket.read_from_socket(socket);

    packet = *(woo200::IntegerPacket*)finalPacket.next();
    packet2 = *(woo200::StringPacket*)finalPacket.next();

    std::cout << packet.get_value() << std::endl;
    std::cout << packet2.get_value() << std::endl;

    socket.close();

    return 0;
}