#include "server.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context)
: io_context_(io_context)
// , robot_arm_acceptor_(io_context_, 
//                       boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ROBOTARM_PORT))
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
    // robot_arm_accept();
    std::cout << ">>> Start acception." << std::endl;
    platform_accept();
}

// void TCPServer::robot_arm_accept()
// {
//     // local ptr can be declared instead of member ptr?
//     auto robot_arm_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
//     robot_arm_acceptor_.async_accept(
//         *robot_arm_socket_ptr, 
//         [&](boost::system::error_code error)
//         {
//             std::make_shared<SessionRobotArm>(std::move(*robot_arm_socket_ptr_), std::move(*timer_ptr));
//             robot_arm_accept();
//         });
// }

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
                    std::array<unsigned char, 4> data{'1','2','3','4'};
                    platform_session_->write(data.data(), 4);
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

// std::shared_ptr<Session::SessionRobotArm> TCPServer::getRobotArmSession()
// {
//     return robotarm_session_;
// }