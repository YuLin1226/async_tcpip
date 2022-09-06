#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "server.hpp"

int main()
{
    try
    {
        std::cout << ">>> Server starts" << std::endl;
        boost::asio::io_context io_context;
    
        TCP::Server server(io_context);
        // auto io_thread = std::thread(&run, std::ref(io_context));
        io_context.run();
        // while( true ) 
        // {
        //     std::string line;
        //     std::getline(std::cin, line);
        //     if(line == "stop") 
        //     {
        //         io_context.stop();
        //         break;
        //     }
        //     else 
        //     {
        //     }
        // }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}