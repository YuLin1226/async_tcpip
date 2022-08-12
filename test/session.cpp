#include "session.hpp"

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

    void session::writeRobotArmMoveCommand(const int move_id)
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
            // robot arm run "no1 drill above"
            case 11:
                move_cmd = "$11,1,drillabove,0,move$";
                break;
            // robot arm run "no1 drill workplace"
            case 12:
                move_cmd = "$12,1,drillworkplace,0,move$";
                break;
            // robot arm run "no1 drill safe"
            case 13:
                move_cmd = "$13,1,drillsafe,0,move$";
                break;
            // robot arm run "no2 drill above"
            case 21:
                move_cmd = "$21,2,drillabove,0,move$";
                break;
            // robot arm run "no2 drill workplace"
            case 22:
                move_cmd = "$22,2,drillworkplace,0,move$";
                break;
            // robot arm run "no2 drill safe"
            case 23:
                move_cmd = "$23,2,drillsafe,0,move$";
                break;
            // robot arm run "no3 drill above"
            case 31:
                move_cmd = "$31,3,drillabove,0,move$";
                break;
            // robot arm run "no3 drill workplace"
            case 32:
                move_cmd = "$32,3,drillworkplace,0,move$";
                break;
            // robot arm run "no3 drill safe"
            case 33:
                move_cmd = "$33,3,drillsafe,0,move$";
                break;
            // robot arm run "no4 drill above"
            case 41:
                move_cmd = "$41,4,drillabove,0,move$";
                break;
            // robot arm run "no4 drill workplace"
            case 42:
                move_cmd = "$42,4,drillworkplace,0,move$";
                break;
            // robot arm run "no4 drill safe"
            case 43:
                move_cmd = "$43,4,drillsafe,0,move$";
                break;
            // robot arm run "no5 drill above"
            case 51:
                move_cmd = "$51,5,drillabove,0,move$";
                break;
            // robot arm run "no5 drill workplace"
            case 52:
                move_cmd = "$52,5,drillworkplace,0,move$";
                break;
            // robot arm run "no5 drill safe"
            case 53:
                move_cmd = "$53,5,drillsafe,0,move$";
                break;
            // robot arm run "no6 drill above"
            case 61:
                move_cmd = "$61,6,drillabove,0,move$";
                break;
            // robot arm run "no6 drill workplace"
            case 62:
                move_cmd = "$62,6,drillworkplace,0,move$";
                break;
            // robot arm run "no6 drill safe"
            case 63:
                move_cmd = "$63,6,drillsafe,0,move$";
                break;
            // robot arm run "go home"
            case 99:
                move_cmd = "$99,safe,0,0,move$";
                break;
            // robot arm run "pcb above (get target)"
            case 100:
                move_cmd = "$100,pcbabove,0,0,move$";
                break;
            // robot arm run "pcb x position (get target)"
            case 101:
                move_cmd = "$101,pcbworkplace,0,x,move$";
                break;
            // robot arm run "pcb safe (get target)"
            case 102:
                move_cmd = "$102,pcbsafe,0,0,move$";
                break;
            // robot arm run "pcb above (place target)"
            case 103:
                move_cmd = "$103,pcbabove,0,0,move$";
                break;
            // robot arm run "pcb x position (place target)"
            case 104:
                move_cmd = "$104,pcbworkplace,0,x,move$";
                break;
            // robot arm run "pcb safe (place target)"
            case 105:
                move_cmd = "$105,pcbsafe,0,0,move$";
                break;

            default:
                move_cmd = "";
                break;
        }

        if(move_cmd == "")
        {
            std::cout << "[Output] Error: Wrong command id.\n";
            return;
        }

        std::cout << "[Output] Send command: " << move_id << "\n";

        boost::asio::async_write(
            socket_,
            boost::asio::buffer(move_cmd + "\r\n"),
            [&](boost::system::error_code error, std::size_t bytes_transferred)
            {
                // cout bug, can't print out move_id correctly.
                // std::cout << "[Output] Send command: " << move_id << "\n";
            });
    }

    std::vector<char> session::readRobotArmResponse(const int move_id)
    {
        
        int data_size;
        switch (move_id)
        {
            // active robot arm program.
            case 1: 
                data_size = 20;
                break;
            // robot arm run "alignment"
            case 2: 
                data_size = 19;
                break;
            // robot arm run "no1 drill above"
            case 11:
                data_size = 25;
                break;
            // robot arm run "no1 drill workplace"
            case 12:
                data_size = 29;
                break;
            // robot arm run "no1 drill safe"
            case 13:
                data_size = 24;
                break;
            // robot arm run "no2 drill above"
            case 21:
                data_size = 25;
                break;
            // robot arm run "no2 drill workplace"
            case 22:
                data_size = 29;
                break;
            // robot arm run "no2 drill safe"
            case 23:
                data_size = 24;
                break;
            // robot arm run "no3 drill above"
            case 31:
                data_size = 25;
                break;
            // robot arm run "no3 drill workplace"
            case 32:
                data_size = 29;
                break;
            // robot arm run "no3 drill safe"
            case 33:
                data_size = 24;
                break;
            // robot arm run "no4 drill above"
            case 41:
                data_size = 25;
                break;
            // robot arm run "no4 drill workplace"
            case 42:
                data_size = 29;
                break;
            // robot arm run "no4 drill safe"
            case 43:
                data_size = 24;
                break;
            // robot arm run "no5 drill above"
            case 51:
                data_size = 25;
                break;
            // robot arm run "no5 drill workplace"
            case 52:
                data_size = 29;
                break;
            // robot arm run "no5 drill safe"
            case 53:
                data_size = 24;
                break;
            // robot arm run "no6 drill above"
            case 61:
                data_size = 25;
                break;
            // robot arm run "no6 drill workplace"
            case 62:
                data_size = 29;
                break;
            // robot arm run "no6 drill safe"
            case 63:
                data_size = 24;
                break;
            // robot arm run "go home"
            case 99:
                data_size = 19;
                break;
            // robot arm run "pcb above (get target)"
            case 100:
                data_size = 24;
                break;
            // robot arm run "pcb x position (get target)"
            case 101:
                data_size = 28;
                break;
            // robot arm run "pcb safe (get target)"
            case 102:
                data_size = 23;
                break;
            // robot arm run "pcb above (place target)"
            case 103:
                data_size = 24;
                break;
            // robot arm run "pcb x position (place target)"
            case 104:
                data_size = 28;
                break;
            // robot arm run "pcb safe (place target)"
            case 105:
                data_size = 23;
                break;

            default:
                data_size = 0;
                break;
        }

        auto self(shared_from_this());
        bool data_available = false;
        std::vector<char> char_vector(data_size);

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
                        data_available = false;
                        std::cerr << "[Output] readCallback Error " << error << std::endl;
                    }
                    std::cout << "[Output] Reading finished and cancel timer.\n";
                    timeout_->cancel();
                    data_available = true;
                });
            
            timeout_->expires_from_now(boost::posix_time::seconds(20));
            // timeout_->async_wait(  
            //     [&](const boost::system::error_code &error)
            //     {
            //         if (!error)
            //         {
            //             data_available = false;
            //             socket_.cancel();
            //             std::cerr << "[Output] Read timeout." << std::endl;
            //         }
            //     });
            timeout_->wait();
            if(!data_available)
            {
                socket_.cancel();
                std::cerr << "[Output] Read timeout." << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "[Output] Read exception. " << e.what() << '\n';
        }
        

        // Although a timer is set, but this if condition is not related to io object, so it won't be blocked.
        // Hence the function quickly jumps to this if condition, and throw.
        if (data_available)
        {
            return char_vector;
        }
        else
        {
            throw "[Output] TCP reading timeout";
        }

    }

    void session::readRobotArmResponse(const int move_id, std::vector<char>& char_vector, int& read_status)
    {
        
        int data_size;
        switch (move_id)
        {
            // active robot arm program.
            case 1: 
                data_size = 20;
                break;
            // robot arm run "alignment"
            case 2: 
                data_size = 19;
                break;
            // robot arm run "no1 drill above"
            case 11:
                data_size = 25;
                break;
            // robot arm run "no1 drill workplace"
            case 12:
                data_size = 29;
                break;
            // robot arm run "no1 drill safe"
            case 13:
                data_size = 24;
                break;
            // robot arm run "no2 drill above"
            case 21:
                data_size = 25;
                break;
            // robot arm run "no2 drill workplace"
            case 22:
                data_size = 29;
                break;
            // robot arm run "no2 drill safe"
            case 23:
                data_size = 24;
                break;
            // robot arm run "no3 drill above"
            case 31:
                data_size = 25;
                break;
            // robot arm run "no3 drill workplace"
            case 32:
                data_size = 29;
                break;
            // robot arm run "no3 drill safe"
            case 33:
                data_size = 24;
                break;
            // robot arm run "no4 drill above"
            case 41:
                data_size = 25;
                break;
            // robot arm run "no4 drill workplace"
            case 42:
                data_size = 29;
                break;
            // robot arm run "no4 drill safe"
            case 43:
                data_size = 24;
                break;
            // robot arm run "no5 drill above"
            case 51:
                data_size = 25;
                break;
            // robot arm run "no5 drill workplace"
            case 52:
                data_size = 29;
                break;
            // robot arm run "no5 drill safe"
            case 53:
                data_size = 24;
                break;
            // robot arm run "no6 drill above"
            case 61:
                data_size = 25;
                break;
            // robot arm run "no6 drill workplace"
            case 62:
                data_size = 29;
                break;
            // robot arm run "no6 drill safe"
            case 63:
                data_size = 24;
                break;
            // robot arm run "go home"
            case 99:
                data_size = 19;
                break;
            // robot arm run "pcb above (get target)"
            case 100:
                data_size = 24;
                break;
            // robot arm run "pcb x position (get target)"
            case 101:
                data_size = 28;
                break;
            // robot arm run "pcb safe (get target)"
            case 102:
                data_size = 23;
                break;
            // robot arm run "pcb above (place target)"
            case 103:
                data_size = 24;
                break;
            // robot arm run "pcb x position (place target)"
            case 104:
                data_size = 28;
                break;
            // robot arm run "pcb safe (place target)"
            case 105:
                data_size = 23;
                break;

            default:
                data_size = 0;
                break;
        }

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
            
            timeout_->expires_from_now(boost::posix_time::seconds(5));
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


