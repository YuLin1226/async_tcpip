#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "session.hpp"


class Server
{

private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    int port_;
    std::shared_ptr<session> s_;

public:

    Server(boost::asio::io_context& io_context);

    Server(boost::asio::io_context& io_context, int& port);

    ~Server();
    
    void accept();

    std::shared_ptr<session> getSession();

};

