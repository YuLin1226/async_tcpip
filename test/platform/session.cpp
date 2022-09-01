#include "session.hpp"
#include <iostream>
#include <typeinfo>

// namespace

    session::session(boost::asio::ip::tcp::socket&& socket, boost::asio::io_context& io_context)        
    : socket_(std::move(socket))
    , io_context_(io_context)
    {
        std::cout << "*** Create session. ***" << std::endl;
        initialization();
    }
    
    session::~session()
    {
        std::cout << "*** Session eliminated. ***" << std::endl;
    }

    void session::initialization()
    {
        std::cout << "*** Session initialized. ***" << std::endl;
        timeout_ = std::shared_ptr<boost::asio::deadline_timer>{new boost::asio::deadline_timer(io_context_)};
        mutex_   = std::shared_ptr<boost::mutex>{new boost::mutex};
    }

    std::string session::getMoveCMD(const int move_id)
    {
        std::string move_cmd;
        
        switch (move_id)
        {
            // active robot arm program.
            case 1: 
                move_cmd = "$1,active,0,0,move$";
                break;
            // robot arm run "alignment"
            case 2: 
                move_cmd = "$2,align,0,0,move$";
                break;
            default:
                move_cmd = "";
                break;
        }

        return move_cmd;
    }

    std::string session::getMoveCMD(std::string vehicle_state, 
                                 std::string send_mission,
                                 std::string send_mission_state, 
                                 std::string reply_mission,
                                 std::string reply_mission_state,
                                 std::string vehicle_position_state,
                                 std::string recipe,
                                 std::string tray_number)
    {
        std::string cmd;
        cmd += "@";
        cmd += "0}" + vehicle_state + ",";
        cmd += "1}" + send_mission + ",";
        cmd += "2}" + send_mission_state + ",";
        cmd += "3}" + reply_mission + ",";
        cmd += "4}" + reply_mission_state + ",";
        cmd += "5}" + vehicle_position_state + ",";
        cmd += "6}" + recipe + ",";
        cmd += "7}" + tray_number;
        cmd += "#";

        return cmd;
    }

    std::string session::getMoveREPLY(  std::string platform_state, 
                                        std::string send_mission,
                                        std::string send_mission_state, 
                                        std::string reply_mission,
                                        std::string reply_mission_state,
                                        std::string platform_position_state,
                                        std::string recipe,
                                        std::string trouble_shooting)
    {
        std::string reply;
        reply += "@";
        reply += "0}" + platform_state + ",";
        reply += "1}" + send_mission + ",";
        reply += "2}" + send_mission_state + ",";
        reply += "3}" + reply_mission + ",";
        reply += "4}" + reply_mission_state + ",";
        reply += "5}" + platform_position_state + ",";
        reply += "6}" + recipe + ",";
        reply += "7}" + trouble_shooting;
        reply += "#";

        return reply;
    }

    void session::writeRobotArmMoveCommand( std::string vehicle_state, 
                                            std::string send_mission,
                                            std::string send_mission_state, 
                                            std::string reply_mission,
                                            std::string reply_mission_state,
                                            std::string vehicle_position_state,
                                            std::string recipe,
                                            std::string tray_number)
    {
        auto move_cmd = getMoveCMD(vehicle_state, send_mission, send_mission_state, reply_mission, reply_mission_state, vehicle_position_state, recipe, tray_number);

        if(move_cmd == "")
        {
            std::cout << "[Output] Error: Wrong command id.\n";
            return;
        }

        std::cout << "[Output] Send command: " << move_cmd << "\n";

        boost::asio::async_write(
            socket_,
            boost::asio::buffer(move_cmd + "\r\n"),
            [&](boost::system::error_code error, std::size_t bytes_transferred)
            {
                // cout bug, can't print out move_id correctly.
                // std::cout << "[Output] Send command: " << move_id << "\n";
            });
    }

    void session::readRobotArmResponse( std::string vehicle_state, 
                                        std::string send_mission,
                                        std::string send_mission_state, 
                                        std::string reply_mission,
                                        std::string reply_mission_state,
                                        std::string vehicle_position_state,
                                        std::string recipe,
                                        std::string tray_number, 
                                        std::vector<char>& char_vector, 
                                        int& read_status)
    {
        
        int data_size = getMoveREPLY(vehicle_state, send_mission, send_mission_state, reply_mission, reply_mission_state, vehicle_position_state, recipe, tray_number).length();
        auto self(shared_from_this());
        read_status = 0;
        char_vector = std::vector<char>(data_size);

        try
        {
            boost::mutex::scoped_lock scoped_locker(*mutex_);
            boost::asio::async_read( 
                socket_, 
                boost::asio::buffer(char_vector, data_size),
                [&](const boost::system::error_code &error, std::size_t bytes_transferred)
                {
                    if (error)
                    {
                        read_status = -1;
                        std::cerr << "[Output] readCallback Error " << error << std::endl;
                    }
                    else
                    {
                        read_status = 1;
                        timeout_->cancel();
                    }
                });
            
            timeout_->expires_from_now(boost::posix_time::seconds(20));
            timeout_->async_wait(  
                [&](const boost::system::error_code &error)
                {
                    if (!error)
                    {
                        socket_.cancel();
                        std::cerr << "[Output] Read timeout." << std::endl;
                    }
                    else
                    {
                        std::cerr << "[Output] Timer destroyed." << std::endl;
                    }
                });
        }
        catch(const std::exception& e)
        {
            std::cerr << "[Output] Read exception. " << e.what() << '\n';
        }
        
        

    }

    void session::readRobotArmResponse(std::vector<char>& char_vector, int& read_status)
    {

        auto self(shared_from_this());
        read_status = 0;
        // char_vector = std::vector<char>(data_size);
        boost::asio::streambuf streambuf;
        try
        {
            boost::mutex::scoped_lock scoped_locker(*mutex_);

            boost::asio::async_read_until(
                socket_, 
                streambuf, 
                "}#", 
            [&](boost::system::error_code error, std::size_t bytes_transferred)
            {
                if (error)
                {
                    read_status = -1;
                    std::cerr << "[Output] readCallback Error " << error << std::endl;
                }
                else
                {
                    read_status = 1;
                    timeout_->cancel();
                    char_vector = std::vector<char>(streambuf.size());
                    boost::asio::buffer_copy(boost::asio::buffer(char_vector), streambuf.data());
                    std::cout << "[Output] Received data: ";
                    for(auto& i: char_vector)
                    {
                        std::cout << i;
                    }
                    std::cout <<"\n";
                }
            });

            
            timeout_->expires_from_now(boost::posix_time::seconds(20));
            timeout_->async_wait(  
                [&](const boost::system::error_code &error)
                {
                    if (!error)
                    {
                        socket_.cancel();
                        std::cerr << "[Output] Read timeout." << std::endl;
                    }
                    else
                    {
                        std::cerr << "[Output] Timer destroyed." << std::endl;
                    }
                });
        }
        catch(const std::exception& e)
        {
            std::cerr << "[Output] Read exception. " << e.what() << '\n';
        }





        
    }


