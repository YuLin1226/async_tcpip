#include <iostream>
#include <boost/asio.hpp>

class session : public std::enable_shared_from_this<session>
{
public:

    session(boost::asio::ip::tcp::socket&& socket)
    : socket(std::move(socket))
    {
    }

    ~session()
    {
        std::cout << "Session destroyed" << std::endl;
    }

    void start()
    {
        // readMsg(10);
        boost::asio::async_read_until(socket, 
                                      streambuf, 
                                      '\n', 
                                      [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
        {
            std::cout << std::istream(&self->streambuf).rdbuf();
        });
        writeMsg();
    }

    void writeMsg()
    {
        boost::asio::async_write(
            socket,
            boost::asio::buffer("Hello asio client, this is asio server\n"),
            [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
            {
                std::cout << ">>> send message completed" << std::endl;
            });
    }

    void writeMsg1()
    {
        for(auto i = 0 ; i < received_data.size() ; i++)
            std::cout << received_data[i] << " ";
        boost::asio::async_write(
            socket,
            boost::asio::buffer(received_data, 10),
            [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
            {
                std::cout << ">>> send message completed" << std::endl;
            });
    }

    void readMsg(uint8_t data_size)
    {
        auto self(shared_from_this());
        boost::asio::async_read(
            socket,
            boost::asio::buffer(received_data, data_size),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    // send back to client
                    writeMsg1();
                }
            }
        );
        
    }
    

private:

    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<char> received_data = std::vector<char>(10);
};