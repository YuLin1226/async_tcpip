#include <iostream>
#include <optional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class TCPserver
{
    typedef TCPserver                       this_type;
    typedef boost::asio::ip::tcp::acceptor  acceptor_type;
    typedef boost::asio::ip::tcp::endpoint  endpoint_type;
    typedef boost::asio::ip::tcp::socket    socket_type;

private:
    boost::asio::io_service io_service_;
    acceptor_type           acceptor_;

public:

    TCPserver():
    acceptor_(io_service_, endpoint_type(boost::asio::ip::tcp::v4(), 6688))
    {
        accept();
    }

    ~TCPserver()
    {
    }

    void run()
    {
        io_service_.run();
    }

    void accept()
    {
        std::shared_ptr<socket_type> socket_ptr = std::make_shared<socket_type>(io_service_);
        acceptor_.async_accept(*socket_ptr,
                               boost::bind(&this_type::acceptHandler,
                                           this,
                                           boost::asio::placeholders::error,
                                           socket_ptr));
    }

    void acceptHandler(const boost::system::error_code& ec, std::shared_ptr<socket_type> socket_ptr)
    {
        if(ec) return;
        std::cout << ">>> Client: " << socket_ptr->remote_endpoint().address() << std::endl;
        socket_ptr->async_write_some(boost::asio::buffer("Hello asio client, this is asio server"),
                                     boost::bind(&this_type::writeHandler,
                                                 this,
                                                 boost::asio::placeholders::error));
    }

    void writeHandler(const boost::system::error_code& ec)
    {
        std::cout << ">>> send message completed" << std::endl;
    }
};

int main()
{
    try
    {
        std::cout << ">>> Server starts" << std::endl;
        TCPserver server;
        server.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}