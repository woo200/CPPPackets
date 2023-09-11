#include "base_packet.hpp"

namespace woo200
{
    Packet::Packet()
    {
        this->size = 0;
    }
    Packet Packet::operator/(Packet &packet)
    {
        std::cout << this->get_data() << std::endl;
        std::cout << packet.get_data() << std::endl;
        this->packets.push_back(&packet);
        return *this;
    }
    // Virtual Function
    std::string Packet::get_i_data()
    {
        return "";
    }

    std::string Packet::get_data()
    {
        std::cout << "Packet::get_data()" << std::endl;
        std::string final_data;
        final_data += this->get_i_data();
        
        for (unsigned long i = 0; i < this->packets.size(); i++)
        {
            final_data += this->packets[i]->get_i_data();
            std::cout << this->packets(\) << std::endl;
        }

        this->size = final_data.size();
        return final_data;
    }

    int Packet::get_size()
    {
        if (this->size == 0)
            this->get_data();
        return this->size;
    }

    IntegerPacket::IntegerPacket(std::string data)
    {
        this->data = data;
    }
    std::string IntegerPacket::get_i_data() 
    {
        return this->data;
    }
}