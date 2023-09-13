#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    // Packet definition

    woo200::PSimpleVector<float> example_string;

    example_string.push_back(1.0f);
    example_string.push_back(2.0f);
    example_string.push_back(3.1415f);
    example_string.push_back(4.0f);

    woo200::ServerSocket socket;
    if (socket.bind("0.0.0.0", 8080) < 0)
        exit_error("E: Failed to bind to port");
    if (socket.listen(5) < 0)
        exit_error("E: Failed to listen on port");
    
    std::cout << "Listening on 0.0.0.0:8080" << std::endl;
    woo200::ClientSocket* client_socket = socket.accept();  

    example_string.read_from_socket(*client_socket);   // Send to server

    example_string.clear();
    example_string.push_back(5.0f);
    example_string.push_back(6.0f);
    example_string.push_back(7.0f);
    example_string.push_back(8.0f);

    example_string.send_to_socket(*client_socket);   // Send to servers

    socket.close();
    return 0;
}