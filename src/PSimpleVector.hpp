#pragma once

#include "base_packet.hpp"

namespace woo200
{
    template<class T>
    class PSimpleVector : public Packet
    {
        template <class T2>
        class Proxy
        {
            private:
                PSimpleVector* vectorClass;
                int index;
            public:
                Proxy(PSimpleVector* vectorClass, int index) {
                    this->vectorClass = vectorClass;
                    this->index = index;
                }
                operator T2() {
                    return this->vectorClass->get(this->index);
                }
                Proxy& operator=(T2 value) {
                    this->vectorClass->set(this->index, value);
                    return *this;
                }
        };
        
        private:
            std::string get_i_data() {
                std::string header = Packet::get_i_data();
                for (unsigned int i = 0; i < *this->size_field; i++)
                    header += std::string((char*)&this->value[i], sizeof(T));
                return header;
            }
            int read_i_data(ClientSocket &socket) {
                Packet::read_i_data(socket);
                this->resize(*this->size_field);

                for (unsigned int i = 0; i < *this->size_field; i++)
                    if (socket.recv((char*)&this->value[i], sizeof(T)) < 0)
                        return -1;
                return 0;
            }
            void resize(int size) {
                *this->size_field = size;
                T* newBlock = (T*) realloc(this->value, sizeof(T) * size);
                if (newBlock == NULL)
                {
                    newBlock = (T*) malloc(sizeof(T) * size);
                    memcpy(newBlock, this->value, sizeof(T) * *this->size_field);
                    free(this->value);
                }
                this->value = newBlock;
            }
            T* value;
            PObj<unsigned int>* size_field;

        public:
            PSimpleVector(int size = 0) {
                this->value = (T*) malloc(sizeof(T) * size);

                this->size_field = new PObj<unsigned int>(size);
                this->add_field(this->size_field);
            }
            ~PSimpleVector() {
                free(this->value);
            }
            void set(int index, T value) {
                this->value[index] = value;
            }
            T& get(int index) {
                return this->value[index];
            }
            Proxy<T> operator[](int index) {
                return Proxy<T>(this, index);
            }
            unsigned int vector_size() {
                return *this->size_field;
            }
            void push_back(T value) {
                this->resize(++*this->size_field);
                this->value[*this->size_field-1] = value;
            }
            void pop_back() {
                this->resize(--*this->size_field);
            }
            void clear() {
                this->resize(0);
            }
    };
}
