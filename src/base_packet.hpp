#pragma once

#include "base_sockets.hpp"
#include <vector>

namespace woo200
{
    // BASE CLASS (Not Implimented)
    class Packet
    {
        private:
            virtual std::string get_i_data();
            std::vector<Packet*> packets;
            int size = 0;
        public:
            Packet();
            Packet(ClientSocket &socket);

            std::string get_data();
            int get_size();

            Packet operator/(Packet &packet);
    };
    
    class IntegerPacket : public Packet
    {
        private:
            std::string get_i_data();
            std::string data;
        public:
            IntegerPacket(std::string data);
            IntegerPacket(ClientSocket &socket);
    };
}
