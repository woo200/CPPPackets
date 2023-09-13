#include "main.hpp"

void exit_error(std::string error)
{
    std::cout << error << std::endl;
    exit(EXIT_FAILURE);
}

int main(void)
{
    woo200::PSimpleVector<int> example_vector(5);

    example_vector[0] = 1;
    example_vector[1] = 2;
    example_vector[2] = 3;
    example_vector[3] = 4;
    example_vector[4] = 5;

    example_vector.push_back(17);

    for (int i = 0; i < example_vector.vector_size(); i++)
        std::cout << example_vector[i] << std::endl;

    std::cout << "\"" << example_vector.get_size() << "\"" << std::endl;

    return 0;
}