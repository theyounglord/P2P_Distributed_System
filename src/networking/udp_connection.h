#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include <iostream>
#include <boost/asio.hpp>

class UDPConnection {
public:
    UDPConnection(const std::string& host, const std::string& port)
        : host_(host), port_(port), io_context_(), socket_(io_context_) {}

    bool bind() {
        try {
            boost::asio::ip::udp::resolver resolver(io_context_);
            boost::asio::ip::udp::endpoint endpoint = *resolver.resolve(host_, port_).begin();
            socket_.open(endpoint.protocol());
            socket_.bind(endpoint);
            std::cout << "UDP socket bound to " << host_ << ":" << port_ << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error binding UDP socket: " << e.what() << std::endl;
            return false;
        }
    }

    bool record(var cab_record, const boost::asio::ip::udp::endpoint& target) {
        try {
            socket_.send_to(boost::asio::buffer(cab_record), target);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error sending UDP message: " << e.what() << std::endl;
            return false;
        }
    }

    bool send(const std::string& message, const boost::asio::ip::udp::endpoint& target) {
        try {
            socket_.send_to(boost::asio::buffer(message), target);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error sending UDP message: " << e.what() << std::endl;
            return false;
        }
    }

    std::string receive(boost::asio::ip::udp::endpoint& sender) {
        try {
            char buffer[1024];
            size_t length = socket_.receive_from(boost::asio::buffer(buffer), sender);
            return std::string(buffer, length);
        } catch (const std::exception& e) {
            std::cerr << "Error receiving UDP message: " << e.what() << std::endl;
            return "";
        }
    }

    void close() {
        try {
            socket_.close();
            std::cout << "UDP socket closed." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error closing UDP socket: " << e.what() << std::endl;
        }
    }

private:
    std::string host_;
    std::string port_;
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
};

#endif
