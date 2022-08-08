#include <iostream>
#include <boost/asio.hpp>

class session : public std::enable_shared_from_this<session>
{
public:

    session(boost::asio::ip::tcp::socket&& socket)
    : socket(std::move(socket))
    {
    }

    void start()
    {
        boost::asio::async_read_until(socket, 
                                      streambuf, 
                                      '\n', 
                                      [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
        {
            std::cout << std::istream(&self->streambuf).rdbuf();
        });
    }

private:

    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
};