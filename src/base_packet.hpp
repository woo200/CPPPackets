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
            virtual void read_i_data(ClientSocket &socket);

            std::vector<Packet*> packets;
            int size = 0;
            int index = 0;
        public:
            Packet();

            void read_from_socket(ClientSocket &socket);
            std::string get_data();
            int get_size();
            int send_to_socket(ClientSocket &socket);

            Packet* next();
            Packet operator/(Packet &packet);
    };
    
    class PInt : public Packet
    {
        private:
            std::string get_i_data();
            void read_i_data(ClientSocket &socket);
            int value;
        public:
            PInt(int value = 0);
            int get_value();
            void set_value(int value);
    };

    class PString : public Packet
    {
        private:
            std::string get_i_data();
            void read_i_data(ClientSocket &socket);
            std::string data;
        public:
            PString(std::string data = "");
            std::string get_value();
            void set_value(std::string data);
    };
}
