#include "client.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    // Packet definition

    woo200::PString example_string("Hello world!");
    woo200::PObj<int> example_int(1234567890);
    woo200::PObj<float> example_float(123.456f);

    woo200::Packet packet = example_string / example_int / example_float;

    woo200::ClientSocket socket;
    if (socket.connect(8080, "127.0.0.1") < 0)
        exit_error("E: Failed to connect to server");

    packet.send_to_socket(socket);   // Send to server   
    packet.read_from_socket(socket); // Read packet (overrides existing values)

    std::cout << "Received String: " << example_string.get_value() << std::endl;
    std::cout << "Received Int: " <<    example_int.get_value() << std::endl;
    std::cout << "Received Float: " <<  example_float.get_value() << std::endl;

    socket.close();
    return 0;
}