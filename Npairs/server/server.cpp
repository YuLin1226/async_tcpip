#include "server.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context)
: io_context_(io_context)
, robot_arm_acceptor_(io_context_, 
                      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ROBOTARM_PORT))
, platform_acceptor_(io_context_, 
                     boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PLATFORM_PORT))
{
    std::cout << ">>> Server created." << std::endl;
    accept();
}


TCPServer::~TCPServer()
{
    std::cout << ">>> Server destroyed." << std::endl;
}

void TCPServer::accept()
{
    robot_arm_accept();
    platform_accept();
}

void TCPServer::robot_arm_accept()
{
    // local ptr can be declared instead of member ptr?
    robot_arm_socket_ptr_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    auto timer_ptr = std::make_shared<std::shared_ptr<boost::asio::deadline_timer>>(io_context_);
    robot_arm_acceptor_.async_accept(
        *robot_arm_socket_ptr_, 
        [&](boost::system::error_code error)
        {
            std::make_shared<SessionRobotArm>(std::move(*robot_arm_socket_ptr_), std::move(*timer_ptr));
            robot_arm_accept();
        });
}

void TCPServer::platform_accept()
{
    platform_socket_ptr_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    auto timer_ptr = std::make_shared<std::shared_ptr<boost::asio::deadline_timer>>(io_context_);
    platform_acceptor_.async_accept(
        *platform_socket_ptr_, 
        [&](boost::system::error_code error)
        {
            std::make_shared<SessionPlatform>(std::move(*platform_socket_ptr_), std::move(*timer_ptr));
            platform_accept();
        });
}

void TCPServer::readFromSpecifiedClient(Session* session)
{
    session->readMessage();
}

void TCPServer::writeToSpecifiedClient(Session* session)
{
    session->writeMessage();
}