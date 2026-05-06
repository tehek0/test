#include "../shared/inc.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char** argv) {
   if (argc < 2) {
        std::cout << "server.exe <port>" << std::endl;
        return -1;
    } 

    try {
        unsigned short port = std::stoi(argv[1]);

        asio::io_context io_context;
        
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
        asio::ip::tcp::acceptor acceptor(io_context, endpoint);
        
        std::cout << "Started on port " << port << "..." << std::endl;
        
        weather types[3] = {weather::clear, weather::cloudy, weather::rain};

        while(true) {
            asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "Client connected!" << std::endl;
            char data[1024];
            std::error_code ec;
            size_t length = socket.read_some(asio::buffer(data), ec);
            
            if (!ec) {
                std::cout << "Recieve: " 
                        << std::string(data, length) << std::endl;
            } else {
                std::cout << "Error: " << ec.message() << std::endl;
            }
            
            char output_buf[2] = {0, 1};
            asio::write(socket, asio::buffer(output_buf));

            std::this_thread::sleep_for(20ms);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unhandled exception" << std::endl;
    }
}