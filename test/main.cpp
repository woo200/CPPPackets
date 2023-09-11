#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    // Packet definition
    woo200::PInt int_part;
    woo200::PString string_part;
    woo200::PString string_part2;

    woo200::Packet finalPacket = int_part / string_part / string_part2;

    int int_value;
    std::string string_value, string_value2;

    std::cout << "Enter an integer: ";
    std::cin >> int_value;
    std::cout << "Enter a string: ";
    std::cin >> string_value;
    std::cout << "Enter another string: ";
    std::cin >> string_value2;

    int_part.set_value(int_value);
    string_part.set_value(string_value);
    string_part2.set_value(string_value2);

    woo200::ClientSocket socket;
    if (socket.connect(8080, "127.0.0.1") < 0)
        exit_error("E: Failed to connect to server");

    finalPacket.send_to_socket(socket);   // Send to server
    finalPacket.read_from_socket(socket); // Wait for server response

    int_part =     *(woo200::PInt*)    finalPacket.next();
    string_part =  *(woo200::PString*) finalPacket.next();
    string_part2 = *(woo200::PString*) finalPacket.next();

    std::cout << int_part.get_value() << std::endl;
    std::cout << string_part.get_value() << std::endl;
    std::cout << string_part2.get_value() << std::endl;

    socket.close();

    return 0;
}