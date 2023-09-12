#include "base_packet.hpp"

namespace woo200
{
    Packet::Packet()
    {
        this->size = 0;
        this->index = 0;

        this->packets = std::vector<Packet*>();
        this->packets.push_back(this);

        this->fields = std::vector<Packet*>();
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

    // If overriden, this function should return the data for this packet only
    std::string Packet::get_i_data()
    {
        std::string final_data;

        for (unsigned long i = 0; i < this->fields.size(); i++)
            final_data.append(this->fields[i]->get_i_data());

        return final_data;
    }
    // Virtual Function
    int Packet::read_i_data(ClientSocket &socket)
    {
        for (unsigned long i = 0; i < this->fields.size(); i++)
        {
            int ret = this->fields[i]->read_i_data(socket);
            if (ret < 0)
                return ret;
        }
    }

    std::string Packet::get_data()
    {
        std::string final_data;

        for (unsigned long i = 0; i < this->packets.size(); i++)
            final_data.append(this->packets[i]->get_i_data());

        this->size = final_data.size();
        return final_data;
    }

    int Packet::read_from_socket(ClientSocket &socket)
    {
        for (unsigned long i = 0; i < this->packets.size(); i++)
        {
            int ret = this->packets[i]->read_i_data(socket);
            if (ret < 0)
                return ret;
        }   
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
    void Packet::add_field(Packet* packet)
    {
        this->fields.push_back(packet);
    }

    PString::PString(std::string data)
    {
        this->data = data;
    }
    int PString::read_i_data(ClientSocket &socket)
    {
        unsigned short size;
        if (socket.recv((unsigned short*)&size, sizeof(size)) < 0)
            return -1;

        char* data = new char[size];
        if (socket.recv(data, size) < 0)
            return -1;

        this->data = std::string(data, size);
        
        return 0;
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