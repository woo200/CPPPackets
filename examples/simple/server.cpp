#include "server.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    // Packet definition

    woo200::PString example_string;
    woo200::PObj<int> example_int;
    woo200::PObj<float> example_float;

    woo200::Packet packet = example_string / example_int / example_float;

    woo200::ServerSocket socket;
    if (socket.bind("0.0.0.0", 8080) < 0)
        exit_error("E: Failed to bind to port");
    if (socket.listen(5) < 0)
        exit_error("E: Failed to listen on port");
    
    std::cout << "Listening on 0.0.0.0:8080" << std::endl;
    woo200::ClientSocket* client_socket = socket.accept();  

    packet.read_from_socket(*client_socket);   // Send to server 

    std::cout << "Received String: " << example_string.get_value() << std::endl;
    std::cout << "Received Int: " <<    example_int.get_value() << std::endl;
    std::cout << "Received Float: " <<  example_float.get_value() << std::endl;

    example_string.set_value("Hello back!");
    example_int.set_value(987654321);
    example_float.set_value(654.321f);

    packet.send_to_socket(*client_socket);   // Send to servers

    socket.close();
    return 0;
}