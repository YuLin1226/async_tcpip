#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "session/session_robot_arm.hpp"
#include "session/session_platform.hpp"
#include <memory>


class TCPServer
{
private:

    const unsigned int ROBOTARM_PORT = 9999;
    const unsigned int PLATFORM_PORT = 8888;

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor robotarm_acceptor_;
    boost::asio::ip::tcp::acceptor platform_acceptor_;

    std::shared_ptr<Session::SessionPlatform> platform_session_;
    std::shared_ptr<Session::SessionRobotArm> robotarm_session_;

    std::mutex mtx_;

    std::shared_ptr<boost::asio::ip::tcp::socket> platform_socket_ptr_;
    std::shared_ptr<boost::asio::ip::tcp::socket> robotarm_socket_ptr_;

public:
    TCPServer(boost::asio::io_context& io_context);
    
    ~TCPServer();

    /**
     * @brief accept client to make connection.
     */
    void accept();
    void robotarm_accept();
    void platform_accept();

    std::shared_ptr<Session::SessionPlatform> getPlatformSession();
    std::shared_ptr<Session::SessionRobotArm> getRobotArmSession();

};



#endif






