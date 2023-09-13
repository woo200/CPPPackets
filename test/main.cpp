#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    // Packet definition

    woo200::PSimpleVector<unsigned short> example_string;

    example_string.push_back(5);
    example_string.push_back(6);
    example_string.push_back(7);
    example_string.push_back(8);

    woo200::ClientSocket socket;
    if (socket.connect(8080,"127.0.0.1") < 0)
        exit_error("E: Failed to connect to server");

    example_string.send_to_socket(socket);   // Send to servers
    example_string.read_from_socket(socket); // Read from server

    for (unsigned int i = 0; i < example_string.vector_size(); i++)
        std::cout << "NUMBER: " << example_string[i] << std::endl;

    socket.close();
    return 0;
}
