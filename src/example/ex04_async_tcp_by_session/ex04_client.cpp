#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/bind.hpp>

class TCPclient : public std::enable_shared_from_this<TCPclient>
{
    // Simplified type definition
    typedef TCPclient                       this_type;
    typedef boost::asio::ip::tcp::endpoint  endpoint_type;
    typedef boost::asio::ip::address        address_type;
    typedef boost::asio::ip::tcp::socket    socket_type;
    // typedef std::shared_ptr<socket_type>    socket_pointer;
    typedef std::vector<char>               buffer_type;

private:
    boost::asio::io_service     io_service_;
    buffer_type                 buffer_;
    endpoint_type               endpoint_;

public:
    TCPclient():
    buffer_(100,0),
    endpoint_(address_type::from_string("127.0.0.1"), 6688)
    {
        start();
    }
    ~TCPclient()
    {
    }

    void run()
    {
        io_service_.run();
    }

    void start()
    {
        std::shared_ptr<socket_type> socker_ptr = std::make_shared<socket_type>(io_service_);
        socker_ptr->async_connect(endpoint_,
                                  boost::bind(&this_type::connectionHandler,
                                              this,
                                              boost::asio::placeholders::error,
                                              socker_ptr));
    }

    void connectionHandler(const boost::system::error_code& ec, std::shared_ptr<socket_type> socket_ptr)
    {
        if(ec) return;
        std::cout << ">>> Receive from " << socket_ptr->remote_endpoint().address() << std::endl;
        // socket_ptr->async_read_some(boost::asio::buffer(buffer_),
        //                             boost::bind(&this_type::readHandler, 
        //                                         this, 
        //                                         boost::asio::placeholders::error));

        socket_ptr->async_read_some(boost::asio::buffer(buffer_),
                                    boost::bind(&this_type::readHandler, 
                                                this, 
                                                boost::asio::placeholders::error,
                                                socket_ptr));
        boost::asio::async_write(
            *socket_ptr,
            boost::asio::buffer("$1,safe,0,0,done$\n"),
            [&](boost::system::error_code error, std::size_t bytes_transferred)
            {
                std::cout << ">>> send message completed" << std::endl;
            });

    }

    void readHandler(const boost::system::error_code& ec, std::shared_ptr<socket_type> socket_ptr)
    {
        if(ec) return;
        std::cout << &buffer_[0] << std::endl;
        socket_ptr->async_read_some(boost::asio::buffer(buffer_),
                                    boost::bind(&this_type::readHandler, 
                                                this, 
                                                boost::asio::placeholders::error,
                                                socket_ptr));
    }

};

int main()
{
    try
    {
        std::cout << "Client starts." << std::endl;
        TCPclient client;
        client.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}

