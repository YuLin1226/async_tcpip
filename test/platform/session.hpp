#include <iostream>
#include <boost/asio.hpp>
#include <string.h>
#include <boost/thread/mutex.hpp>




class session : public std::enable_shared_from_this<session>
{
public:

    session(boost::asio::ip::tcp::socket&& socket, boost::asio::io_context& io_context);

    ~session();

    void writeRobotArmMoveCommand(  std::string vehicle_state, 
                                    std::string send_mission,
                                    std::string send_mission_state, 
                                    std::string reply_mission,
                                    std::string reply_mission_state,
                                    std::string vehicle_position_state,
                                    std::string recipe,
                                    std::string tray_number);

    // void start()
    // {
    //     writeMsg();
    //     boost::asio::async_read_until(socket, 
    //                                   streambuf_, 
    //                                   "e$", 
    //                                   [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
    //     {
    //         std::cout << std::istream(&self->streambuf_).rdbuf();
    //     });
    // }

    void initialization();
    void readRobotArmResponse(  std::string vehicle_state, 
                                std::string send_mission,
                                std::string send_mission_state, 
                                std::string reply_mission,
                                std::string reply_mission_state,
                                std::string vehicle_position_state,
                                std::string recipe,
                                std::string tray_number, 
                                std::vector<char>& char_vector, 
                                int& read_status);

    void readRobotArmResponse(std::vector<char>&char_vector, int& read_status);

    std::string getMoveCMD(const int move_id);
    std::string getMoveCMD( std::string vehicle_state, 
                            std::string send_mission,
                            std::string send_mission_state, 
                            std::string reply_mission,
                            std::string reply_mission_state,
                            std::string vehicle_position_state,
                            std::string recipe,
                            std::string tray_number);
    std::string getMoveREPLY(   std::string platform_state, 
                                std::string send_mission,
                                std::string send_mission_state, 
                                std::string reply_mission,
                                std::string reply_mission_state,
                                std::string platform_position_state,
                                std::string recipe,
                                std::string trouble_shooting);



private:

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf streambuf_;
    std::shared_ptr<boost::asio::deadline_timer> timeout_;
    std::shared_ptr<boost::mutex> mutex_;
    
};

