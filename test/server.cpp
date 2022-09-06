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

    void Server::accept()
    {
        platform_accept();
    }

    void Server::platform_accept()
    {
        platform_socket_ptr_ = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        // auto timer_ptr = std::make_shared<std::shared_ptr<boost::asio::deadline_timer>>(io_context_);
        platform_acceptor_.async_accept(
            *platform_socket_ptr_, 
            [&](boost::system::error_code error)
            {
                auto s = std::make_shared<Session::SessionEx>(io_context_, std::move(*platform_socket_ptr_));

                s->start(
                [s](const Frame::FrameEX &frame)
                {
                    auto frameSize = frame.parseFrameSize();
                    frame.print(frameSize, std::cout);
                    //todo: check this
                    std::array<unsigned char, 4> data{0x3, 0x1, 0x4, 0x1};
                    s->write(data.data(), 4);
                },
                []()
                {
                    std::cerr << "session broken" << std::endl;
                });

                platform_accept();
            });
    }

} // namespace TCP
