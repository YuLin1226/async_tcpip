#include "server.hpp"


void gManualSendRobotCommand(Server& srv)
{
    while( true ) 
        {
            if(srv.getSession() == NULL)
            {
            }
            else
            {
                std::cout << "Enter robot command id: ";
                std::string id;
                std::getline(std::cin, id);
                try
                {
                    srv.getSession()->writeRobotArmMoveCommand(std::stoi(id));
                    auto a = srv.getSession()->readRobotArmResponse(std::stoi(id));
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
        std::cout << ">>> Server starts" << std::endl;
        boost::asio::io_context io_context;
        int port = 6688;
        Server server(io_context, port);
        server.accept();
        auto t = std::thread(&gManualSendRobotCommand, std::ref(server));
        io_context.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}