#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "session/session_robot_arm.hpp"
#include "session/session_platform.hpp"


class TCPServer
{
private:

    const unsigned int ROBOTARM_PORT = 9999;
    const unsigned int PLATFORM_PORT = 8888;

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor robot_arm_acceptor_;
    boost::asio::ip::tcp::acceptor platform_acceptor_;
    std::shared_ptr<boost::asio::ip::tcp::socket> robot_arm_socket_ptr_;
    std::shared_ptr<boost::asio::ip::tcp::socket> platform_socket_ptr_;

public:
    TCPServer(boost::asio::io_context& io_context);
    
    ~TCPServer();

    /**
     * @brief accept client to make connection.
     */
    void accept();
    void robot_arm_accept();
    void platform_accept();

    void readFromSpecifiedClient(Session* session);
    void writeToSpecifiedClient(Session* session);


};










