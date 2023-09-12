#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    // Packet definition
    woo200::PFileHeader file_header;

    file_header.set_filename("test.txt");
    file_header.set_filesize(1234);

    woo200::ClientSocket socket;
    if (socket.connect(8080, "127.0.0.1") < 0)
        exit_error("E: Failed to connect to server");

    file_header.send_to_socket(socket);   // Send to server
    file_header.read_from_socket(socket); // Wait for server response

    std::cout << file_header.get_filename() << std::endl;
    std::cout << file_header.get_filesize() << std::endl;

    socket.close();

    return 0;
}