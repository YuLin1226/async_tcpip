#include <iostream>
#include <boost/asio.hpp>
#include <string.h>
#include <boost/thread/mutex.hpp>




class session : public std::enable_shared_from_this<session>
{
public:

    session(boost::asio::ip::tcp::socket&& socket, boost::asio::io_context& io_context);

    ~session();

    void writeRobotArmMoveCommand(const int move_id);

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

    std::vector<char> readRobotArmResponse(const int move_id);
    void readRobotArmResponse(const int move_id, std::vector<char>& char_vector, int& read_status);
    

private:

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf streambuf_;
    std::shared_ptr<boost::asio::deadline_timer> timeout_;
    std::shared_ptr<boost::mutex> mutex_;
    
};

