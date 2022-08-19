#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "server.hpp"


    Server::Server(boost::asio::io_context& io_context)
    : io_context_(io_context)
    // , port_(6688)
    , acceptor_(io_context_, 
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6688))
    , s_(NULL)
    {
        std::cout << "*** Create server. ***\n";
    }

    Server::Server(boost::asio::io_context& io_context, int& port)
    : io_context_(io_context)
    // , port_(port)
    , acceptor_(io_context_, 
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6688))
    , s_(NULL)
    {
        std::cout << "*** Create server. ***\n";
    }

    Server::~Server()
    {
        std::cout << "*** Server eliminated. ***\n";
    }

    void Server::accept()
    {
        socket_ = std::make_unique<boost::asio::ip::tcp::socket>(io_context_);
        acceptor_.async_accept(
            *socket_, 
            [&, this](boost::system::error_code error)
            {
                // if a new client connects.
                s_ = std::make_shared<session>(std::move(*socket_), io_context_);
                // wait for new clients to connect.
                accept();
            });
    }

    std::shared_ptr<session> Server::getSession()
    {
        return s_;
    }

    
