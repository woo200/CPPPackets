#pragma once

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
                return std::string((char*)this->value, sizeof(T) * this->size);
            }
            int read_i_data(ClientSocket &socket) {
                return socket.recv((char*)this->value, sizeof(T) * this->size);
            }
            void resize(int size) {
                this->size = size;
                T* newBlock = (T*) realloc(this->value, sizeof(T) * size);
                if (newBlock == NULL)
                {
                    newBlock = (T*) malloc(sizeof(T) * size);
                    memcpy(newBlock, this->value, sizeof(T) * this->size);
                    free(this->value);
                }
                this->value = newBlock;
            }
            T* value;
            int size;
        public:
            PSimpleVector(int size = 0) {
                this->size = size;
                this->value = (T*) malloc(sizeof(T) * size);
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
            int vector_size() {
                return this->size;
            }
            void push_back(T value) {
                this->resize(++this->size);
                this->value[this->size-1] = value;
            }
            void pop_back() {
                this->resize(--this->size);
            }
            void clear() {
                this->resize(0);
            }
    };
}
