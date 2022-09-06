#include "server.hpp"

namespace TCP
{
    Server::Server(boost::asio::io_context& io_context)
    : io_context_(io_context)
    , platform_acceptor_(io_context_, 
                        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PLATFORM_PORT))
    {
        std::cout << ">>> Server created." << std::endl;
        accept();
    }
    
    Server::~Server()
    {
        std::cout << ">>> Server destroyed." << std::endl;
    }

    void Server::platform_accept()
    {
        platform_socket_ptr_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        auto timer_ptr = std::make_shared<std::shared_ptr<boost::asio::deadline_timer>>(io_context_);
        platform_acceptor_.async_accept(
            *platform_socket_ptr_, 
            [&](boost::system::error_code error)
            {
                // std::make_shared<SessionPlatform>(std::move(*platform_socket_ptr_), std::move(*timer_ptr));
                platform_accept();
            });
    }

} // namespace TCP
