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
                std::string vehicle_state, send_mission, send_mission_state, reply_mission, reply_mission_state, vehicle_postion_state, recipe, tray_number;
                std::cout << "\n>>> Enter vehicle_state (0-3): ";
                std::getline(std::cin, vehicle_state);

                std::cout << "\n>>> Enter send_mission (0-20): ";
                std::getline(std::cin, send_mission);

                std::cout << "\n>>> Enter send_mission_state (0-2): ";
                std::getline(std::cin, send_mission_state);

                std::cout << "\n>>> Enter reply_mission (0-2): ";
                std::getline(std::cin, reply_mission);

                std::cout << "\n>>> Enter reply_mission_state (0-2): ";
                std::getline(std::cin, reply_mission_state);

                std::cout << "\n>>> Enter vehicle_postion_state (0-1): ";
                std::getline(std::cin, vehicle_postion_state);

                std::cout << "\n>>> Enter recipe (name): ";
                std::getline(std::cin, recipe);

                std::cout << "\n>>> Enter tray_number (0-24 or empty): ";
                std::getline(std::cin, tray_number);

                try
                {
                    int read_status;
                    std::vector<char> data;
                    srv.getSession()->writeRobotArmMoveCommand(
                        vehicle_state,
                        send_mission,
                        send_mission_state,
                        reply_mission,
                        reply_mission_state,
                        vehicle_postion_state,
                        recipe,
                        tray_number);

                    srv.getSession()->readRobotArmResponse(
                        "0",
                        "0",
                        "0",
                        send_mission,
                        "0",
                        "0",
                        recipe,
                        "0", 
                        data,
                        read_status);
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