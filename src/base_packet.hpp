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
            virtual int read_i_data(ClientSocket &socket);

            std::vector<Packet*> packets;
            std::vector<Packet*> fields;
            int size = 0;
            unsigned long index = 0;
        protected:
            void add_field(Packet* packet);
        public:
            Packet();

            virtual int read_from_socket(ClientSocket &socket);
            virtual std::string get_data();
            virtual int get_size();
            virtual int send_to_socket(ClientSocket &socket);

            Packet* next();
            Packet operator/(Packet &packet);
    };
    
    template <class T>
    class PObj : public Packet
    {
        private:
            std::string get_i_data() {
                return std::string((char*)&this->value, sizeof(T));
            }
            int read_i_data(ClientSocket &socket) {
                socket.recv((char*)&this->value, sizeof(T));
            }
            T value;
        public:
            PObj(T value = NULL) {
                this->value = value;
            }
            T get_value() {
                return this->value;
            }
            void set_value(T value) {
                this->value = value;
            }
    };

    class PString : public Packet
    {
        private:
            std::string get_i_data();
            int read_i_data(ClientSocket &socket);
            std::string data;
        public:
            PString(std::string data = "");
            std::string get_value();
            void set_value(std::string data);
    };

}
