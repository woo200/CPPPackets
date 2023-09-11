#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    woo200::PInt int_part(5);
    woo200::PString string_part("Hello World!");

    woo200::Packet finalPacket = int_part / string_part;

    woo200::ClientSocket socket;
    if (socket.connect(8080, "127.0.0.1") < 0)
        exit_error("E: Failed to connect to server");

    finalPacket.send_to_socket(socket);   // Send to server
    finalPacket.read_from_socket(socket); // Wait for server response

    int_part =    *(woo200::PInt*)    finalPacket.next();
    string_part = *(woo200::PString*) finalPacket.next();

    std::cout << int_part.get_value() << std::endl;
    std::cout << string_part.get_value() << std::endl;

    socket.close();

    return 0;
}