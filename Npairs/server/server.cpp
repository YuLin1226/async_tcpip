#include "server.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context)
: io_context_(io_context)
, robotarm_acceptor_(io_context_, 
                      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ROBOTARM_PORT))
, platform_acceptor_(io_context_, 
                     boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PLATFORM_PORT))
, platform_session_(NULL)
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
    std::cout << ">>> Start acception." << std::endl;
    robotarm_accept();
    platform_accept();
}

void TCPServer::robotarm_accept()
{
    robotarm_socket_ptr_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    robotarm_acceptor_.async_accept(
        *robotarm_socket_ptr_, 
        [&](boost::system::error_code error)
        {
            std::make_shared<Session::SessionRobotArm>(io_context_, std::move(*robotarm_socket_ptr_));
            robotarm_accept();
        });
}

void TCPServer::platform_accept()
{
    platform_socket_ptr_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    platform_acceptor_.async_accept(
        *platform_socket_ptr_, 
        [&, this](boost::system::error_code error)
        {
            platform_session_ = std::make_shared<Session::SessionPlatform>(io_context_, std::move(*platform_socket_ptr_));
            platform_session_->start(
                [this](const Frame::FramePlatform &frame)
                {
                    auto frameSize = frame.parseFrameSize();
                    frame.print(frameSize, std::cout);
                    platform_session_->start_decode_data_ = 0;
                    //todo: check this
                    platform_session_->shutdownTimerWhenDataReceived();
                },
                []()
                {
                    std::cerr << "session broken" << std::endl;
                });            
            platform_accept();
        });
}

std::shared_ptr<Session::SessionPlatform> TCPServer::getPlatformSession()
{
    std::lock_guard<std::mutex> lock(mtx_);
    return platform_session_;
}

std::shared_ptr<Session::SessionRobotArm> TCPServer::getRobotArmSession()
{
    std::lock_guard<std::mutex> lock(mtx_);
    return robotarm_session_;
}