#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "server.hpp"
#include "session/frame/cmd/command_platform.hpp"


void run(TCPServer& srv)
{
    std::cout << "\n>>> Wait for clients.";
    while( true ) 
    {
        if(srv.getPlatformSession() == NULL)
        {
        }
        else
        {
            std::cout << "\n>>> Enter to write command";
            std::string id;
            std::getline(std::cin, id);
        
            try
            {
                auto cmd = PlatformCommand::getCommandMessage();
                // std::array<unsigned char, 4> data{0x3, 0x1, 0x4, 0x1};
                // srv.getPlatformSession()->write(data.data(), 4);       
                srv.getPlatformSession()->write((unsigned char*)(cmd.c_str()), cmd.size());       
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        TCPServer server(io_context);
        auto io_thread = std::thread(&run, std::ref(server));
        io_context.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
