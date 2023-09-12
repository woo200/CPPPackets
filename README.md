# CPP Packets

## Introduction

CPP Packets is a flexible and efficient C++ library designed for high-level communication of complex data structures over a TCP socket. It not only provides a smooth and intuitive way to handle socket communication, but also offers an API to create custom packets for your specific needs.

## Features

- High-level socket client and server implementation
- Flexible packet building API
- Efficient communication of complex data structures
- Simplified error handling and connectivity checks

### Examples

You can find examples of client/server communication with packets in the examples folder. 

## Getting Started

### 1. Setting up the Library

`git clone https://github.com/woo200/CPPPackets.git`
`cd CPPPackets`
`make`
`sudo make install`

### 2. Create Custom Packet Classes

The core feature of the CPP Packets library is the ability to define your own packet classes, allowing for easy communication of custom data structures. Here's a brief guide on how to do this:

#### 2.1. Inheritance

Your custom packet class should inherit from the base `Packet` class. This provides basic functionality and interfaces for serialization and deserialization of packets.

#### 2.2. Private Fields

Define any necessary private fields. For simpler types, use provided classes such as `PString` for strings or `PObj<T>` for other objects. 

#### 2.3. Public Functions

Implement necessary public functions to set and get data. This abstracts the internal representation and provides an interface for the user.

#### 2.4. Serialization and Deserialization

Override `get_i_data()` for serializing the packet data into a string format and `read_i_data(ClientSocket &socket)` for deserializing data from the socket into the packet's fields.

#### 2.5 Fields

Fields are ways to package multiple packet parts into a single class. The method `this->add_field(Packet* field);` is used to adding fields, and should only be called in the constructor. When using fields, you CANNOT override `get_i_data` or `read_i_data`, otherwise the fields will be ignored. 
Example:
```cpp
class PFileHeader : public Packet
{
    private:
        PString* filename;
        PObj<unsigned long>* size;
    public:
        PFileHeader(std::string filename = "", unsigned long size = 0);
        ~PFileHeader();

        std::string get_filename();
        unsigned long get_filesize();
        void set_filename(std::string filename);
        void set_filesize(unsigned long size);
};

PFileHeader::PFileHeader(std::string filename, unsigned long size)
{
    this->filename = new PString(filename);
    this->size = new PObj<unsigned long>(size);

    this->add_field(this->filename);
    this->add_field(this->size);
}
PFileHeader::~PFileHeader() 
{
    delete this->filename;
    delete this->size;
}
// The rest of the implimentations here
```

### 3. Using the Library

Once your custom packet classes are set up, you can utilize the `ClientSocket` and `ServerSocket` classes for communication. 

- `ClientSocket` and `ServerSocket` provide functions for connection, sending and receiving data, and disconnecting.
- Packets can be sent and received seamlessly without worrying about underlying socket operations.

## API Reference

### Packet Class

- `read_from_socket(ClientSocket &socket)`: Reads packet data from the socket.
- `send_to_socket(ClientSocket &socket)`: Sends packet data to the socket.
- `get_data()`: Gets the full data of the packet.
- `get_size()`: Gets the size of the packet data.

### PObj<T>

- A templated class for objects.
- Use `get_value()` and `set_value(T value)` to manipulate the contained data.

### PString

- A specialized class for string data.
- Offers functions `get_value()` and `set_value(std::string data)` to get and set the string respectively.

### ClientSocket and ServerSocket

- High-level classes for TCP socket communication.
- Functions include `connect()`, `send()`, `recv()`, and `close()`.