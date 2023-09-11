#include "base_packet.hpp"

namespace woo200
{
    Packet::Packet()
    {
        this->size = 0;
        this->index = 0;

        this->packets = std::vector<Packet*>();
        this->packets.push_back(this);
    }
    Packet Packet::operator/(Packet &packet)
    {
        this->packets.push_back(&packet);
        return *this;
    }
    Packet* Packet::next()
    {
        if (this->index >= this->packets.size())
            return nullptr;
        return this->packets[this->index++];
    }

    // Virtual Function
    std::string Packet::get_i_data()
    {
        return "";
    }
    // Virtual Function
    void Packet::read_i_data(ClientSocket &socket)
    {
        return;
    }

    std::string Packet::get_data()
    {
        std::string final_data;

        for (unsigned long i = 0; i < this->packets.size(); i++)
            final_data.append(this->packets[i]->get_i_data());

        this->size = final_data.size();
        return final_data;
    }

    void Packet::read_from_socket(ClientSocket &socket)
    {
        for (unsigned long i = 0; i < this->packets.size(); i++)
            this->packets[i]->read_i_data(socket);
    }
    int Packet::send_to_socket(ClientSocket &socket)
    {
        return socket.send((void*)this->get_data().c_str(), this->get_size());
    }

    int Packet::get_size()
    {
        if (this->size == 0)
            this->get_data();
        return this->size;
    }

    PInt::PInt(int value)
    {
        this->value = value;
    }
    void PInt::read_i_data(ClientSocket &socket)
    {
        socket.recv((char*)&this->value, sizeof(this->value));
    }
    std::string PInt::get_i_data() 
    {
        return std::string((char*)&this->value, sizeof(this->value));
    }
    int PInt::get_value()
    {
        return this->value;
    }
    void PInt::set_value(int value)
    {
        this->value = value;
    }

    PString::PString(std::string data)
    {
        this->data = data;
    }
    void PString::read_i_data(ClientSocket &socket)
    {
        unsigned short size;
        socket.recv((unsigned short*)&size, sizeof(size));

        char* data = new char[size];
        socket.recv(data, size);

        this->data = std::string(data, size);
    }
    std::string PString::get_i_data()
    {
        unsigned short size = this->data.size();
        return std::string((char*)&size, sizeof(size)) + this->data;
    }
    std::string PString::get_value()
    {
        return this->data;
    }
    void PString::set_value(std::string data)
    {
        this->data = data;
    }
    
}