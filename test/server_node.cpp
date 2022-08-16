#include "server.hpp"
#include <thread>
#include <chrono>
#include <sstream>

void gManualSendRobotCommand(Server& srv)
{
    while( true ) 
        {
            if(srv.getSession() == NULL)
            {
            }
            else
            {
                std::cout << "\n>>> Enter robot command id: ";
                std::string id;
                std::getline(std::cin, id);
            

                try
                {
                    int read_status;
                    std::vector<char> data;
                    srv.getSession()->writeRobotArmMoveCommand(std::stoi(id));
                    srv.getSession()->readRobotArmResponse(std::stoi(id), data, read_status);
                    while(read_status == 0)
                    {
                        // do nothing, just wait.
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    if(read_status==1)
                    {
                        std::cout << "[Output] Received data: ";
                        for(auto& i: data)
                        {
                            std::cout << i;
                        }
                        std::cout <<"\n";
                    }
                    // auto a = srv.getSession()->readRobotArmResponse(std::stoi(id));
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